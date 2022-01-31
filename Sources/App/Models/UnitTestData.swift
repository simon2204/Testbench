//
//  UnitTestData.swift
//  
//
//  Created by Simon Schöpke on 28.04.21.
//

import Vapor

/// Dateien, die zu einer Praktikumsaufgabe gehören.
struct UnitTestData: Content {
    /// ID der Praktikumsaufgabe.
    let assignmentId: String
    /// Dateien mit der Lösung der Praktikumsaufgabe.
    let files: [File]
}


