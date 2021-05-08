//
//  GlobalConfig.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

struct GlobalConfig: Codable {
    let workingDirectory: String
    let testSpecificationDirectory: String
    let compiler: String
    let buildOptions: [String]?
    let assignments: [Assignment]
}
