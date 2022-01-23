//
//  Compiler.swift
//  
//
//  Created by Simon Schöpke on 21.04.21.
//

import Foundation

struct Compiler {
    
    /// URL des Compilers.
    private let url: URL
    
    /// Erstellt einen Compiler, der den Compiler auf dem System verwendet.
    /// - Parameter url: URL des Compilers.
    init(_ url: URL) {
        self.url = url
    }
    
    /// Baut ein `Executable` aus den übergebenen Dateien.
    /// - Parameters:
    ///   - sourceFiles: Source Dateien aus denen die Anwendung gebaut wird.
    ///   - destination: Speicherort der zu erstellenden Anwendung
    ///   - options: Build Optionen.
    /// - Returns: Executable, welches aus den übergebenen Dateien erstellt wurde.
    func build(
        sourceFiles: [URL],
        destination: URL,
        options: [String]) throws -> Executable
    {
        let arguments = Compiler.buildArguments(
            sourceFiles: sourceFiles,
            destination: destination,
            options: options)
        
        try buildExecutable(withArgs: arguments)
        
        return Executable(url: destination)
    }
    
    private static func buildArguments(
        sourceFiles: [URL],
        destination: URL,
        options: [String]) -> [String]
    {
        let sourceFilePaths = sourceFiles.map(\.path)
        let outputOption = "-o"
        let outputFile = destination.path
        return sourceFilePaths + options + [outputOption, outputFile]
    }
    
    private func buildExecutable(withArgs arguments: [String]) throws {
        let pipe = Pipe()
        let task = Process()
        
        task.executableURL = url
        task.arguments = arguments
        task.standardError = pipe
        
        try task.run()
        
        task.waitUntilExit()
        
        guard task.terminationStatus == 0 else {
            let status = task.terminationStatus
            let description = pipe.errorDescription
            throw DidNotCompileError(status: status, description: description)
        }
    }
}


// MARK: - Error(s)
extension Compiler {
    struct DidNotCompileError: DescriptiveError {
        let description: String
        
        init(status: Int32, description: String) {
            let defaultDescription = "Die Anwendung konnte nicht kompiliert werden. Statuscode \(status)."
            self.description = defaultDescription + (description.isEmpty ? "" : " \(description)")
        }
    }
}
