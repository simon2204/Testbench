//
//  UnitTest.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

public struct UnitTest {
    private static let assertsJsonLog = "ppr_tb_asserts_json.log"
    
    private let config: TestCase
    private let submission: URL
    private let compiler: Compiler
    private let testEnvironment: TestEnivronment
    
    init(config: TestCase, submission: URL) throws {
        self.config = config
        self.submission = submission
        self.compiler = Compiler(config.compiler)
        self.testEnvironment = try TestEnivronment(config: config, submission: submission)
    }
    
    public func performTests() throws -> TestResult {
        let runTime = try executeTests()
        let logfile = testEnvironment.getItem(withName: UnitTest.assertsJsonLog)
        
        var result = try TestResult.fromLogfile(logfile)
        result.runTime = runTime

        return result
    }
    
    private func executeTests() throws -> TimeInterval {
        let canBuildCustomExecutable = try buildCustomExecutable()
        
        if canBuildCustomExecutable {
            return try runCustomTasks()
        } else {
            return try runSubmissionExecutable()
        }
    }
    
    private func runSubmissionExecutable() throws -> TimeInterval {
        let executable = try buildSubmissionExecutable()
        
        let runTime = try compiler.run(
            process: executable,
            arguments: [],
            deadline: config.timeout)
        
        return runTime
    }
    
    private func runCustomTasks() throws -> TimeInterval {
        let _ = try buildSubmissionExecutable()
        
        let totalRunTime = try config.tasks.reduce(0.0) { partialRunTime, task in
            let runTime = try runCustomTask(task)
            return runTime + partialRunTime
        }
        
        return totalRunTime
    }
    
    private func runCustomTask(_ task: TestCase.Process) throws -> TimeInterval {
        let process = self.testEnvironment
            .getItem(withName: task.executableName)
        
        return try compiler.run(
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
    
    private func buildExecutable(_ executable: TestCase.Executable,
                                 fromSourceFiles files: [URL]) throws -> URL
    {
        let destination = testEnvironment
            .getItem(withName: executable.name)
        
        let _ = try compiler.build(
            sourceFiles: files,
            destination: destination,
            options: executable.buildOptions)
        
        return destination
    }
}
