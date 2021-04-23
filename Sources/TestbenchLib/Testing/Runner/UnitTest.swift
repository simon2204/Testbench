//
//  UnitTest.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

final class UnitTest {
    private let testbenchConfig: TestbenchConfiguration
    
    init(config: TestbenchConfiguration) {
        self.testbenchConfig = config
    }
    
    func performTestForSubmission(at url: URL, withConfiguration testConfiguration: TestConfiguration) throws {
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
            
            // TODO: Parse logfile
            
            
            
            testEnvironment.cleanUp()
        } catch {
            print(error)
        }
    }
}
