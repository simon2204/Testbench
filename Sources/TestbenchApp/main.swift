import ArgumentParser
import Foundation
import TestbenchLib

struct Testbench: ParsableCommand {
    
    @Option(name: .shortAndLong, help: "Set the configuration file.")
    var config: String?
    
    mutating func run() throws {
        guard let _ = try constructTestbenchConfiguration() else { return }
    
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
