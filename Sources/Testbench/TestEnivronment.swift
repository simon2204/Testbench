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
    
    init(config: Config, submission: URL) throws {
        let workingURL = config.workingDirectory
        self.destination = TestEnivronment.appendingUniquePathComponent(on: workingURL)
        
        self.submission = submission
        
        self.submissionBuild = self.destination.appendingPathComponent("submissionBuild")
        self.customBuild = self.destination.appendingPathComponent("customBuild")
        
        self.submissionDependencies = config.submissionExecutable.dependencies
        self.customDependencies = config.customTestExecutable?.dependencies
        
        self.sharedResources = config.sharedResources
        
        try setUpTestEnvironmentForSubmission()
    }
    
    private func setUpTestEnvironmentForSubmission() throws {
        
        try createTestEnvironment()
        
        try FileManager.default.copyItems(
            at: submission,
            into: submissionBuild)
        
        try FileManager.default.unzipItems(at: submissionBuild)
        
        try copySubmissionDependencies()
        
        try copyCustomDependencies()
        
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
                    withIntermediateDirectories: false)
        
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
    
    private static func appendingUniquePathComponent(on url: URL) -> URL {
        url.appendingPathComponent(UUID().uuidString)
    }
    
    private func copySubmissionDependencies() throws {
        guard let dependencies = submissionDependencies else { return }
        
        if try CFileManager.containsMainFunction(in: dependencies) {
            try CFileManager.renameMainFunctions(at: submissionBuild)
        }
        
        try FileManager
            .default
            .copyItems(at: dependencies, into: submissionBuild)
    }
    
    fileprivate func copyCustomDependencies() throws {
        guard let dependencies = customDependencies else { return }
        
        try FileManager
            .default
            .copyItems(at: dependencies, into: customBuild)
    }
    
    func customSourceFiles() throws -> [URL] {
        try CFileManager.cFiles(at: customBuild)
    }
    
    func submissionSourceFiles() throws -> [URL] {
        try CFileManager.cFiles(at: submissionBuild)
    }
    
    func getItem(withName name: String) throws -> URL {
        let item = destination.appendingPathComponent(name)
        guard FileManager.default.fileExists(atPath: item.path) else {
            throw TestEnivronmentError.noSuchItem(withName: name)
        }
        return item
    }
    
    func appendingPathCompotent(_ pathComponent: String) -> URL {
        destination.appendingPathComponent(pathComponent)
    }
    
    private func cleanUp() {
        try? FileManager.default.removeItem(at: destination)
    }
    
    deinit {
		#if !DEBUG
		cleanUp()
		#endif
    }
}

extension TestEnivronment {
    enum TestEnivronmentError: Error {
        case couldNotChangeCurrentDirectory
        case noSuchItem(withName: String)
    }
}
