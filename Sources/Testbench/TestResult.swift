//
//  TestResult.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

/// Ergebnis der Auswertung  zu einer Praktikumsaufgabe.
///
/// Die Auswertung beinhaltet alle Ergebnisse zu den verschiedenen Testfällen, die ausgeführt wurden.
/// Sowie der Ausführungsdauer, eine eventuelle Fehlermeldung und das Datum,
/// welches den Start der Ausführung der Testfälle kennzeichnet.
public struct TestResult: Codable {
    
    /// Name der Praktikumsaufgabe.
    public var assignmentName: String
    
    /// Anzahl an Testfällen insgesamt.
    public var totalTestcases: Int
    
    /// Die Zeit, die benötigt wurde, um alle Testfälle der Praktikumsaufgabe auszuführen.
    /// Enthält `nil`, wenn es vorzeitig zu einem Fehler in der Praktikumsaufgabe gab,
    /// der dazu geführt hat den Test zu unterbrechen.
    public var runTime: TimeInterval?
    
    /// Die Fehlermeldung, welche Aufschluss darüber geben soll,
    /// warum es zu einem vorzeitigen Beenden des Tests gekommen ist.
    /// Enthält `nil`, wenn alle Testfälle durchlaufen werden konnten.
    public var errorMsg: String?
    
    /// Beginn der Ausführung der Testfälle.
    public var date = Date()
    
    /// Enthällt alle Auswertungen, für die Testfälle, die ausgeführt wurden.
    public private(set) var entries: [Entry] = []
    
    /// Anzahl der erfolgreichen Testfällen.
    public var successCount: Int {
        entries.filter(\.successful).count
    }
    
    /// Eintrag der Auswertung eines Testfalles.
    ///
    /// Pro durchgeführten Testfall gibt es einen entsprechenden Logeintrag.
    /// Der Logeintrag beinhaltet die Informationen zur Auswertung eines Testfalles.
    public struct Entry: Codable {
        /// Weitere Informationen zu einem Testfall.
        ///
        /// Es kann zum Beispiel Aufschluss darüber gegeben werden, was in diesem Testfall konkret überprüft wird.
        /// Welche Funktion getestet und wie sie aufgerufen wurde.
        public let info: String
        
        /// Fehlermeldung, wenn das Programm oder die Funktion sich nicht verhält wie erwartet.
        public let error: String
        
        /// Gibt an, ob das Ergebnis der Auswertung erfolgreich war.
        public var successful: Bool {
            error.isEmpty
        }
    }
}

extension TestResult {
    mutating func appendEntries(from logfile: URL) throws {
        let decoder = JSONDecoder()
        
        // Read in the logdata from a local file.
        let logdata = try String(contentsOf: logfile, encoding: .utf8)
        
        // Each line represents an `Entry`.
        let lines = logdata.components(separatedBy: .newlines)
        
        for line in lines {
            guard let data = Self.dataFromLine(line) else { continue }
            let logfileEntry = try decoder.decode(Entry.self, from: data)
            self.append(entry: logfileEntry)
        }
    }
    
    private static func dataFromLine(_ line: String) -> Data? {
        if line.isEmpty { return nil }
        return line.data(using: .utf8)
    }
}

extension TestResult {
    mutating func append(entry: Entry) {
        self.entries.append(entry)
    }
}
