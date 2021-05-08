//
//  TestConfig.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

struct TestConfig: Identifiable, Codable {
    
    public let id: Int
    
    /// The assignment's label.
    ///
    /// For expample: Blocksatz (Blatt 06)
    public let label: String
    
    /// The maximum time needed for executing all test cases in milliseconds.
    ///
    /// If the test cases need more than the specified amout of time, the submission might have run into an infinite loop.
    public let timeoutInMs: Int
    
    public let sharedResources: String?
    
    public let submissionExecutable: Executable?
    
    public let customTestExecutable: Executable?
    
    public let tasks: [Process]?
}


extension TestConfig {
    public struct Process: Codable {
        
        /// Name of the executable
        public let executableName: String
        
        /// Arguments to pass to the executable
        public let commandLineArguments: [String]
    }
}


extension TestConfig {
    public struct Executable: Codable {
        
        /// Name of the executable after compiling
        public let name: String
        
        /// Name of the directory containing dependencies for building the executable
        public let dependencies: String?
    
        /// Additional build options
        ///
        /// Overrides build options from "config.json" but does not override internal build options.
        public let buildOptions: [String]?
    }
}
