//
//  TestResult.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

/// Das Ergebnis der Auswertung  zu einer Praktikumsaufgabe.
///
/// Die Auswertung beinhaltet alle Ergebnisse zu den verschiedenen Testfällen, die ausgeführt wurden.
/// Sowie der Ausführungsdauer, eine eventuelle Fehlermeldung und das Datum,
/// welches den Start der Ausführung der Testfälle kennzeichnet.
///
public struct TestResult: Codable {
    /// Enthällt alle Auswertungen, für die Testfälle, die ausgeführt wurden.
    public private(set) var entries: [LogfileEntry] = []
    
    /// Die Zeit, die benötigt wurde, alle Testfälle der Praktikumsaufgabe auszuführen.
    /// Enthält `nil`, wenn es vorzeitig zu einem Fehler in der Praktikumsaufgabe gab,
    /// der dazu geführt hat den Test zu unterbrechen.
    public var runTime: TimeInterval?
    
    /// Die Fehlermeldung, welche Aufschluss darüber geben soll,
    /// warum es zu einem vorzeitigen Beenden des Tests gekommen ist.
    /// Enthält `nil`, wenn alle Testfälle durchlaufen werden konnten.
    public var errorMsg: String?
    
    /// Datum des Starts zur Ausführung der Testfälle.
    public var date: String
    
    init() {
        let now = Date()
        let localizedDate = DateFormatter
            .localizedString(
                from: now,
                dateStyle: .full,
                timeStyle: .long)
        self.date = localizedDate
    }
    
    /// Logeintrag eines Testfalles.
    ///
    /// Pro durchgeführten Testfall gibt es einen entsprechenden Logeintrag.
    /// Der Logeintrag beinhaltet die Informationen zur Auswertung eines Testfalles.
    ///
    public struct LogfileEntry: Codable {
        
        /// Identifikation eines Logeintrages.
        ///
        /// Jeder Logeintrag hat eine bestimmte `id`,
        /// oft aufsteigend nach der Ausführungsreihenfolge der Testfälle vergeben
        /// und dient dazu den Logeintrag einen bestimmten Testfall zuzuordnen
        /// und um möglicherweise fehlende Logeinträge zu bemerken.
        ///
        public let id: Int
        
        /// Identifikation, um Logeinträge zu gruppieren.
        ///
        /// Logeinträge mit der gleichen `groupId` kennzeichnen zum Beispiel die gleiche Art eines Testfalles.
        ///
        public let groupId: Int
        
        /// Weitere Informationen zu einem Testfall.
        ///
        /// Es kann zum Beispiel Aufschluss darüber gegeben werden, was in diesem Testfall konkret überprüft wird.
        /// Welche Funktion getestet wird und wie sie aufgerufen wird.
        ///
        public let info: String
        
        /// Enthält die erwartete Ausgabe eines Programmes oder einer Funktion.
        public let expected: String
        
        /// Enthält die tatsächliche  Ausgabe eines Programmes oder einer Funktion.
        public let actual: String
        
        /// Fehlermeldung, wenn das Programm oder die Funktion sich nicht verhält wie erwartet.
        public let error: String
        
        /// Anzahl aller auszuführenden Testfälle.
        public let total: Int
    }
}

extension TestResult {
    init(from logfile: URL) throws {
        self.init()
        
        let decoder = JSONDecoder()
        
        // read in the logdata from a local file
        let logdata = try String(contentsOf: logfile, encoding: .utf8)
        
        // each line represents a `LogfileEntry`
        let lines = logdata.components(separatedBy: .newlines)
        
        for line in lines {
            guard let data = Self.dataFromLine(line) else { continue }
            let logfileEntry = try decoder.decode(LogfileEntry.self, from: data)
            self.append(entry: logfileEntry)
        }
    }
    
    private static func dataFromLine(_ line: String) -> Data? {
        if line.isEmpty { return nil }
        return line.data(using: .utf8)
    }
}

extension TestResult {
    mutating func append(entry: LogfileEntry) {
        self.entries.append(entry)
    }
}
