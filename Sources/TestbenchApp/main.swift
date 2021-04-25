import ArgumentParser
import Foundation
import TestbenchLib

struct Testbench: ParsableCommand {
    
    @Option(name: .shortAndLong, help: "Set the configuration file.")
    var config: String?
    
    mutating func run() throws {
        guard let testbenchConfig = try constructTestbenchConfiguration() else { return }
        
        let testConfigURL = URL(fileURLWithPath: "/Users/Simon/Desktop/test_specification/blatt01_Ulam")
        let submissionURL = URL(fileURLWithPath: "/Users/Simon/Desktop/submission")

        let unitTest = UnitTest(testbenchConfiguration: testbenchConfig)

        let testConfiguration = try TestConfiguration(directory: testConfigURL,
                                                      fileName: "test-configuration.json")

        let result = try unitTest.performTestForSubmission(at: submissionURL, withConfiguration: testConfiguration)
    }
    
    func constructTestbenchConfiguration() throws -> TestbenchConfiguration? {
        try testbenchConfigurationFromInput() ?? Testbench.testbenchConfigurationFromResources()
    }
    
    func testbenchConfigurationFromInput() throws -> TestbenchConfiguration? {
        guard let config = config else { return nil }
        return try TestbenchConfiguration.loadWithJSONDecoder(from: URL(fileURLWithPath: config))
    }
    
    static func testbenchConfigurationFromResources() throws -> TestbenchConfiguration? {
        guard let defaultConfigURL = Bundle.module.url(forResource: "config", withExtension: "json")
        else { return nil }
        return try TestbenchConfiguration.loadWithJSONDecoder(from: defaultConfigURL)
    }
}

Testbench.main()
