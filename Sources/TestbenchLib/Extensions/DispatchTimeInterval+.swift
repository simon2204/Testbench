//
//  DispatchTimeInterval+.swift
//  
//
//  Created by Simon Schöpke on 23.04.21.
//

import Foundation

extension DispatchTimeInterval {
    var seconds: Double {
        switch self {
        case .seconds(let seconds):
            return Double(seconds)
        case .milliseconds(let milliseconds):
            return Double(milliseconds) / 1_000
        case .microseconds(let microseconds):
            return Double(microseconds) / 1_000_000
        case .nanoseconds(let nanoseconds):
            return Double(nanoseconds) / 1_000_000_000
        case .never:
            return .infinity
        @unknown default:
            return 0
        }
    }
}
