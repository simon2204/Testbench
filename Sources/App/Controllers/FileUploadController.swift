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
    
    func boot(routes: RoutesBuilder) throws {
        let uploadRoutes = routes.grouped("api", "upload")
        uploadRoutes.post(use: uploadHandler)
    }
    
    func uploadHandler(_ request: Request) async throws -> TestResult {
        
        let unitTestData = try request.content.decode(UnitTestData.self)
        let directory = submission.appendingPathComponent(UUID().uuidString)
        try FileManager.default.createDirectory(at: directory, withIntermediateDirectories: false)
        
        try await write(files: unitTestData.files, to: directory, request: request)
        
        guard let assignmentID = Int(unitTestData.assignmentId) else {
            throw FileUploadError.notAValidID(unitTestData.assignmentId)
        }
        
        return try await performTests(assignmentId: assignmentID, submission: directory, request)
    }
    
    func write(files: [File], to directory: URL, request: Request) async throws {
        try await withThrowingTaskGroup(of: Void.self) { group in
            for file in files {
                group.addTask {
                    try await file.write(to: directory, request: request)
                }
            }
            try await group.waitForAll()
        }
    }
    
    func performTests(assignmentId: Int, submission: URL, _ request: Request) async throws -> TestResult {
        let testbench = Testbench(config: config)
        return try testbench.performTests(submission: submission, assignment: assignmentId)
    }
}

extension TestResult: Content {}

enum FileUploadError: Error {
    case notAValidID(String)
}
