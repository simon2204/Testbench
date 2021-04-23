//
//  CCompiler.swift
//  
//
//  Created by Simon Schöpke on 21.04.21.
//

import Foundation

struct CCompiler {
    let source: URL
    let destination: URL
    let compiler: Compiler
    let options: BuildOptions
    
    func build() throws -> TimeInterval  {
        let compilerURL = URL(fileURLWithPath: compiler.rawValue)
        
        let cFilePaths = CFileManager.cFiles(at: source).map(\.path)
        let outputOption = "-o \(destination.path)"
        let compilerArguments = cFilePaths + options.arguments + [outputOption]
        
        let secondsNeeded = try CCompiler.measureExecutionTime {
            let task = try Process.run(compilerURL, arguments: compilerArguments)
            task.waitUntilExit()
        }
        
        return secondsNeeded
    }
    
    func run(withDeadline deadline: DispatchTimeInterval) throws -> TimeInterval {
        let testExecutable = destination.appendingPathComponent("test_executable")
        
        let secondsNeeded = try CCompiler.measureExecutionTime {
            // TODO: Arguments
            let task = try Process.run(testExecutable, arguments: [])
            let deadlineHasPassed = task.waitUntilExit(deadline: .now() + deadline)
            if deadlineHasPassed { throw CompileError.runTimeExceeded(seconds: deadline.seconds) }
        }
        
        return secondsNeeded
    }
}

extension CCompiler {
    struct BuildOptions: OptionSet {
        let rawValue: Int
        
        static let compilationTimeOptimization  = BuildOptions(rawValue: 1 << 0)
        static let enableAllWarnings            = BuildOptions(rawValue: 1 << 1)
        static let printVerboseInformation      = BuildOptions(rawValue: 1 << 2)
        static let enableSupportForISOC89       = BuildOptions(rawValue: 1 << 3)
        static let defineTestbenchMacro         = BuildOptions(rawValue: 1 << 4)
        static let convertWarningsIntoErrors    = BuildOptions(rawValue: 1 << 5)
        
        fileprivate var arguments: [String] {
            var args = [String]()
            if self.contains(.compilationTimeOptimization)  { args.append("-O") }
            if self.contains(.enableAllWarnings)            { args.append("-Wall") }
            if self.contains(.printVerboseInformation)      { args.append("-v") }
            if self.contains(.enableSupportForISOC89)       { args.append("-ansi") }
            if self.contains(.defineTestbenchMacro)         { args.append("-DTESTBENCH") }
            if self.contains(.convertWarningsIntoErrors)    { args.append("-Werror") }
            return args
        }
    }
}

extension CCompiler {
    enum Compiler: String {
        case gcc    = "/usr/bin/gcc"
        case clang  = "/usr/bin/clang"
    }
}

extension CCompiler {
    private static func measureExecutionTime(task: () throws -> Void) rethrows -> TimeInterval {
        let start = DispatchTime.now()
        try task()
        let end = DispatchTime.now()
        let nanoTime = end.uptimeNanoseconds - start.uptimeNanoseconds
        let timeInterval = Double(nanoTime) / 1_000_000_000
        return timeInterval
    }
}

extension CCompiler {
    enum CompileError: LocalizedError {
        case buildTimeExceeded(seconds: TimeInterval)
        case runTimeExceeded(seconds: TimeInterval)
        
        var errorDescription: String? {
            switch self {
            case .buildTimeExceeded(seconds: let seconds):
                return "Build time of \(seconds) seconds has been exceeded"
            case .runTimeExceeded(seconds: let seconds):
                return "Run time of \(seconds) seconds has been exceeded"
            }
        }
    }
}
