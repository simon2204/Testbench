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
        options: [String]) throws -> ProcessResult {

        let sourceFilePaths = sourceFiles.map(\.path)
        let outputOption = "-o"
        let outputFile = "\(destination.path)"
        let buildArguments = sourceFilePaths + options + [outputOption, outputFile]
        
        let result = try CProcessManager.measureExecutionTime {
            try runBuildProcess(withArgs: buildArguments)
        }
        
        return result
    }
    
    
    func run(
        process: URL,
        arguments: [String],
        deadline: DispatchTimeInterval) throws -> ProcessResult {
        
        let pipe = Pipe()
        let task = Process()
        
        task.executableURL = process
        task.arguments = arguments
        task.standardOutput = pipe
        
        let result = try CProcessManager.measureExecutionTime {
            try task.run()
        
            let deadlineHasPassed = task.waitUntilExit(deadline: .now() + deadline)
            
            if deadlineHasPassed {
                return ProcessResult
                    .error(.runTimeExceeded(seconds: deadline.seconds))
            }
            
            guard task.terminationReason == .exit else {
                return ProcessResult
                    .error(.uncaughtSignal(
                            status: task.terminationStatus,
                            description: pipe.errorDescription))
            }
            
            return nil
        }
        
        return result
    }
    
    private func runBuildProcess(withArgs arguments: [String]) throws -> ProcessResult? {
        let pipe = Pipe()
        let task = Process()
        
        task.executableURL = compiler
        task.arguments = arguments
        task.standardError = pipe
        
        try task.run()
        
        task.waitUntilExit()
        
        guard task.terminationStatus == 0 else {
            return ProcessResult
                .error(.didNotCompile(
                        status: task.terminationStatus,
                        description: pipe.errorDescription))
        }
        
        return nil
    }
}

extension CProcessManager {
    private static func measureExecutionTime(task: () throws -> ProcessResult?) rethrows -> ProcessResult {
        let start = DispatchTime.now()
        if let result = try task() { return result }
        let end = DispatchTime.now()
        
        let timeNeeded = end.uptimeNanoseconds - start.uptimeNanoseconds
        let timeNeededInSeconds = Double(timeNeeded) / 1_000_000_000
        
        return .timeNeeded(seconds: timeNeededInSeconds)
    }
}

extension CProcessManager {
    enum ProcessResult: Equatable {
        case timeNeeded(seconds: TimeInterval)
        case error(ResultError)
    
        enum ResultError: Error, Equatable {
            case buildTimeExceeded(seconds: TimeInterval)
            case runTimeExceeded(seconds: TimeInterval)
            case didNotCompile(status: Int32, description: String)
            case uncaughtSignal(status: Int32, description: String)
            
            var description: String {
                var errorMsg: String
                
                switch self {
                case .buildTimeExceeded(seconds: let seconds):
                    errorMsg = "Die maximale Zeit zum Erstellen des Programmes von \(seconds) Sekunden wurde überschritten."
                    
                case .runTimeExceeded(seconds: let seconds):
                    errorMsg = "Die maximale Laufzeit des Programmes von \(seconds) Sekunden wurde überschritten."
                    
                case .didNotCompile(status: let status, description: let description):
                    errorMsg = "Das Programm konnte nicht kompiliert werden und warf Statuscode \(status)."
                    if !description.isEmpty { errorMsg.append("\n\n\(description)") }
                    
                case .uncaughtSignal(status: let status, description: let description):
                    errorMsg = "Das Programm beendete sich mit Statuscode \(status)."
                    if !description.isEmpty { errorMsg.append("\n\n\(description)") }
                }
                
                return errorMsg
            }
        }
    }
}
