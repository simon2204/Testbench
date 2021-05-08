//
//  Testbench.swift
//  
//
//  Created by Simon Schöpke on 26.04.21.
//

import Foundation

public struct Testbench {
    private let testCaseManager: TestCaseManager
    
    public init(config: URL) {
        testCaseManager = TestCaseManager(configURL: config)
    }
    
    public func availableAssignments() throws -> [Assignment] {
        try testCaseManager.availableAssignments()
    }
    
    public func performTests(submission: URL, assignment id: Int) throws -> TestResult {
        let testCase = try testCaseManager.testCase(forAssignment: id)
        return try testCaseManager.performTests(submission: submission, testcase: testCase)
    }
}
