//
//  File.swift
//  
//
//  Created by Simon Schöpke on 30.01.22.
//

import Vapor

extension File {
    /// Schreibt die Datei in einen Ordner.
    /// - Parameters:
    ///   - directory: Order, in dem die Datei gespeichert werden soll.
    func write(to directory: URL, request: Request) async throws {
        let path = directory.appendingPathComponent(filename).path
        return try await request.fileio.writeFile(data, at: path)
    }
}
