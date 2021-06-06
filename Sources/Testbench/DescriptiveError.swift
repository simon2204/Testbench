//
//  DescriptiveError.swift
//  
//
//  Created by Simon Schöpke on 06.06.21.
//

protocol DescriptiveError: Error {
    var description: String { get }
}
