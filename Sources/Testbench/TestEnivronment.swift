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
        
        let workingURL = FileManager.default.temporaryDirectory
        
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
            try CFileManager.removeMainFunctions(at: submissionBuild)
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
        case noSuchItem(withName: String)
    }
}

protocol FileManagable {
    func copyItem(at src: URL, to dst: URL) throws
    func removeItem(at url: URL) throws
    func itemExists(at url: URL) -> Bool
    func creatDirectory(at url: URL) throws
    func listItems(at url: URL) -> [URL]
    func isDirectory(at url: URL) -> Bool
    func unzip(item: URL) throws
    var tempDirectory: URL { get }
}

class Directory {
    
    /// Pfad zu  diesem Breich des WorkingDirectories.
    private let url: URL
    
    /// Manager der für das Anlegen von Ordnern und Kopieren von Dateien verantwortlich ist.
    private let filemanager: FileManagable
    
    /// Enthält alle Unterordner dieses Ordners, auf die zugegriffen werden können.
    private(set) var subDirectories: [String : Directory] = [:]
    
    /// Liefert alle Items, die sich in diesem Ordner befinden, außer die Unterordner.
    var items: [URL] {
        filemanager.listItems(at: url)
            .filter { itemURL in
                itemURL.isFileURL
            }
    }
    
    init(url: URL, filemanager: FileManagable) {
        self.url = url
        self.filemanager = filemanager
    }
    
    func addDirectory(at url: URL, withName name: String? = nil) throws -> Directory {
        guard filemanager.itemExists(at: url) else {
            throw SectionError.sectionDoesNotExist(at: url)
        }
        
        let name = name ?? url.lastPathComponent
        
        guard !subDirectories.keys.contains(name) else {
            throw SectionError.alreadyContainsItem(withName: name)
        }
         
        let directory = Directory(url: url, filemanager: filemanager)
        
        subDirectories[name] = directory
        
        return directory
    }
    
    func createDirectory(withName name: String) throws  -> Directory {
        let sectionPath = url.appendingPathComponent(name)
        
        guard !subDirectories.keys.contains(name) else {
            throw SectionError.alreadyContainsItem(withName: name)
        }
        
        try filemanager.creatDirectory(at: sectionPath)
        
        let directory = Directory(url: sectionPath, filemanager: filemanager)
        
        subDirectories[name] = directory
        
        return directory
    }
    
    func copyItems(from url: URL) throws {
        try copyItems(from: url, where: { _ in true })
    }
    
    func copyItems(from url: URL, where condition: (URL) -> Bool) throws {
        let items = filemanager.listItems(at: url)
        for itemURL in items where condition(itemURL) {
            try filemanager.copyItem(at: itemURL, to: url)
        }
    }
    
    /// Entfernt den gesamten Ordner.
    func remove() throws {
        try filemanager.removeItem(at: url)
    }
    
    enum SectionError: Error {
        case alreadyContainsItem(withName: String)
        case sectionDoesNotExist(at: URL)
    }
}

class WorkingDirectory: Directory {
    
    init(filemanager: FileManagable) throws {
        let uniqueFolderName = UUID().uuidString
        let tmpDirectory = filemanager.tempDirectory
        let workingDirectoryURL = tmpDirectory.appendingPathComponent(uniqueFolderName)
        try filemanager.creatDirectory(at: workingDirectoryURL)
        super.init(url: workingDirectoryURL, filemanager: filemanager)
    }
    
    deinit {
        do { try remove() } catch { print(error) }
    }
}

class TestEnvironment2: WorkingDirectory {
    
    override init(filemanager: FileManagable) throws {
        try super.init(filemanager: filemanager)
    }
    
}
