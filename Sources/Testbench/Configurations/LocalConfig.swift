//
//  LocalConfig.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

/// Lokale Konfiguration der Testbench.
///
/// Mit Hilfe dieses structs wird die lokale Konfigurationsdatei dekodiert.
struct LocalConfig: Identifiable, Codable {
    
    /// Identifikation der Praktikumsaufgabe.
    let id: Int
    
    /// Name der Praktikumsaufgabe.
    let assignmentName: String
    
    /// Die Zeit nachdem die Ausführung der Testung abgebrochen wird.
    let timeoutInMs: Int
    
    /// Anzahl der gesamten Testfälle.
    let totalTestcases: Int
    
    /// Ressourcen, die die `tasks` verwenden können.
    let sharedResources: String?
    
    /// Auführbares Programm, welches eingereicht wurde.
    let submissionExecutable: Executable?
    
    /// Ausführbares Programm, um das eingereichte Programm zu überprüfen.
    let customExecutable: Executable?
    
    /// Aufgaben, welche das `submissionExecutable` oder `customExecutable` ausführen sollen.
    let tasks: [Task]?
}


extension LocalConfig {
    struct Task: Codable {
        /// Name des ausführbaren Programmes.
        let executableName: String
        
        /// Kommandozeilenargumente, die dem Programm übergeben werden können.
        let commandLineArguments: [String]
		
		/// Name der Datei, welche nach Beendigung des Programmes den Exitcode beinhaltet.
		let exitcodeFileName: String?
    }
}


extension LocalConfig {
    struct Executable: Codable {
        
        /// Name des ausführbaren Programmes.
        let name: String
        
        /// Pfad zum Ordner, welcher die Dateien zum Kompilieren enthält.
        let dependencies: String?
    
        /// Optionen zum Bauen des Programmes.
        ///
        /// Überschreibt die globalen Build-Optionen, wenn etwas angegeben wird.
        let buildOptions: [String]?
    }
}
