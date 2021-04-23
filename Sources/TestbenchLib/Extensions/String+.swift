//
//  String+.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

extension String {
    func replaceContent(matching expression: NSRegularExpression,
                        withTemplate template: String) -> String {
        let entireContent = NSMakeRange(0, count)
        return expression.stringByReplacingMatches(in: self,
                                                   range: entireContent,
                                                   withTemplate: template)
    }
}
