//
//  Assignment.swift
//  
//
//  Created by Simon Schöpke on 08.05.21.
//


/// Assignment repräsentiert eine Praktikumsaufgabe.
///
/// Eine Praktikumsaufgabe hat eine Identifikation (`id`), um eine ganz bestimmte Praktikumsaufgabe zu wählen
/// und einen Namen, um zu wissen, um welche Praktikumsaufgabe (`Assignment`) es sich handelt.
/// Im Dropdown-Menü der Testbench-Web-App zum Beispiel, werden die zu Verfügung stehenden Praktikumsaufgaben aufgelistet,
/// mit dem jeweiligen Namen (`name`) einer Praktikumsaufgabe (`Assignment`).
///
public struct Assignment: Identifiable, Codable {
    /// Kennzeichnet die Praktikumsaufgabe eindeutich.
    public let id: Int
    
    /// Name der Praktikumsaufgabe.
    public let name: String
    
    /// Relativer Pfad zur Konfigurationsdatei der entsprechenden Praktikumsaufgabe.
    let filePath: String
}
