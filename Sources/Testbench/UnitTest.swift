//
//  UnitTest.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

struct UnitTest {
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
    
    func performTests() throws -> TestResult {
        var result = TestResult()
        var runTime: TimeInterval?
        var errorMsg: String?
        
        do {
            runTime = try executeTests()
        } catch let error as DescriptiveError {
            errorMsg = error.description
        }
        
        if let logfile = try? testEnvironment.getItem(withName: UnitTest.assertsJsonLog) {
            result = try TestResult(from: logfile)
        }
        
        result.runTime = runTime
        result.errorMsg = errorMsg

        return result
    }
    
    private func executeTests() throws -> TimeInterval {
        let executable = try buildSubmissionExecutable()
        let canBuildCostumExecutable = try buildCustomExecutable()
        
        if canBuildCostumExecutable {
            return try runCustomTasks()
        } else {
            return try runSubmissionExecutable(executable)
        }
    }
    
    private func runSubmissionExecutable(_ executable: Executable) throws -> TimeInterval {
        return try executable.run(arguments: [], deadline: config.timeout)
    }
    
    private func runCustomTasks() throws -> TimeInterval {
        let timeNeeded = try config.tasks.reduce(0.0) { totalRunTime, task in
            let currentRunTime = try runCustomTask(task)
            return currentRunTime + totalRunTime
        }
        return timeNeeded
    }
    
    private func runCustomTask(_ task: TestCase.Process) throws -> TimeInterval {
        let process = try self.testEnvironment.getItem(withName: task.executableName)
        let executable = Executable(url: process)
        return try executable.run(arguments: task.commandLineArguments, deadline: config.timeout)
    }
    
    /// Build the submission executable.
    /// - Returns: `URL` to the executable.
    private func buildSubmissionExecutable() throws -> Executable {
        let executable = config.submissionExecutable
        let sourceFiles = try testEnvironment.submissionSourceFiles()
        return try buildExecutable(executable, from: sourceFiles)
    }
    
    /// Builds the constum executable.
    /// - Returns: `true`, if a custom executable was specified and `false` otherwise.
    private func buildCustomExecutable() throws -> Bool {
        guard let executable = config.customTestExecutable else { return false }
        let sourceFiles = try testEnvironment.customSourceFiles()
        let _ = try buildExecutable(executable, from: sourceFiles)
        return true
    }
    
    private func buildExecutable(_ executable: TestCase.Executable, from files: [URL]) throws -> Executable {
        let destination = testEnvironment.appendingPathCompotent(executable.name)
        return try compiler.build(
            sourceFiles: files,
            destination: destination,
            options: executable.buildOptions)
    }
}
