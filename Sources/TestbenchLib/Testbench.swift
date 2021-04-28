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
    
    public static func findAllTestConfigurations() -> [TestConfiguration] {
        TestConfiguration.makeFromFiles(named: "test-configuration.json", at: Testbench.testSpecification)
    }
}
