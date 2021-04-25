import XCTest
import class Foundation.Bundle
@testable import TestbenchLib

final class TestbenchLibTests: XCTestCase {
    
    static let tmpDirectory = FileManager.default.temporaryDirectory.appendingPathComponent(UUID().uuidString)
    static let workingDirectory = tmpDirectory.appendingPathComponent("working_directory")
    static let testSpecification = tmpDirectory.appendingPathComponent("test_specification")
    static let submission = tmpDirectory.appendingPathComponent("submission")

    override class func setUp() {
        // URL to XCTest's Resources directory
        let resources = Bundle.module.resourceURL!.appendingPathComponent("Resources")
        // Copy all needed files into a temporary directory.
        try? FileManager.default.copyItem(at: resources, to: tmpDirectory)
        try? FileManager.default.createDirectory(at: TestbenchLibTests.workingDirectory,
                                                 withIntermediateDirectories: false)
        let configJSON = createConfigJSON(workingDirectoryPath: workingDirectory.path, testSpecificationDirectoryPath: testSpecification.path)
        try? configJSON.write(to: tmpDirectory.appendingPathComponent("config.json"),
                              atomically: true,
                              encoding: .utf8)
    }
    
    override class func tearDown() {
        try? FileManager.default.removeItem(at: tmpDirectory)
    }
    
    func testUlamSuccessful() throws {
        let ulamSuccessful = TestbenchLibTests
            .submission
            .appendingPathComponent("ulam")
            .appendingPathComponent("successful")
        
        let testbenchConfig = try TestbenchConfiguration(directory: TestbenchLibTests.tmpDirectory,
                                                         fileName: "config.json")
        
        let unitTest = UnitTest(testbenchConfiguration: testbenchConfig)
        
        let ulamURL = TestbenchLibTests.testSpecification.appendingPathComponent("blatt01_Ulam")
        
        let testConfig = try TestConfiguration(directory: ulamURL,
                                               fileName: "test-configuration.json")
        
        let result = try unitTest.performTestForSubmission(at: ulamSuccessful,
                                                           withConfiguration: testConfig)

        switch result.entries {
        case .failure:
            XCTFail()
        case .success(let entries):
            XCTAssert(!entries.isEmpty)
            entries.forEach { XCTAssert($0.successful) }
        }
    }
    
    func testUlamDoesNotCompile() throws {
        var thrownError: Error?
        
        let ulamSuccessful = TestbenchLibTests
            .submission
            .appendingPathComponent("ulam")
            .appendingPathComponent("doesNotCompile")
        
        let testbenchConfig = try TestbenchConfiguration(directory: TestbenchLibTests.tmpDirectory,
                                                         fileName: "config.json")
        
        let unitTest = UnitTest(testbenchConfiguration: testbenchConfig)
        
        let ulamURL = TestbenchLibTests.testSpecification.appendingPathComponent("blatt01_Ulam")
        
        let testConfig = try TestConfiguration(directory: ulamURL,
                                               fileName: "test-configuration.json")
        
        XCTAssertThrowsError(try unitTest.performTestForSubmission(at: ulamSuccessful,
                                                                   withConfiguration: testConfig)) { error in
            thrownError = error
        }
        
        XCTAssertTrue(thrownError is CCompiler.CompileError)
        
        XCTAssertEqual(thrownError as? CCompiler.CompileError, .didNotCompile(status: 1))
    }
    
    func testUlamInfiniteLoop() throws {
        var thrownError: Error?
        
        let ulamSuccessful = TestbenchLibTests
            .submission
            .appendingPathComponent("ulam")
            .appendingPathComponent("infiniteLoop")
        
        let testbenchConfig = try TestbenchConfiguration(directory: TestbenchLibTests.tmpDirectory,
                                                         fileName: "config.json")
        
        let unitTest = UnitTest(testbenchConfiguration: testbenchConfig)
        
        let ulamURL = TestbenchLibTests.testSpecification.appendingPathComponent("blatt01_Ulam")
        
        let testConfig = try TestConfiguration(directory: ulamURL,
                                               fileName: "test-configuration.json")
        
        let timeoutInSeconds = Double(testConfig.timeoutInMs) / 1_000
        
        XCTAssertThrowsError(try unitTest.performTestForSubmission(at: ulamSuccessful,
                                                                   withConfiguration: testConfig)) { error in
            thrownError = error
        }
        
        XCTAssertTrue(thrownError is CCompiler.CompileError)
        
        XCTAssertEqual(thrownError as? CCompiler.CompileError, .runTimeExceeded(seconds: timeoutInSeconds))
    }
    
    func testUlamProgramCrash() throws {
        var thrownError: Error?
        
        let ulamSuccessful = TestbenchLibTests
            .submission
            .appendingPathComponent("ulam")
            .appendingPathComponent("programCrash")
        
        let testbenchConfig = try TestbenchConfiguration(directory: TestbenchLibTests.tmpDirectory,
                                                         fileName: "config.json")
        
        let unitTest = UnitTest(testbenchConfiguration: testbenchConfig)
        
        let ulamURL = TestbenchLibTests.testSpecification.appendingPathComponent("blatt01_Ulam")
        
        let testConfig = try TestConfiguration(directory: ulamURL,
                                               fileName: "test-configuration.json")
        
        XCTAssertThrowsError(try unitTest.performTestForSubmission(at: ulamSuccessful,
                                                                   withConfiguration: testConfig)) { error in
            thrownError = error
        }
        
        XCTAssertTrue(thrownError is CCompiler.CompileError)
        
        XCTAssertEqual(thrownError as? CCompiler.CompileError, .uncaughtSignal(status: 11))
    }

    static var allTests = [
        ("testUlamSuccessful", testUlamSuccessful),
        ("testUlamDoesNotCompile", testUlamDoesNotCompile),
        ("testUlamInfiniteLoop", testUlamInfiniteLoop),
        ("testUlamProgramCrash", testUlamProgramCrash)
    ]
}
