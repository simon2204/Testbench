//
//  LocalConfig.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

struct LocalConfig: Identifiable, Codable {
    
    let id: Int
    
    /// The assignment's label.
    ///
    /// For expample: Blocksatz (Blatt 06)
    let assignmentName: String
    
    /// The maximum time needed for executing all test cases in milliseconds.
    ///
    /// If the test cases need more than the specified amout of time, the submission might have run into an infinite loop.
    let timeoutInMs: Int
    
    let totalTestcases: Int
    
    let sharedResources: String?
    
    let submissionExecutable: Executable?
    
    let customExecutable: Executable?
    
    let tasks: [Process]?
}


extension LocalConfig {
    struct Process: Codable {
        
        /// Name of the executable
        let executableName: String
        
        /// Arguments to pass to the executable
        let commandLineArguments: [String]
		
		/// Name of the file to save the exit-code in.
		let exitcodeFileName: String?
    }
}


extension LocalConfig {
    struct Executable: Codable {
        
        /// Name of the executable after compiling
        let name: String
        
        /// Name of the directory containing dependencies for building the executable
        let dependencies: String?
    
        /// Additional build options
        ///
        /// Overrides build options from "config.json" but does not override internal build options.
        let buildOptions: [String]?
    }
}
