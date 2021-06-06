//
//  Executable.swift
//  
//
//  Created by Simon Schöpke on 05.06.21.
//

import Foundation

struct Executable {
    let url: URL
    
    func run(arguments: [String], deadline: DispatchTimeInterval) throws -> TimeInterval {
        let pipe = Pipe()
        let task = Process()
        
        task.executableURL = url
        task.arguments = arguments
        task.standardOutput = pipe
        
        let runResult = try Executable.measureExecutionTime {
            try task.run()
            let deadlineHasPassed = task.waitUntilExit(deadline: .now() + deadline)
            if deadlineHasPassed {
                throw RunTimeExeededError(seconds: deadline.seconds)
            }
            guard task.terminationReason == .exit else {
                let status = task.terminationStatus
                let description = pipe.errorDescription
                throw UncaughtSignalError(status: status, description: description)
            }
        }
        
        return runResult
    }
}

// MARK: - Measure Execution Time

extension Executable {
    private static func measureExecutionTime(task: () throws -> Void) rethrows -> TimeInterval {
        let start = DispatchTime.now()
        try task()
        let end = DispatchTime.now()
        
        let timeNeeded = end.uptimeNanoseconds - start.uptimeNanoseconds
        let timeNeededInSeconds = Double(timeNeeded) / 1_000_000_000
        
        return timeNeededInSeconds
    }
}

// MARK: - Error(s)

extension Executable {
    struct RunTimeExeededError: DescriptiveError {
        let description: String
        
        init(seconds: TimeInterval) {
            description = "Die maximale Laufzeit des Programmes von \(seconds) Sekunden wurde überschritten."
        }
    }

    struct UncaughtSignalError: DescriptiveError {
        let description: String
        
        init(status: Int32, description: String) {
            let defaultDescription = "Das Programm beendete sich mit Statuscode \(status)."
            self.description = defaultDescription + (description.isEmpty ? "" : "\n\n\(description)")
        }
    }
}
