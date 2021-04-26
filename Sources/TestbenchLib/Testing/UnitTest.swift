//
//  UnitTest.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

public struct UnitTest {
    private let testbenchConfig: TestbenchConfiguration
    
    public init (testbenchConfiguration: TestbenchConfiguration) {
        self.testbenchConfig = testbenchConfiguration
    }
    
    public func performTestForSubmission(at url: URL,
                                         withConfiguration testConfiguration: TestConfiguration) throws -> TestResult {
        guard let testDirectory = testConfiguration.testDirectory else { throw TestError.testDirectoryNotFound }
        
        let workingDirectory = URL(fileURLWithPath: testbenchConfig.workingDirectory)
        let testSpecificationDirectory = URL(fileURLWithPath: testbenchConfig.testSpecificationDirectory)
        
        let timeoutInMilliseconds = testConfiguration.timeoutInMs
        
        let testEnvironment = try TestEnivronment(workingURL: workingDirectory,
                                                  testSpecificationURL: testSpecificationDirectory,
                                                  testURL: testDirectory,
                                                  submissionURL: url)
        defer {
            testEnvironment.cleanUp()
        }
        
        let outputFile = testEnvironment
            .destination
            .appendingPathComponent("test_executable")
        
        let buildOptions: CCompiler.BuildOptions = [.compilationTimeOptimization,
                                                    .enableAllWarnings,
                                                    .defineTestbenchMacro]

        let compiler = CCompiler(source: testEnvironment.destination,
                                 destination: outputFile,
                                 compiler: .gcc,
                                 options: buildOptions)
        
        // TODO: Make use of buildTime and runTime.
        let buildTime = try compiler.build()
        let runTime = try compiler.run(withDeadline: .milliseconds(timeoutInMilliseconds))

        let logfileURL = testEnvironment.destination.appendingPathComponent("testresult.csv")
        let result = try TestResult.fromLogfile(at: logfileURL, testconfig: testConfiguration)

        return result
    }
    
    enum TestError: Error, Equatable {
        case testDirectoryNotFound
        case buildTimeExceeded
        case runTimeExceeded
    }
}
