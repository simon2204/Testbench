//
//  FileUploadController.swift
//  
//
//  Created by Simon Schöpke on 28.04.21.
//

import Vapor
import Testbench

struct FileUploadController: RouteCollection {
    
    let app: Application
    
    var testbenchDirectory: URL {
        URL(fileURLWithPath: app.directory.resourcesDirectory)
    }
    
    var config: URL {
        testbenchDirectory.appendingPathComponent("config.json")
    }
    
    var submission: URL {
        testbenchDirectory.appendingPathComponent("submission")
    }
    
    init(app: Application) {
        self.app = app
    }
    
    func boot(routes: RoutesBuilder) throws {
        let uploadRoutes = routes.grouped("api", "upload")
        uploadRoutes.post(use: uploadHandler)
    }
    
    private func uploadHandler(_ request: Request) async throws -> TestResult {
        
        let unitTestData = try request.content.decode(UnitTestData.self)
        
        // Erstellt einen Ordner mit einer UUID als Namen.
        let directory = submission.appendingPathComponent(UUID().uuidString)
        try FileManager.default.createDirectory(at: directory, withIntermediateDirectories: false)
        
        defer {
            try? FileManager.default.removeItem(at: directory)
        }
        
        try await write(files: unitTestData.files, to: directory, request: request)
        
        guard let assignmentID = Int(unitTestData.assignmentId) else {
            throw FileUploadError.notAValidID(unitTestData.assignmentId)
        }
        
        return try performTests(assignmentID: assignmentID, submission: directory)
    }
    
    
    /// Führt den Test auf eine Einreichung für eine bestimmte Praktikumsaufgabe aus.
    /// - Parameters:
    ///   - assignmentID: ID der Praktikumsaufgabe.
    ///   - submission: Ordner mit den Dateien, die eingereicht wurden.
    /// - Returns: Testergebnis.
    func performTests(assignmentID: Int, submission: URL) throws -> TestResult {
        let testbench = Testbench(config: config)
        return try testbench.performTests(submission: submission, assignment: assignmentID)
    }
    
    /// Schreibt alle Dateien in einen bestimmten Ordner.
    /// - Parameters:
    ///   - files: Dateien, die gespeichert werden sollen.
    ///   - directory: Ordner, in denen die Dateien gespeichert werden sollen.
    private func write(files: [File], to directory: URL, request: Request) async throws {
        try await withThrowingTaskGroup(of: Void.self) { group in
            for file in files {
                group.addTask {
                    try await file.write(to: directory, request: request)
                }
            }
            try await group.waitForAll()
        }
    }
}

extension TestResult: Content {}

enum FileUploadError: Error {
    case notAValidID(String)
}
