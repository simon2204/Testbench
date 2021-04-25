//
//  ObtainableFromDirectory.swift
//  
//
//  Created by Simon Schöpke on 24.04.21.
//

import Foundation

public protocol ObtainableFromDirectory: Decodable {
    var file: URL? { get set }
    init(directory: URL, fileName: String) throws
}

extension ObtainableFromDirectory {
    public init(directory: URL, fileName: String) throws {
        
        guard let file = FileManager
            .default
            .firstFile(named: fileName, at: directory)
        else {
            throw ObtainableError.fileNotFound(named: fileName)
        }
        
        self = try Self.loadWithJSONDecoder(from: file)
        self.file = file
    }
}

public enum ObtainableError: Error {
    case fileNotFound(named: String)
}
