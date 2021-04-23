//
//  TestResult.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

struct TestResult {
    private(set) var entries: Result<[Entry], BuildError> = .success([])
    
    mutating func appendEntry(_ newEntry: Entry) {
        switch entries {
        case .failure: break
        case .success(let entries): appendEntry(newEntry, to: entries)
        }
    }
    
    mutating func buildWithError(_ error: BuildError) {
        entries = .failure(error)
    }
    
    private mutating func appendEntry(_ entry: Entry, to entries: [Entry]) {
        var newEntries = entries
        newEntries.append(entry)
        self.entries = .success(newEntries)
    }
    
    struct Entry {
        let task: Task
        let successful: Bool
        var points: Int {
            return successful ? task.points : 0
        }
    }
    
    enum BuildError: Error {
        case didNotCompile
        case couldNotCreateDoxygenFile
        case timeout
    }
}
