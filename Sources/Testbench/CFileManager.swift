//
//  CFileManager.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

struct CFileManager {
    
    private static let mainFuncPattern = "int\\s+main\\s*\\("
    
    private static let invalidMainFuncName = "int ____main("
    
    private static let mainFuncRegex =
        try! NSRegularExpression(pattern: CFileManager.mainFuncPattern)
    
    /// Performs a shallow search for all ".c" files and renames all "main" functions, so the original "main" functions
    /// won't longer execute when the program starts.
    /// - Parameter url: The directory in which the ".c" files will be scanned.
    static func renameMainFunctions(at url: URL) throws {
        let cFileURLs = try cFiles(at: url)
        
        for cFileURL in cFileURLs {
            let content = try String(contentsOf: cFileURL)
            
            let replacement = content.replaceContent(
                matching: CFileManager.mainFuncRegex,
                withTemplate: CFileManager.invalidMainFuncName)
            
            try replacement.write(
                to: cFileURL,
                atomically: true,
                encoding: .utf8)
        }
    }
    
    static func cFiles(at url: URL) throws -> [URL] {
        let urls = try FileManager.default.items(at: url)
        return CFileManager.filterCFiles(from: urls)
    }
    
    static func filterCFiles(from urls: [URL]) -> [URL] {
        return urls.filter(CFileManager.isCFile)
    }
    
    static func isCFile(at url: URL) -> Bool {
        return url.pathExtension == "c"
    }
    
    static func containsMainFunction(in directory: URL) throws -> Bool {
        let cFiles = try cFiles(at: directory)
        return try containsMainFunction(at: cFiles)
    }
    
    static func containsMainFunction(at urls: [URL]) throws -> Bool {
        for url in urls {
            if try containsMainFunction(at: url) { return true }
        }
        return false
    }
    
    static func containsMainFunction(at url: URL) throws -> Bool {
        let sourceCode = try String(contentsOf: url)
        return sourceCode.contains(expression: mainFuncRegex)
    }
}

