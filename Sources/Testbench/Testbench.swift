//
//  Testbench.swift
//  
//
//  Created by Simon Schöpke on 26.04.21.
//

import Foundation

public struct Testbench {
    static let resources = Bundle.module.resourceURL!.appendingPathComponent("Resources")
    static let testSpecification = resources.appendingPathComponent("test_specification")
    static let submission = URL(fileURLWithPath: "/Users/Simon/Desktop/TestbenchDirectories/submission")
    
    public static func findAllTestConfigurations() -> [TestConfiguration] {
        TestConfiguration.makeFromFiles(named: "test-configuration.json", at: Testbench.testSpecification)
    }
    
    public static func performTestsForSubmission(at path: String, forAssignmentWithName name: String) -> TestResult? {
        guard let testConfig = Testbench.findAllTestConfigurations().first(where: {$0.name == name}) else { return nil }
        
        guard let testbenchConfig = try? TestbenchConfiguration(directory: resources, fileName: "config.json") else { return nil }
        
        let unitTest = UnitTest(testbenchConfig: testbenchConfig)
        
        return try? unitTest.performTestForSubmission(at: submission, withConfiguration: testConfig)
    }
}
