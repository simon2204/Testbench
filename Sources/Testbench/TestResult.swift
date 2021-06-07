//
//  TestResult.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

public struct TestResult: Codable {
    public private(set) var entries: [LogfileEntry] = []
    public var runTime: TimeInterval?
    public var errorMsg: String?
    public var date: String
    public var name: String!
    
    init() {
        let now = Date()
        let localizedDate = DateFormatter
            .localizedString(
                from: now,
                dateStyle: .full,
                timeStyle: .long)
        self.date = localizedDate
    }
    
    public struct LogfileEntry: Codable {
        public let id: Int
        public let groupId: Int
        public let info: String
        public let expected: String
        public let actual: String
        public let error: String
        public let total: Int
    }
}

extension TestResult {
    init(from logfile: URL) throws {
        self.init()
        
        let decoder = JSONDecoder()
        
        // read in the logdata from a local file
        let logdata = try String(contentsOf: logfile, encoding: .utf8)
        
        // each line represents a `LogfileEntry`
        let lines = logdata.components(separatedBy: .newlines)
        
        for line in lines {
            guard let data = Self.dataFromLine(line) else { continue }
            let logfileEntry = try decoder.decode(LogfileEntry.self, from: data)
            self.append(entry: logfileEntry)
        }
    }
    
    private static func dataFromLine(_ line: String) -> Data? {
        if line.isEmpty { return nil }
        return line.data(using: .utf8)
    }
}

extension TestResult {
    mutating func append(entry: LogfileEntry) {
        self.entries.append(entry)
    }
}
