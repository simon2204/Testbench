//
//  TestEnivronment.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

struct TestEnivronment {
    let destination: URL
    private let test: URL
    private let submission: URL
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
    
    init(workingURL: URL, testSpecificationURL: URL, testURL: URL, submissionURL: URL) throws {
        self.destination = TestEnivronment.appendingUniqueTestPathComponent(on: workingURL)
        self.test = testURL
        self.submission = submissionURL
        self.source = testSpecificationURL
        try setUpTestEnvironmentForSubmission()
        FileManager.default.changeCurrentDirectoryPath(destination.path)
    }
    
    private func setUpTestEnvironmentForSubmission() throws {
        do {
            try createTestEnvironment()
            
            try FileManager.default.copyItems(at: submission,
                                              into: destination)
            try FileManager.default.unzipItems(at: destination)

            try CFileManager.renameMainFunctions(at: destination)

            try FileManager.default.copyItems(at: test, into: destination)
            try FileManager.default.copyItem(at: sourceTestbenchLoggingC,
                                             to: destinationTestbenchLoggingC)
            try FileManager.default.copyItem(at: sourceTestbenchLoggingH,
                                             to: destinationTestbenchLoggingH)
        } catch {
            self.cleanUp()
            throw error
        }
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

