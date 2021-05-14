//
//  CProcessManager.swift
//  
//
//  Created by Simon Schöpke on 21.04.21.
//

import Foundation

struct CProcessManager {
    let compiler: URL
    
    init(_ compiler: URL) {
        self.compiler = compiler
    }
    
    func build(
        sourceFiles: [URL],
        destination: URL,
        options: [String]) throws -> TimeInterval {

        let sourceFilePaths = sourceFiles.map(\.path)
        let outputOption = "-o"
        let outputFile = "\(destination.path)"
        let buildArguments = sourceFilePaths + options + [outputOption, outputFile]
        
        let secondsNeeded = try CProcessManager.measureExecutionTime {
            try runBuildProcess(withArgs: buildArguments)
        }
        
        return secondsNeeded
    }
    
    
    func run(
        process: URL,
        arguments: [String],
        deadline: DispatchTimeInterval) throws -> TimeInterval {
        
        let pipe = Pipe()
        let task = Process()
        
        task.executableURL = process
        task.arguments = arguments
        task.standardOutput = pipe
        
        let secondsNeeded = try CProcessManager.measureExecutionTime {
            try task.run()
        
            let deadlineHasPassed = task.waitUntilExit(deadline: .now() + deadline)
            
            if deadlineHasPassed {
                throw ProcessError.runTimeExceeded(seconds: deadline.seconds)
            }
            
            guard task.terminationReason == .exit else {
                let stdError = StdError(pipe: pipe)
  
                throw ProcessError.uncaughtSignal(
                    status: task.terminationStatus,
                    description: stdError.description)
            }
        }
        
        return secondsNeeded
    }
    
    private func runBuildProcess(withArgs arguments: [String]) throws {
        let pipe = Pipe()
        let task = Process()
        
        task.executableURL = compiler
        task.arguments = arguments
        task.standardError = pipe
        
        try task.run()
        
        task.waitUntilExit()
        
        guard task.terminationStatus == 0 else {
            let stdError = StdError(pipe: pipe)
  
            throw ProcessError.didNotCompile(
                status: task.terminationStatus,
                description: stdError.description)
        }
    }
}

extension CProcessManager {
    private static func measureExecutionTime(task: () throws -> Void) rethrows -> TimeInterval {
        let start = DispatchTime.now()
        try task()
        let end = DispatchTime.now()
        let nanoTime = end.uptimeNanoseconds - start.uptimeNanoseconds
        let timeInterval = Double(nanoTime) / 1_000_000_000
        return timeInterval
    }
}

extension CProcessManager {
    enum ProcessError: Error, Equatable {
        case buildTimeExceeded(seconds: TimeInterval)
        case runTimeExceeded(seconds: TimeInterval)
        case didNotCompile(status: Int32, description: String)
        case uncaughtSignal(status: Int32, description: String)
    }
}

struct StdError: Equatable, CustomStringConvertible {
    let description: String
    
    init(pipe: Pipe) {
        let errData = pipe.fileHandleForReading.readDataToEndOfFile()
        self.description = String(data: errData, encoding: .utf8)?
            .trimmingCharacters(in: .newlines) ?? ""
    }
}
