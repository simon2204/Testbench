//
//  TestConfiguration.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

public struct TestConfiguration: Decodable {
    let name: String
    let assignmentId: String
    let type: TestType
    let tasks: [Task]
    let pointsNeeded: Int
    let timeoutInMS: Int
    
    enum TestType: String, Decodable {
        case unitTest, commandLineTest
    }
}
