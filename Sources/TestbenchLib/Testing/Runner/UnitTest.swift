//
//  UnitTest.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

public final class UnitTest {
    private let testbenchConfig: TestbenchConfiguration
    
    public init(config: TestbenchConfiguration) {
        self.testbenchConfig = config
    }
    
    public func performTestForSubmission(at url: URL, withConfiguration testConfiguration: TestConfiguration) throws -> TestResult? {
        
        do {
            let testEnvironment = try TestEnivronment(configuration: testbenchConfig,
                                                      submissionURL: url)
            // TODO: Perform Testing...
            
            let buildOptions: CCompiler.BuildOptions = [.compilationTimeOptimization,
                                                        .enableAllWarnings,
                                                        .defineTestbenchMacro]
            
            let compiler = CCompiler(source: url,
                                     destination: testEnvironment.destination,
                                     compiler: .gcc,
                                     options: buildOptions)
            
            let buildTime = try compiler.build()
            
            let timeoutInMilliseconds = testConfiguration.timeoutInMS
            
            let runTimeInSeconds = try compiler.run(withDeadline: .milliseconds(timeoutInMilliseconds))
            
            
            let logfileURL = testEnvironment.destination.appendingPathComponent("testresult.csv")
            let result = try TestResult.fromLogfile(at: logfileURL, testconfig: testConfiguration)
            
            testEnvironment.cleanUp()
            
            return result
        } catch {
            print(error)
        }
        
        return nil
    }
}
