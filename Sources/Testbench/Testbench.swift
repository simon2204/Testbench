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
public struct Testbench {
    private let testCaseManager: TestCaseManager
    
    /// Erstellt eine Testbench Instance mit Hilfe einer Konfigurationsdatei.
    ///
    /// Der Pfad zur Konfigurationsdatei erfolgt mittels `URL`.
    /// ```swift
    /// let pathToConfigFile = "/Users/Simon/Desktop/TestbenchDirectories/config.json"
    /// let configFileURL = URL(fileURLWithPath: pathToConfigFile)
    /// let testbench = Testbench(config: configFileURL)
    /// ```
    ///
    /// Die Konfigurationsdatei ist im Format von JSON zu definieren.
    /// ```json
    ///{
    ///    "workingDirectory": "/Users/Simon/Desktop/TestbenchDirectories/working_directory",
    ///    "testSpecificationDirectory": "/Users/Simon/Desktop/TestbenchDirectories/test_specification",
    ///    "compiler": "/usr/bin/gcc",
    ///    "buildOptions": ["-O", "-Wall"],
    ///    "assignments": [
    ///        {
    ///            "id": 1,
    ///            "name": "Ulam",
    ///            "filePath": "blatt01_Ulam/test-configuration.json"
    ///        },
    ///        {
    ///            "id": 2,
    ///            "name": "Matrix",
    ///            "filePath": "blatt02_Matrix/test-configuration.json"
    ///        },
    ///        {
    ///            "id": 3,
    ///            "name": "GameOfLife",
    ///            "filePath": "blatt03_GameOfLife/test-configuration.json"
    ///        },
    ///        {
    ///            "id": 4,
    ///            "name": "Huffman Module",
    ///            "filePath": "blatt04_HuffmanModule/test-configuration.json"
    ///        },
    ///        {
    ///            "id": 5,
    ///            "name": "Bocksatzformatierung",
    ///            "filePath": "blatt05_Blocksatzformatierung/test-configuration.json"
    ///        },
    ///        {
    ///            "id": 6,
    ///            "name": "Huffman Kommandozeile",
    ///            "filePath": "blatt06_HuffmanKommandozeile/test-configuration.json"
    ///        },
    ///        {
    ///            "id": 7,
    ///            "name": "Binärer Heap",
    ///            "filePath": "blatt07_BinaererHeap/test-configuration.json"
    ///        },
    ///        {
    ///            "id": 8,
    ///            "name": "Binärbaum",
    ///            "filePath": "blatt08_Binaerbaum/test-configuration.json"
    ///        },
    ///        {
    ///            "id": 9,
    ///            "name": "Huffman",
    ///            "filePath": "blatt09_Huffman/test-configuration.json"
    ///        }
    ///    ]
    ///}
    /// ```
    /// Das `workingDirectory` gibt den Pfad zu einem leeren Ordner an, worin die Testbench arbeiten kann.
    /// Dort wird aus dem Quelltext der Einreichungen zu den Praktikumsaufgaben und dem Quelltext,
    /// der benötigt wird, um die entsprechende Praktikumsaufgabe zu testen, ein Programm erzeugt,
    /// welches eine Logdatei erzeugt, in die die entsprechenden Auswertungen der Testfälle geschrieben werden.
    /// ```json
    /// "workingDirectory": "/Users/Simon/Desktop/TestbenchDirectories/working_directory"
    /// ```
    ///
    /// Das `testSpecificationDirectory` gibt den Pfad zum Ordner an,
    /// der die Spezifikationen aller Praktikumsaufgaben enthält,
    /// die getestet werden können.
    /// In dem jeweiligen Ordner einer Spezifikation zu einer Pratikumsaufgabe,
    /// befindet sich mindestens eine Konfigurationsdatei zu dem Testen der Praktikumsaufgabe
    /// und weitere Dateien, die zum Testen benötigt werden.
    /// ```json
    /// "testSpecificationDirectory": "/Users/Simon/Desktop/TestbenchDirectories/test_specification"
    /// ```
    ///
    /// Pfad zum C-Compiler, welcher verwendet werden soll.
    /// ```json
    /// "compiler": "/usr/bin/gcc"
    /// ```
    ///
    /// Die `buildOptions` enthalten die einzelnen Kommandozeilenargumente, die dem `compiler` übergeben werden.
    /// Die `buildOptions` werden für jede Kompilierung der verwendeten Quelltexte übergeben.
    /// In der jeweiligen Konfigurationsdatei einer Praktikumsaufgabe kann diese Option überschrieben werden
    /// und dem Compiler andere oder auch keine `buildOptions` übergeben werden.
    /// ```json
    /// "buildOptions": ["-O", "-Wall"]
    /// ```
    ///
    /// Die `assignments` enthalten die Praktikumsaufgaben, die getestet werden können,
    /// die `id` mit der sich eine Praktikumsaufgabe eindeutich zuordnen lässt,
    /// der `name` der Praktikumsaufgabe und
    /// der Pfad zur Konfigurationsdatei der Praktikumsaufgabe relativ zum Pfad des `testSpecificationDirectory`.
    /// Ist der Pfad zum `testSpecificationDirectory`
    /// ```
    /// /Users/Simon/Desktop/TestbenchDirectories/test_specification
    /// ```
    /// und der `filePath` zur Konfigurationsdatei der Ulam-Praktikumsaufgabe
    /// ```
    /// blatt01_Ulam/test-configuration.json
    /// ```
    /// , dann lautet der absolute Pfad zur
    /// Konfigurationsdatei der Ulam-Praktikumsaufgabe
    /// ```
    /// /Users/Simon/Desktop/TestbenchDirectories/test_specification/blatt01_Ulam/test-configuration.json
    /// ```
    ///
    /// ```json
    /// "assignments": [
    ///    {
    ///        "id": 1,
    ///        "name": "Ulam",
    ///        "filePath": "blatt01_Ulam/test-configuration.json"
    ///    }
    /// ]
    /// ```
    ///
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
    ///   - id: Die Praktikumsaufgabe mit der entsprechenden ID, welche ausgewertet werden soll.
    /// - Throws: Error bei einer `id`, die zu der es keine zugehörige Praktikumsaufgabe gibt.
    /// - Returns: Auswertung zu der Praktikumsaufgabe.
    public func performTests(submission: URL, assignment id: Int) throws -> TestResult {
        let testCase = try testCaseManager.testCase(forAssignment: id)
        return try testCaseManager.performTests(submission: submission, testcase: testCase)
    }
}
