//
//  TestEnivronment.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

final class TestEnivronment {
    private let submissionBuild: URL
    private let customBuild: URL
    private let destination: URL
    private let submission: URL
    private let submissionDependencies: URL?
    private let customDependencies: URL?
    private let sharedResources: URL?
    
    init(config: TestCase, submission: URL) throws {
        let workingURL = config.workingDirectory
        self.destination = TestEnivronment.appendingUniqueTestPathComponent(on: workingURL)
        
        self.submission = submission
        
        self.submissionBuild = self.destination.appendingPathComponent("submissionBuild")
        self.customBuild = self.destination.appendingPathComponent("customBuild")
        
        self.submissionDependencies = config.submissionExecutable.dependencies
        self.customDependencies = config.customTestExecutable?.dependencies
        
        self.sharedResources = config.sharedResources
        
        try setUpTestEnvironmentForSubmission()
        
        guard FileManager.default.changeCurrentDirectoryPath(destination.path) else {
            throw TestEnivronmentError.couldNotChangeCurrentDirectory
        }
    }
    
    private func setUpTestEnvironmentForSubmission() throws {
        
        try createTestEnvironment()
        
        try FileManager.default.copyItems(
            at: submission,
            into: submissionBuild)
        
        try FileManager.default.unzipItems(at: submissionBuild)
        
        if let dependencies = self.submissionDependencies {
            if try CFileManager.containsMainFunction(in: dependencies) {
                try CFileManager.renameMainFunctions(at: submissionBuild)
            }
            try FileManager.default.copyItems(
                at: dependencies,
                into: submissionBuild)
        }
        
        if let dependencies = self.customDependencies {
            try FileManager.default.copyItems(at: dependencies,
                                              into: customBuild)
        }
        
        if let sharedResources = self.sharedResources {
            try FileManager.default.copyItems(
                at: sharedResources,
                into: destination)
        }
    }
    
    private func createTestEnvironment() throws {
        try FileManager
                .default
                .createDirectory(
                    atPath: destination.path,
                    withIntermediateDirectories: true)
        try FileManager
                .default
                .createDirectory(
                    atPath: submissionBuild.path,
                    withIntermediateDirectories: false)
        try FileManager
                .default
                .createDirectory(
                    atPath: customBuild.path,
                    withIntermediateDirectories: false)
    }
    
    private static func appendingUniqueTestPathComponent(on url: URL) -> URL {
        var testEnvironment = url
        testEnvironment.appendPathComponent("tests")
        testEnvironment.appendPathComponent(UUID().uuidString)
        return testEnvironment
    }
    
    func customSourceFiles() throws -> [URL] {
        try CFileManager.cFiles(at: customBuild)
    }
    
    func submissionSourceFiles() throws -> [URL] {
        try CFileManager.cFiles(at: submission)
    }
    
    func urlToItem(withName name: String) -> URL {
        self.destination.appendingPathComponent(name)
    }
    
    private func cleanUp() {
        try? FileManager.default.removeItem(at: destination)
    }
    
    deinit {
//        cleanUp()
    }
}

extension TestEnivronment {
    enum TestEnivronmentError: Error {
        case couldNotChangeCurrentDirectory
    }
}
