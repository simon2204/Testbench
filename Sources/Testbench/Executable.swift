//
//  Executable.swift
//  
//
//  Created by Simon Schöpke on 05.06.21.
//

import Foundation

struct Executable {
	
	/// URL of the executable
    let url: URL
	
	/// Name of the file where the exitcode gets to be saved in.
	var exitcodeName: URL?
    
    func run(arguments: [String], deadline: DispatchTimeInterval) throws -> TimeInterval {
        let pipe = Pipe()
        let task = Process()
        
        task.executableURL = url
        task.arguments = arguments
        task.standardOutput = pipe
		
        let timeNeeded = try Executable.measureExecutionTime {
            try task.run()
            
            let deadlineHasPassed = task.waitUntilExit(deadline: .now() + deadline)
            
            if deadlineHasPassed { throw RunTimeExeededError(seconds: deadline.seconds) }
			
			if let exitcodeName = exitcodeName {
				let status = "\(task.terminationStatus)"
				try status.write(to: exitcodeName, atomically: true, encoding: .ascii)
			} else {
                let status = task.terminationStatus
				guard status == 0 else {
					let description = pipe.errorDescription
					throw UncaughtSignalError(status: status, description: description)
				}
			}
        }
        
        return timeNeeded
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
            description = "Die Anwendung wurde aufgrund von Zeitüberschreitung beendet."
        }
    }
}

extension Executable {
    struct UncaughtSignalError: DescriptiveError {
        let description: String
        init(status: Int32, description: String) {
            let defaultDescription = "Die Anwendung beendete sich mit Statuscode \(status)."
            self.description = defaultDescription + (description.isEmpty ? "" : " \(description)")
        }
    }
}
