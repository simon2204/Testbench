//
//  Config.swift
//  
//
//  Created by Simon Schöpke on 07.05.21.
//

import Foundation

/// Vereinigt die lokale Konfiguration mit der globalen Konfiguration.
struct Config {
    
    let testConfigURL: URL
    
    let globalConfig: GlobalConfig
    
    let localConfig: LocalConfig
    
    /// Name der Praktikumsaufgabe.
    var assignmentName: String {
        localConfig.assignmentName
    }
    
    /// Die gesamte Anzahl an Testfällen, die durchgeführt werden.
    var totalTestcases: Int {
        localConfig.totalTestcases
    }
    
    var testSpecURL: URL {
        testConfigURL
            .deletingLastPathComponent()
            .appendingPathComponent(globalConfig.testSpecificationDirectory)
    }
    
    var timeout: DispatchTimeInterval {
        .milliseconds(localConfig.timeoutInMs)
    }
    
    var sharedResources: URL? {
        guard let resources = localConfig.sharedResources else {
            return nil
        }
        return URL(fileURLWithPath: resources, relativeTo: testConfigURL)
    }
    
    var submissionExecutable: Executable {
        if let executable = Executable(
            executable: localConfig.submissionExecutable,
            testConfigURL: testConfigURL,
            buildOptions: globalConfig.buildOptions)
        {
            return executable
        }
        
        return Executable(name: "submission")
    }
    
    var customTestExecutable: Executable? {
        Executable(
            executable: localConfig.customExecutable,
            testConfigURL: testConfigURL,
            buildOptions: globalConfig.buildOptions
        )
    }
    
    var compiler: URL {
        URL(fileURLWithPath: globalConfig.compiler)
    }
    
    var tasks: [Process] {
        let processes = localConfig.tasks ?? []
        return processes.map(Process.init)
    }
}

extension Config {
    public struct Process {
        /// Name of the executable
        let executableName: String
        
        /// Arguments to pass to the executable
        let commandLineArguments: [String]
		
		/// Name of the file where the exit-code should get saved in.
		let exitcodeName: String?
        
        fileprivate init(_ process: LocalConfig.Task) {
            self.executableName = process.executableName
            self.commandLineArguments = process.commandLineArguments
			self.exitcodeName = process.exitcodeFileName
        }
    }
}

extension Config {
    struct Executable {
        
        /// Name of the executable after compiling
        let name: String
        
        /// Name of the directory containing dependencies for building the executable
        let dependencies: URL?
        
        /// Additional build options
        ///
        /// Overrides build options from "config.json" but does not override internal build options.
        let buildOptions: [String]
        
        fileprivate init(
            name: String,
            dependencies: URL? = nil,
            buildOptions: [String]? = nil)
        {
            self.name = name
            self.dependencies = dependencies
            self.buildOptions = buildOptions ?? []
        }
        
        fileprivate init?(
            executable: LocalConfig.Executable?,
            testConfigURL: URL,
            buildOptions: [String]?)
        {
            guard let executable = executable else {
                return nil
            }
            
            let buildOptions = executable.buildOptions ?? buildOptions
            var dependenciesURL: URL?
            
            if let dependencies = executable.dependencies {
                dependenciesURL = URL(
                    fileURLWithPath: dependencies,
                    relativeTo: testConfigURL)
            }
            
            self.name = executable.name
            self.dependencies = dependenciesURL
            self.buildOptions = buildOptions ?? []
        }
    }
}
