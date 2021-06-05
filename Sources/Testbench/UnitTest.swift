//
//  UnitTest.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

public struct UnitTest {
    typealias ProcessResult = CProcessManager.ProcessResult
    
    private static let assertsJsonLog = "ppr_tb_asserts_json.log"
    
    private let config: TestCase
    private let submission: URL
    private let processManager: CProcessManager
    private let testEnvironment: TestEnivronment
    
    init(config: TestCase, submission: URL) throws {
        self.config = config
        self.submission = submission
        self.processManager = CProcessManager(config.compiler)
        self.testEnvironment = try TestEnivronment(config: config, submission: submission)
    }
    
    public func performTests() throws -> TestResult {
        
        var result = TestResult()
        var runTime: TimeInterval?
        var errorMsg: String?
        
        let processResult = try executeTests()
        
        switch processResult {
        case .timeNeeded(seconds: let seconds): runTime = seconds
        case .error(let error): errorMsg = error.description
        }
        
        if let logfile = try? testEnvironment.getItem(withName: UnitTest.assertsJsonLog) {
            result = try TestResult(from: logfile)
        }
        
        result.runTime = runTime
        result.errorMsg = errorMsg
        result.name = config.label

        return result
    }
    
    private func executeTests() throws -> ProcessResult {
        let canBuildCustomExecutable = try buildCustomExecutable()
        
        if canBuildCustomExecutable {
            return try runCustomTasks()
        } else {
            return try runSubmissionExecutable()
        }
    }
    
    private func runSubmissionExecutable() throws -> ProcessResult {
        let executable = try buildSubmissionExecutable()
        
        let runTime = try processManager.run(
            process: executable,
            arguments: [],
            deadline: config.timeout)
        
        return runTime
    }
    
    private func runCustomTasks() throws -> ProcessResult {
        let _ = try buildSubmissionExecutable()
        let zeroBuildTime = ProcessResult.timeNeeded(seconds: 0)
        
        let processResult = try config.tasks.reduce(zeroBuildTime) { partialResult, task in
            let result = try runCustomTask(task)
            
            if case let .timeNeeded(seconds: runTime) = result,
               case let .timeNeeded(seconds: partialRuntime) = partialResult
            {
                return .timeNeeded(seconds: runTime + partialRuntime)
            }
            
            return partialResult
        }
        
        return processResult
    }
    
    private func runCustomTask(_ task: TestCase.Process) throws -> ProcessResult {
        let process = try self.testEnvironment
            .getItem(withName: task.executableName)
        
        return try processManager.run(
            process: process,
            arguments: task.commandLineArguments,
            deadline: config.timeout)
    }
    
    
    /// Build the submission executable.
    /// - Returns: `URL` to the executable.
    private func buildSubmissionExecutable() throws -> URL {
        let executable = config.submissionExecutable
        let sourceFiles = try testEnvironment.submissionSourceFiles()
        return try buildExecutable(executable, fromSourceFiles: sourceFiles)
    }
    
    /// Builds the constum executable.
    /// - Returns: true, if a custom executable was specified and false otherwise.
    private func buildCustomExecutable() throws -> Bool {
        guard let executable = config.customTestExecutable else { return false }
        let sourceFiles = try testEnvironment.customSourceFiles()
        let _ = try buildExecutable(executable, fromSourceFiles: sourceFiles)
        return true
    }
    
    private func buildExecutable(
        _ executable: TestCase.Executable,
        fromSourceFiles files: [URL])
    throws -> URL
    {
        let destination = testEnvironment
            .appendingPathCompotent(executable.name)
        
        let _ = try processManager.build(
            sourceFiles: files,
            destination: destination,
            options: executable.buildOptions)
        
        return destination
    }
}
