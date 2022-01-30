//
//  UnitTestData.swift
//  
//
//  Created by Simon Schöpke on 28.04.21.
//

import Vapor

struct UnitTestData: Content {
    let assignmentId: String
    let files: [File]
}

extension File {
    func write(to directory: URL, request: Request) async throws {
        let path = directory.appendingPathComponent(filename).path
        return try await request.fileio.writeFile(data, at: path)
    }
}
