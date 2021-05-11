//
//  TestCase.swift
//  
//
//  Created by Simon Schöpke on 07.05.21.
//

import Foundation


struct TestCase {
    
    /// `URL` to the test configuration.
    let _testConfigURL: URL
    
    let globalConfig: GlobalConfig
    /// Config from the test configuration.
    let config: TestConfig
    
    public var label: String {
        config.label
    }
    
    public var workingDirectory: URL {
        URL(fileURLWithPath: globalConfig.workingDirectory)
    }
    
    public var testSpecURL: URL {
        URL(fileURLWithPath: globalConfig.testSpecificationDirectory)
    }
    
    public var testConfigURL: URL {
        _testConfigURL
    }
    
    public var timeout: DispatchTimeInterval {
        .milliseconds(config.timeoutInMs)
    }
    
    public var sharedResources: URL? {
        guard let resources = config.sharedResources else {
            return nil
        }
        return URL(fileURLWithPath: resources, relativeTo: testConfigURL)
    }
    
    public var submissionExecutable: Executable {
        if let executable = Executable(
            executable: config.submissionExecutable,
            testConfigURL: _testConfigURL,
            buildOptions: globalConfig.buildOptions)
        {
            return executable
        }
        
        return Executable(name: "submission")
    }
    
    public var customTestExecutable: Executable? {
        Executable(
            executable: config.customExecutable,
            testConfigURL: _testConfigURL,
            buildOptions: globalConfig.buildOptions
        )
    }
    
    public var compiler: URL {
        URL(fileURLWithPath: globalConfig.compiler)
    }
    
    public var tasks: [Process] {
        let processes = config.tasks ?? []
        return processes.map(Process.init)
    }
    
}

extension TestCase {
    public struct Process {
        /// Name of the executable
        public let executableName: String
        
        /// Arguments to pass to the executable
        public let commandLineArguments: [String]
        
        fileprivate init(_ process: TestConfig.Process) {
            self.executableName = process.executableName
            self.commandLineArguments = process.commandLineArguments
        }
    }
}

extension TestCase {
    public struct Executable {
        /// Name of the executable after compiling
        public let name: String
        
        /// Name of the directory containing dependencies for building the executable
        public let dependencies: URL?
        
        /// Additional build options
        ///
        /// Overrides build options from "config.json" but does not override internal build options.
        public let buildOptions: [String]
        
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
            executable: TestConfig.Executable?,
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
