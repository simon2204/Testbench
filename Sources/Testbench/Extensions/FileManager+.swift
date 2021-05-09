//
//  FileManager+.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation
import ZIPFoundation

extension FileManager {
    func items(at url: URL) -> [URL] {
        guard let paths = try? contentsOfDirectory(atPath: url.path) else { return [] }
        let items = paths.map(url.appendingPathComponent)
        
        var itemsAndAliases = [URL]()
        
        for item in items {
            if let alias = try? URL(resolvingAliasFileAt: item) {
                itemsAndAliases.append(alias)
            } else {
                itemsAndAliases.append(item)
            }
        }
        
        return itemsAndAliases
    }
}

extension FileManager {
    func copyItems(at srcURL: URL, into dstURL: URL) throws {
        let items = self.items(at: srcURL)
        
        for item in items {
            let dstItem = dstURL.appendingPathComponent(item.lastPathComponent)
            
            if FileManager.default.fileExists(atPath: dstItem.path) {
                try FileManager.default.removeItem(at: dstItem)
            }
            
            try FileManager.default.copyItem(at: item,
                                              to: dstItem)
        }
    }
}

extension FileManager {
    func unzipItems(at url: URL) throws {
        let zipped = zippedItems(at: url)
        try zipped.forEach(unzipItem)
    }
    
    private func zippedItems(at url: URL) -> [URL] {
        let items = self.items(at: url)
        return items.filter(FileManager.hasZIPPathExtension)
    }
    
    private func unzipItem(at url: URL) throws {
        try unzipItem(at: url, to: url.deletingLastPathComponent())
    }
    
    private static func hasZIPPathExtension(url: URL) -> Bool {
        url.pathExtension == "zip"
    }
}

extension FileManager {
    /// Recursively searches for a file at a directory matching a specific name.
    /// - Parameters:
    ///   - name: Name of a file to search for.
    ///   - url: The Directory in which to look for.
    /// - Returns: The first `URL` to the file with the given name.
    func firstFile(named name: String, at url: URL) -> URL? {
        let files = self.files(at: url)
        return files.first(where: { $0.lastPathComponent == name })
    }
    
    /// Recursively searches for all files at the given directory.
    /// - Parameter url: The directory in which to look for.
    /// - Returns: An array of all urls found at the given directory.
    func files(at url: URL) -> [URL] {
        var files = [URL]()
        
        if let enumerator = FileManager
            .default
            .enumerator(at: url, includingPropertiesForKeys: [.isRegularFileKey],
                        options: [.skipsHiddenFiles, .skipsPackageDescendants]) {
            
            for case let fileURL as URL in enumerator {
                
                let fileAttributes = try? fileURL.resourceValues(forKeys: [.isRegularFileKey])
            
                if fileAttributes?.isRegularFile ?? false {
                    files.append(fileURL)
                }
            }
        }

        return files
    }
    
    /// Recursively searches for all files with a specific name at the given directory.
    /// - Parameter url: The directory in which to look for.
    /// - Parameter name: The file name to filter for.
    /// - Returns: An array of all urls found with the given name at the given directory.
    func files(at url: URL, named name: String) -> [URL] {
        self.files(at: url).filter { $0.lastPathComponent == name }
    }
}
