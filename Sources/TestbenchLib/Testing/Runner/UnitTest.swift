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
    
    func performTestForSubmission(at url: URL, withConfiguration testConfiguration: TestConfiguration) {
        do {
            let testEnvironment = try TestEnivronment(configuration: testbenchConfig,
                                                      submissionURL: url)
            
            // TODO: Perform Testing...
            
            testEnvironment.cleanUp()
        } catch {
            print(error)
        }
    }
}
