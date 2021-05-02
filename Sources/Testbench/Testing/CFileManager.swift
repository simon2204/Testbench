//
//  CFileManager.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

public struct CFileManager {
    
    private static let mainFuncPattern = "int\\s+main\\s*\\("
    
    private static let invalidMainFuncName = "int ____main("
    
    private static var mainFuncRegex: NSRegularExpression {
        return try! NSRegularExpression(pattern: CFileManager.mainFuncPattern)
    }
    
    /// Performs a shallow search for all ".c" files and renames all "main" functions, so the original "main" functions
    /// won't longer execute when the program starts.
    /// - Parameter url: The directory in which the ".c" files will be scanned.
    static func renameMainFunctions(at url: URL) throws {
        let cFileURLs = cFiles(at: url)
        
        for cFileURL in cFileURLs {
            let content = try String(contentsOf: cFileURL)
            let replacement = content.replaceContent(matching: CFileManager.mainFuncRegex,
                                                     withTemplate: CFileManager.invalidMainFuncName)
            try replacement.write(to: cFileURL,
                                  atomically: true,
                                  encoding: .utf8)
        }
    }
    
    static func cFiles(at url: URL) -> [URL] {
        let urls = FileManager.default.items(at: url)
        return CFileManager.filterCFiles(from: urls)
    }
    
    static func filterCFiles(from urls: [URL]) -> [URL] {
        return urls.filter(CFileManager.isCFile)
    }
    
    static func isCFile(at url: URL) -> Bool {
        return url.pathExtension == "c"
    }
}

