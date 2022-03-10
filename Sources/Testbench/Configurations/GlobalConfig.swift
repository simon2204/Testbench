//
//  GlobalConfig.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

/// Globale Konfiguration der Testbench.
///
/// Mit Hilfe dieses structs wird die globale Konfigurationsdatei dekodiert.
struct GlobalConfig: Codable {
    /// Ordner, in dem die Testdateien und Konfiguration liegen.
    let testSpecificationDirectory: String
    
    /// Pfad zum Kompiler auf dem System.
    let compiler: String
    
    /// Optionen die zum Kompilieren verwendet werden.
    let buildOptions: [String]?
    
    /// Aufgaben, die die Testbench auswerten kann.
    let assignments: [Assignment]
}
