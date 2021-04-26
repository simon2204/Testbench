import ArgumentParser
import Foundation
import TestbenchLib

struct TestbenchApp: ParsableCommand {
    
    @Option(name: .shortAndLong, help: "Set the configuration file.")
    var config: String?
    
    mutating func run() throws {
        guard let _ = try constructTestbenchConfiguration() else { return }
    }
    
    func constructTestbenchConfiguration() throws -> TestbenchConfiguration? {
        try testbenchConfigurationFromInput() ?? TestbenchApp.testbenchConfigurationFromResources()
    }
    
    func testbenchConfigurationFromInput() throws -> TestbenchConfiguration? {
        guard let config = config else { return nil }
        return try TestbenchConfiguration.loadWithJSONDecoder(from: URL(fileURLWithPath: config))
    }
    
    static func testbenchConfigurationFromResources() throws -> TestbenchConfiguration? {
//        let defaultConfigURL = resources.appendingPathComponent("config.json")
//        return try TestbenchConfiguration.loadWithJSONDecoder(from: defaultConfigURL)
        return nil
    }
}

TestbenchApp.main()
