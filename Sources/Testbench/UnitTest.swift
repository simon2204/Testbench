//
//  UnitTest.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

public struct UnitTest {
    let config: TestCase
    let submission: URL
    
    public func performTests() throws -> TestResult {
        let testEvironment = try TestEnivronment(config: config, submissionURL: submission)
        
        defer { testEvironment.cleanUp() }
        
        let runTime: TimeInterval
    
        if let customExecutable = config.customTestExecutable {
            let _ = try buildSubmissionExecutable(testEvironment)
            try buildCustomExecutable(testEvironment, customExecutable)
            runTime = try runCustomTasks(testEvironment)
        } else {
            runTime = try runSubmissionExecutable(testEvironment)
        }
        
        let logfileURL = testEvironment
            .destination
            .appendingPathComponent("ppr_tb_asserts_json.log")
        
        var result = try TestResult.fromLogfile(at: logfileURL)
        result.runTime = runTime

        return result
    }
    
    private func runSubmissionExecutable(_ testEvironment: TestEnivronment) throws -> TimeInterval {
        let compiler = Compiler(config.compiler)
        
        let processName = try buildSubmissionExecutable(testEvironment)
        
        let runTime = try compiler.run(
            process: processName,
            arguments: [],
            deadline: config.timeout)
        
        return runTime
    }
    
    private func runCustomTasks(_ testEvironment: TestEnivronment) throws -> TimeInterval  {
        try config.tasks.reduce(0) { runtime, task in
            let compiler = Compiler(config.compiler)
            
            let processName = testEvironment
                .destination
                .appendingPathComponent(task.executableName)
            
            return try compiler.run(
                process: processName,
                arguments: task.commandLineArguments,
                deadline: config.timeout) + runtime
        }
    }
    
    private func buildSubmissionExecutable(
        _ testEvironment: TestEnivronment) throws -> URL
    {
        let submissionDestination = testEvironment
            .destination
            .appendingPathComponent(config.submissionExecutable.name)
        let submissionCompiler = Compiler(config.compiler)
        let submissionBuildFiles = try CFileManager.cFiles(at: testEvironment.submissionBuild)
        let _ = try submissionCompiler.build(
            sourceFiles: submissionBuildFiles,
            destination: submissionDestination,
            options: config.submissionExecutable.buildOptions)
        
        return submissionDestination
    }
    
    
    private func buildCustomExecutable(
        _ testEvironment: TestEnivronment,
        _ customExecutable: TestCase.Executable) throws
    {
        let customDestination = testEvironment
            .destination
            .appendingPathComponent(customExecutable.name)
        let customCompiler = Compiler(config.compiler)
        let customBuildFiles = try CFileManager.cFiles(at: testEvironment.customBuild)
        let _ = try customCompiler.build(
            sourceFiles: customBuildFiles,
            destination: customDestination,
            options: customExecutable.buildOptions)
    }
    
    enum TestError: Error, Equatable {
        case testDirectoryNotFound
        case buildTimeExceeded
        case runTimeExceeded
    }
}
