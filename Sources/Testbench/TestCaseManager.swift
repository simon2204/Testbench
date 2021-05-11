//
//  TestCaseManager.swift
//
//
//  Created by Simon Schöpke on 06.05.21.
//

import Foundation

struct TestCaseManager {
    private let config: URL
    
    init(config: URL) {
        self.config = config
    }
    
    func availableAssignments() throws -> [Assignment] {
        let config = try GlobalConfig.loadWithJSONDecoder(from: self.config)
        return config.assignments
    }
    
    func testCase(forAssignment id: Int) throws -> TestCase {
        let assignments = try availableAssignments()
        
        guard let assignment = assignments.first(where: { $0.id == id }) else {
            throw TestCaseError.assignmentNotFound(forID: id)
        }
        
        let config = try GlobalConfig.loadWithJSONDecoder(from: config)
        let testSpecURL = URL(fileURLWithPath: config.testSpecificationDirectory)
        let testConfigURL = URL(fileURLWithPath: assignment.filePath, relativeTo: testSpecURL)
        let testConfig = try TestConfig.loadWithJSONDecoder(from: testConfigURL)
        
        return TestCase(
            _testConfigURL: testConfigURL,
            globalConfig: config,
            config: testConfig)
    }
    
    func performTests(submission: URL, testcase: TestCase) throws -> TestResult {
        let unitTest = try UnitTest(config: testcase, submission: submission)
        return try unitTest.performTests()
    }
}

extension TestCaseManager {
    enum TestCaseError: Error {
        case assignmentNotFound(forID: Int)
    }
}
