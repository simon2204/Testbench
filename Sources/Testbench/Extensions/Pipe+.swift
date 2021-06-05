//
//  Pipe+.swift
//  
//
//  Created by Simon Schöpke on 05.06.21.
//

import Foundation

extension Pipe {
    var errorDescription: String {
        let errData = fileHandleForReading.readDataToEndOfFile()
        let description = String(data: errData, encoding: .utf8)?
            .trimmingCharacters(in: .newlines) ?? ""
        return description
    }
}
