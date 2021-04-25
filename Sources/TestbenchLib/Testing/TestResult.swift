//
//  TestResult.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

public struct TestResult {
    public private(set) var entries: Result<[Entry], Error> = .success([])
    
    mutating func appendEntry(_ newEntry: Entry) {
        switch entries {
        case .failure: break
        case .success(let entries): appendEntry(newEntry, to: entries)
        }
    }
    
    mutating func buildWithError(_ error: Error) {
        entries = .failure(error)
    }
    
    private mutating func appendEntry(_ entry: Entry, to entries: [Entry]) {
        var newEntries = entries
        newEntries.append(entry)
        self.entries = .success(newEntries)
    }
    
    public struct Entry {
        let task: Task
        let successful: Bool
        var points: Int {
            return successful ? task.points : 0
        }
    }
}

extension TestResult {
    static func fromLogfile(at url: URL, testconfig: TestConfiguration) throws -> TestResult {
        var testResult = TestResult()
        
        let logdata = try String(contentsOfFile: url.path)
        let lines = logdata.components(separatedBy: .newlines)
        
        for line in lines {
            if line.isEmpty || line.hasPrefix("#") { continue }
            
            let entries = line.components(separatedBy: "\t")
            
            guard let taskID = Int(entries[0]) else { continue }
            
            let successful = entries[1].lowercased() == "success"
            
            // TODO: Make use of description
            let description = entries.count > 2 ? entries[2] : ""
            
            guard let task = testconfig
                    .tasks
                    .first(where: {$0.id == taskID}) else { continue }
            
            let entry = Entry(task: task, successful: successful)
            
            testResult.appendEntry(entry)
        }
        
        return testResult
    }
}
