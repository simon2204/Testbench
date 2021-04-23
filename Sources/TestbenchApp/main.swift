import ArgumentParser
import Foundation
import TestbenchLib

struct Testbench: ParsableCommand {
    
    @Option(name: .shortAndLong, help: "Set the configuration file.")
    var config: String?
    
    mutating func run() throws {
        guard let testbenchConfig = constructTestbenchConfiguration() else { return }
        print(testbenchConfig)
        Bundle.module.url(forResource: "config", withExtension: "json")
        
        let process = Process()
        process.launchPath = "/usr/bin/env"
        process.arguments = ["sudo", "-u", "simon"]
              
        process.launch()
        
        DispatchQueue.main.asyncAfter(deadline: .now() + .milliseconds(200)) {
            process.terminate()
        }
        
        process.waitUntilExit()
    }
    
    func constructTestbenchConfiguration() -> TestbenchConfiguration? {
        testbenchConfigurationFromInput() ?? Testbench.testbenchConfigurationFromResources()
    }
    
    func testbenchConfigurationFromInput() -> TestbenchConfiguration? {
        guard let config = config else { return nil }
        return try? TestbenchConfiguration.loadWithJSONDecoder(from: URL(fileURLWithPath: config))
    }
    
    static func testbenchConfigurationFromResources() -> TestbenchConfiguration? {
        guard let defaultConfigURL = Bundle.module.url(forResource: "config", withExtension: "json")
        else { return nil }
        return try? TestbenchConfiguration.loadWithJSONDecoder(from: defaultConfigURL)
    }
}

Testbench.main()


