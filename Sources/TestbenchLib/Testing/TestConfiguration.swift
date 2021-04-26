//
//  TestConfiguration.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

public struct TestConfiguration: ObtainableFromDirectory {
    public var file: URL?
    let relativeTestDirectory: String
    let name: String
    let assignmentId: String
    let type: TestType
    let tasks: [Task]
    let pointsNeeded: Int
    let timeoutInMs: Int
    
    var testDirectory: URL? {
        file?.deletingLastPathComponent().appendingPathComponent(relativeTestDirectory)
    }
    
    enum TestType: String, Decodable {
        case unitTest           = "UNIT_TEST"
        case commandLineTest    = "COMMAND_LINE_ARG_TEST"
    }
}

extension TestConfiguration {
    public static func findAllFiles(named name: String, at url: URL) -> [TestConfiguration] {
        let testConfigurationURLs = FileManager.default.files(at: url, named: name)
        var testConfigurations = [TestConfiguration]()
        
        for testConfigurationURL in testConfigurationURLs {
            guard
                var testConfiguration = try? TestConfiguration.loadWithJSONDecoder(from: testConfigurationURL)
            else { continue }
            testConfiguration.file = testConfigurationURL
            testConfigurations.append(testConfiguration)
        }
        
        return testConfigurations
    }
}
