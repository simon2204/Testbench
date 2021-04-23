//
//  File.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

extension Decodable {
    public static func loadWithJSONDecoder(from url: URL) throws -> Self {
        let decoder = JSONDecoder()
        let configData = try Data(contentsOf: url)
        return try decoder.decode(Self.self, from: configData)
    }
}
