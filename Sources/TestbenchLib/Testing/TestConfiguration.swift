//
//  TestConfiguration.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

public struct TestConfiguration: ObtainableFromDirectory {
    
    /// `URL` to the local test-configuration file.
    public var file: URL?
    
    /// Relative path to the directory containing all test cases for an assignment.
    public let relativeTestDirectory: String
    
    /// The assignments name.
    ///
    /// For expample: 1. Ulam-Varianten, 2. Matrix, 6. Huffman Kommandozeile.
    public let name: String
    
    /// Assignment identification
    public let assignmentId: String
    
    /// The kind of test that should be applied.
    public let type: TestType
    
    /// Tasks that are performed as test cases on the submission.
    public let tasks: [Task]
    
    /// Points needed to pass an assignment.
    public let pointsNeeded: Int
    
    /// The maximum time needed for executing all test cases in milliseconds.
    ///
    /// If the test cases need more than the specified amout of time, the submission might have run into an infinite loop.
    public let timeoutInMs: Int
    
    /// The absolute `URL` to the test directory containing all test cases fo an assignment.
    public var testDirectory: URL? {
        // remove filename from the `URL` to get to the directory's `URL`
        // and go from there to the test directory
        file?.deletingLastPathComponent().appendingPathComponent(relativeTestDirectory)
    }
    
    /// A `TestType` can be a unit test for modules or a command-line-argument test.
    public enum TestType: String, Decodable {
        case unitTest           = "UNIT_TEST"
        case commandLineTest    = "COMMAND_LINE_ARG_TEST"
    }
}

extension TestConfiguration {
    /// Recursively scans a directory for all test-configuration files.
    ///
    /// If a test-configuration file cannot be parsed it won't be included in the list of `TestConfiguration`s.
    ///
    /// - Parameters:
    ///   - name: Name of the test-configuration files to scan for.
    ///   - url: Directory to scan for test-configuration files.
    /// - Returns: An array of all found `TestConfiguration`s.
    public static func makeFromFiles(named name: String, at url: URL) -> [TestConfiguration] {
        // retrieves all the files with the given `name` first.
        let testConfigurationURLs = FileManager.default.files(at: url, named: name)
        
        // will include all `Testconfiguration`s that have been found.
        var testConfigurations = [TestConfiguration]()
        
        // tries to parse all files as a `TestConfiguration`.
        for testConfigurationURL in testConfigurationURLs {
            
            // if the decoder fails to parse a test configuration file
            // the loops will move on to the next file.
            guard var testConfiguration = try? TestConfiguration
                    .loadWithJSONDecoder(from: testConfigurationURL)
            else { continue }
            
            // `URL` to the parsed test configuration file.
            testConfiguration.file = testConfigurationURL
            
            testConfigurations.append(testConfiguration)
        }
        
        return testConfigurations
    }
}
