//
//  Compiler.swift
//  
//
//  Created by Simon Schöpke on 21.04.21.
//

import Foundation

struct Compiler {
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
        
        let secondsNeeded = try Compiler.measureExecutionTime {
            try runBuildProcess(withArgs: buildArguments)
        }
        
        return secondsNeeded
    }
    
    
    func run(
        process: URL,
        arguments: [String],
        deadline: DispatchTimeInterval) throws -> TimeInterval {
        
        let secondsNeeded = try Compiler.measureExecutionTime {
            let task = try Process.run(process, arguments: arguments)
            let deadlineHasPassed = task.waitUntilExit(deadline: .now() + deadline)
            
            if deadlineHasPassed {
                throw CompileError.runTimeExceeded(seconds: deadline.seconds)
            }
            
            guard task.terminationReason == .exit else {
                throw CompileError.uncaughtSignal(status: task.terminationStatus)
            }
        }
        
        return secondsNeeded
    }
    
    private func runBuildProcess(withArgs arguments: [String]) throws {
        let task = try Process.run(compiler, arguments: arguments)
        task.waitUntilExit()
        guard task.terminationStatus == 0 else {
            throw CompileError.didNotCompile(status: task.terminationStatus)
        }
    }
}

extension Compiler {
    private static func measureExecutionTime(task: () throws -> Void) rethrows -> TimeInterval {
        let start = DispatchTime.now()
        try task()
        let end = DispatchTime.now()
        let nanoTime = end.uptimeNanoseconds - start.uptimeNanoseconds
        let timeInterval = Double(nanoTime) / 1_000_000_000
        return timeInterval
    }
}

extension Compiler {
    enum CompileError: Error, Equatable {
        case buildTimeExceeded(seconds: TimeInterval)
        case runTimeExceeded(seconds: TimeInterval)
        case didNotCompile(status: Int32)
        case uncaughtSignal(status: Int32)
    }
}
