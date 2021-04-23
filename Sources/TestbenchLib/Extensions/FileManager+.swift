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
        return paths.map(url.appendingPathComponent)
    }
}

extension FileManager {
    func copyItems(at srcURL: URL, into dstURL: URL) {
        let items = self.items(at: srcURL)
        
        for item in items {
            let dstItem = dstURL.appendingPathComponent(item.lastPathComponent)
            
            if FileManager.default.fileExists(atPath: dstItem.path) {
                try? FileManager.default.removeItem(at: dstItem)
            }
            
            try? FileManager.default.copyItem(at: item,
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
