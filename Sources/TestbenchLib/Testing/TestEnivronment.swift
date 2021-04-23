//
//  TestEnivronment.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

struct TestEnivronment {
    let destination: URL
    
    private let source: URL
    
    private var sourceTestbenchLoggingC: URL {
        source.appendingPathComponent("testbench_logging.c")
    }
    
    private var sourceTestbenchLoggingH: URL {
        source.appendingPathComponent("testbench_logging.h")
    }
    
    private var destinationTestbenchLoggingC: URL {
        destination.appendingPathComponent("testbench_logging.c")
    }
    
    private var destinationTestbenchLoggingH: URL {
        destination.appendingPathComponent("testbench_logging.h")
    }
    
    init(configuration: TestbenchConfiguration, submissionURL: URL) throws {
        self.destination = TestEnivronment.appendingUniqueTestPathComponent(on: configuration.workingDirectory)
        self.source = configuration.testSpecificationDirectory
        try setUpTestEnvironmentForSubmission(at: submissionURL)
    }
    
    private func setUpTestEnvironmentForSubmission(at url: URL) throws {
        try createTestEnvironment()
        try FileManager.default.copyItem(at: url,
                                         to: destination)
        try FileManager.default.unzipItems(at: destination)
        
        CFileManager.renameMainFunction(at: destination)
        
        try FileManager.default.copyItem(at: sourceTestbenchLoggingC,
                                         to: destinationTestbenchLoggingC)
        try FileManager.default.copyItem(at: sourceTestbenchLoggingH,
                                         to: destinationTestbenchLoggingH)
    }
    
    private func createTestEnvironment() throws {
        try FileManager
                .default
                .createDirectory(atPath: destination.path,
                                 withIntermediateDirectories: true)
    }
    
    private static func appendingUniqueTestPathComponent(on url: URL) -> URL {
        var testEnvironment = url
        testEnvironment.appendPathComponent("tests")
        testEnvironment.appendPathComponent(UUID().uuidString)
        return testEnvironment
    }
    
    func cleanUp() {
        try? FileManager.default.removeItem(at: destination)
    }
}
