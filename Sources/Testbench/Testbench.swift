//
//  Testbench.swift
//  
//
//  Created by Simon Schöpke on 26.04.21.
//

import Foundation

/// Teste Lösungen zu Praktikumsaufgaben der Prozeduralen Programmierung in C.
///
/// Die Testbench wertet die eingereichte Lösung zu einer Praktikumsaufgabe der Prozeduralen Programmierung in C,
/// mit Hilfe von verschiedenen Testfällen pro Praktikumsaufgabe aus.
///
/// Um ein Testbench-Objekt zu erstellen wird eine Konfigurationsdatei benötigt.
/// Der Pfad zur Konfigurationsdatei erfolgt mittels `URL`.
/// ```swift
/// let pathToConfigFile = "/Users/Simon/Desktop/TestbenchDirectories/config.json"
/// let configFileURL = URL(fileURLWithPath: pathToConfigFile)
/// let testbench = Testbench(config: configFileURL)
/// ```
///
public struct Testbench {
    private let testCaseManager: TestCaseManager
    
    /// Erstellt eine Testbench Instance mit Hilfe einer Konfigurationsdatei.
    /// - Parameter config: Pfad zur Konfigurationsdatei.
    public init(config: URL) {
        testCaseManager = TestCaseManager(config: config)
    }
    
    /// Findet alle zur Verfügung stehenden Praktikumsaufgaben, dessen Lösungen ausgewertet werden können.
    /// - Returns: Liefert alle Praktikumsaufgaben die gefunden wurden.
    public func availableAssignments() throws -> [Assignment] {
        try testCaseManager.availableAssignments()
    }
    
    /// Wertet die Einreichung einer Praktikumsaufgabe aus.
    /// - Parameters:
    ///   - submission: Pfad zum Ordner der Einreichung.
    ///   - id: Die Praktikumsaufgabe mit der entsprechenden `id`, welche ausgewertet werden soll.
    /// - Throws: TestCaseError.assignmentNotFound(forID:) bei einer `id`,  zu der es keine zugehörige Praktikumsaufgabe gibt.
    /// - Returns: Auswertung zu der Praktikumsaufgabe.
    public func performTests(submission: URL, assignment id: Int) throws -> TestResult {
        let testCase = try testCaseManager.testCase(forAssignment: id)
        return try testCaseManager.performTests(submission: submission, testcase: testCase)
    }
}
