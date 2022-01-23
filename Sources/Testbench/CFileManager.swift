//
//  CFileManager.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

struct CFileManager {
    
    /// Signatur der main-Funktion in C.
    private static let mainFuncPattern = "int\\s+main\\s*\\("
    
    /// Gültige Signatur einer Funktion in C, welche nicht der Signatur der main-Funktion entspricht.
    private static let invalidMainFuncName = "int ____main("
    
    private static let mainFuncRegex =
        try! NSRegularExpression(pattern: CFileManager.mainFuncPattern)
    
    /// Führt eine flache Suche nach allen C-Dateien durch und entfernt alle main-Funktionen.
    ///
    /// Die main-Funktionen werden entfernt,
    /// damit diese beim Start eines Programmes nicht mehr ausgeführt werden.
    ///
    /// - Parameter url: Ordner in der die main-Funktionen entfernt werden sollen.
    static func renameMainFunctions(at url: URL) throws {
        
        // Liste von URLs zu allen C-Dateien, die sich im Ordner befinden.
        let cFileURLs = try cFiles(at: url)
        
        // Entfernt aus allen Datein, die main-Funktion, falls vorhanden.
        for cFileURL in cFileURLs {
            
            // Inhalt der Datei, welche eine main-Funktion beinhaltet.
            let content = try String(contentsOf: cFileURL, encoding: .ascii)
            
            // Inhalt der Datei, bei der die main-Funktion entfernt worden ist.
            let replacement = content.replaceContent(
                matching: CFileManager.mainFuncRegex,
                withTemplate: CFileManager.invalidMainFuncName)
            
            // Überschreibt den Inhalt der Datei, mit dem Inhalt,
            // bei dem die main-Funktion entfernt worden ist.
            try replacement.write(
                to: cFileURL,
                atomically: true,
                encoding: .utf8)
        }
    }
    
    /// Liefert alle Dateien mit der Endung ".c".
    ///
    /// Die Funktion führt nur eine flache Suche durch,
    /// somit werden keine weiteren Datein geliefert,
    /// die sich in weiteren Unterordnern befinden.
    ///
    /// - Parameter url: URL des Ordners, in der sich die Dateien befinden.
    /// - Returns: URLs zu den C-Dateien.
    static func cFiles(at url: URL) throws -> [URL] {
        let urls = try FileManager.default.items(at: url)
        return CFileManager.filterCFiles(from: urls)
    }
    
    /// Filtert aus den übergebenen URLs nur die C-Dateien heraus.
    /// - Parameter urls: URLs der verschiedenen Dateien.
    /// - Returns: URLs zu den C-Dateien.
    static func filterCFiles(from urls: [URL]) -> [URL] {
        return urls.filter(CFileManager.isCFile)
    }
    
    /// Überprüft, ob die übergebene Datei eine C-Datei ist.
    /// - Parameter url: URL zu der zu überprüfenden Datei.
    /// - Returns: `true`, wenn die Datei eine C-Datei ist.
    static func isCFile(at url: URL) -> Bool {
        return url.pathExtension == "c"
    }
    
    /// Überprüft, ob sich im Ordner eine Datei befindet, die eine main-Funktion enthält.
    /// - Parameter directory: URL zum Ordner, der überprüft werden soll.
    /// - Returns: `true`, wenn eine main-Funktion gefunden wurde.
    static func containsMainFunction(in directory: URL) throws -> Bool {
        let cFiles = try cFiles(at: directory)
        return try containsMainFunction(at: cFiles)
    }
    
    /// Überprüft, ob sich eine main-Funktion in einer der übergebenen Dateien befindet.
    /// - Parameter urls: URLs zu den Dateien, in der sich eine main-Funktion befinden könnte.
    /// - Returns: `true`, wenn eine main-Funktion in einer der Dateien gefunden wurde.
    static func containsMainFunction(at urls: [URL]) throws -> Bool {
        for url in urls {
            if try containsMainFunction(at: url) { return true }
        }
        return false
    }
    
    /// Überprüft, ob sich eine main-Funktion in der Datei, an der übergebenen `URL` befindet.
    /// - Parameter url: URL zur Datei, in der sich eine main-Funktion befinden könnte.
    /// - Returns: `true`, wenn eine main-Funktion gefunden wurde.
    static func containsMainFunction(at url: URL) throws -> Bool {
        let sourceCode = try String(contentsOf: url)
        return sourceCode.contains(expression: mainFuncRegex)
    }
}

