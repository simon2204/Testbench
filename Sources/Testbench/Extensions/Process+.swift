//
//  Process+.swift
//  
//
//  Created by Simon Schöpke on 23.04.21.
//

import Foundation


extension Process {
    /// Block until the receiver is finished. Terminates the receiver after passing a deadline.
    /// - Parameter deadline: The latest time by which the receiver should have completed the task.
    /// - Returns: True if the deadline has passed, false otherwise.
    func waitUntilExit(deadline: DispatchTime) -> Bool {
        var deadlineHasPassed = false
        
        let terminationTask = DispatchWorkItem {
            self.terminate()
            deadlineHasPassed = true
        }
        
        DispatchQueue.main.asyncAfter(deadline: deadline, execute: terminationTask)
        
        self.waitUntilExit()
        
        terminationTask.cancel()
        
        return deadlineHasPassed
    }
}
