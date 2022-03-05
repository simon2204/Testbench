//
//  UnitTest.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

final class UnitTest {
    
    /// Name der Datei, die nach erfolgreicher Testung erstellt worden ist.
    /// Enthält die Ergebnisse der einzelnen Testfälle als JSON.
    private static let assertsJsonLog = "ppr_tb_asserts_json.log"
    
    private let config: Config
    private let submission: URL
    private let compiler: Compiler
    private var testEnvironment: TestEnivronment!
    
    init(config: Config, submission: URL) {
        self.config = config
        self.submission = submission
        self.compiler = Compiler(config.compiler)
    }
    
    func performTests() throws -> TestResult {
        
        var runTime: TimeInterval?
        var errorMsg = ""
        
        do {
            testEnvironment = try TestEnivronment(config: config, submission: submission)
            runTime = try executeTests()
        } catch let error as DescriptiveError {
            errorMsg = error.description
        } catch {
            errorMsg = error.localizedDescription
        }
        
        var result = TestResult(
            assignmentName: config.assignmentName,
            totalTestcases: config.totalTestcases,
            runTime: runTime, errorMsg: errorMsg
        )
        
        // Es muss kein Logfile vorhanden sein, wenn es zuvor eine Error-Nachricht gab.
        // Deswegen soll kein Error geworfen werden, wenn kein Logfile gefunden wurde.
        if let logfile = try? testEnvironment?.getItem(withName: UnitTest.assertsJsonLog) {
            try result.appendEntries(from: logfile)
        }

        return result
    }
    
    private func executeTests() throws -> TimeInterval {
        let executable = try buildSubmissionExecutable()
        let canBuildCustomExecutable = try buildCustomExecutable()
        
        if canBuildCustomExecutable {
            return try runCustomTasks()
        } else {
            return try runSubmissionExecutable(executable)
        }
    }
    
    private func runSubmissionExecutable(_ executable: Executable) throws -> TimeInterval {
        return try executable.run(arguments: [], deadline: config.timeout)
    }
    
    private func runCustomTasks() throws -> TimeInterval {
        let timeNeeded = try config.tasks.reduce(0.0) { totalRunTime, task in
            let currentRunTime = try runCustomTask(task)
            return currentRunTime + totalRunTime
        }
        return timeNeeded
    }
    
    private func runCustomTask(_ task: Config.Process) throws -> TimeInterval {
        let process = try self.testEnvironment.getItem(withName: task.executableName)
		
		var exitCodeURL: URL?
		
		if let exitCodeName = task.exitcodeName {
			exitCodeURL = testEnvironment.appendingPathCompotent(exitCodeName)
		}
		
		let executable = Executable(url: process, exitcodeName: exitCodeURL)
        return try executable.run(arguments: task.commandLineArguments, deadline: config.timeout)
    }
    
    /// Build the submission executable.
    /// - Returns: `URL` to the executable.
    private func buildSubmissionExecutable() throws -> Executable {
        let executable = config.submissionExecutable
        let sourceFiles = try testEnvironment.submissionSourceFiles()
        return try buildExecutable(executable, from: sourceFiles)
    }
    
    /// Builds the constum executable.
    /// - Returns: `true`, if a custom executable was specified and `false` otherwise.
    private func buildCustomExecutable() throws -> Bool {
        guard let executable = config.customTestExecutable else { return false }
        let sourceFiles = try testEnvironment.customSourceFiles()
        let _ = try buildExecutable(executable, from: sourceFiles)
        return true
    }
    
    private func buildExecutable(_ executable: Config.Executable, from files: [URL]) throws -> Executable {
        let destination = testEnvironment.appendingPathCompotent(executable.name)
        return try compiler.build(
            sourceFiles: files,
            destination: destination,
            options: executable.buildOptions)
    }
}


//protocol Parser {
//    associatedtype Entries
//    func parse(data: Data) throws -> Entries
//}
//
//protocol DataSupplier {
//    func getData() throws -> Data
//}
//
//protocol Builder {
//    func build() -> Result<Executer, String>
//}
//
//extension String: Error {
//    
//}
//
//protocol Executer {
//    func run() -> (Int, String?)
//}
//
//class TestRunner {
//    
//    private let dataSupplier: DataSupplier
//    
//    private let parser: Parser
//    
//    private let executer: Executer
//    
//    
//    init(dataSupplier: DataSupplier, parser: Parser, executer: Executer) {
//        self.dataSupplier = dataSupplier
//        self.parser = parser
//        self.executer = executer
//    }
//    
//    func performTest() throws -> Parser.Entries {
//        
//        // build executable
//        
//        let (errorCode, error) = executer.run()
//        
//        let data = try dataSupplier.getData()
//        
//        return try parser.parse(data: data)
//    }
//    
//    
//    
//}
//
//class ResultSupplier: DataSupplier {
//    
//    private let logfile: URL
//    
//    init(logfile: URL) {
//        self.logfile = logfile
//    }
//    
//    func getData() throws -> Data {
//        try Data(contentsOf: logfile)
//    }
//}
//
//class ResultLogDataParser: Parser {
//    
//    func parse(data: Data) throws -> [TestResult.Entry] {
//        
//    }
//}
