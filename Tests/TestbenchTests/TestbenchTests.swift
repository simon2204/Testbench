import XCTest
import Foundation
import Testbench

final class TestbenchTests: XCTestCase {
    
    static let tmpDirectory = FileManager.default
        .temporaryDirectory
        .appendingPathComponent(UUID().uuidString)
    
    static let workingDirectory = tmpDirectory.appendingPathComponent("working_directory")
    static let testSpecification = tmpDirectory.appendingPathComponent("test_specification")
    static let submission = tmpDirectory.appendingPathComponent("submission")

    static let configJSON = "config.json"
    
    static let configJSONURL = tmpDirectory.appendingPathComponent(configJSON)
    
    override class func setUp() {
        // URL to XCTest's Resources directory
        #if os(macOS)
        let resources = Bundle.module.resourceURL!.appendingPathComponent("Resources")
        #else
        let resources = Bundle.module.resourceURL!
        #endif

        let configJSON = createConfigJSON(
            workingDirectory: workingDirectory.path,
            testSpecification: testSpecification.path)

        // Copy all needed files into a temporary directory.
        do {
            try FileManager.default.copyItem(at: resources, to: tmpDirectory)
            
            try FileManager.default
                .createDirectory(
                    at: TestbenchTests.workingDirectory,
                    withIntermediateDirectories: false)
            
            try configJSON.write(
                to: configJSONURL,
                atomically: true,
                encoding: .utf8)
            
        } catch {
            print(error)
        }
    }

    override class func tearDown() {
        try? FileManager.default.removeItem(at: tmpDirectory)
    }

    func testUlamSuccessful() throws {
        let ulamSuccessful = TestbenchTests
            .submission
            .appendingPathComponent("ulam")
            .appendingPathComponent("successful")

        let testbench = Testbench(config: TestbenchTests.configJSONURL)
        
        let result = try testbench.performTests(submission: ulamSuccessful, assignment: 82893)

        XCTAssert(!result.entries.isEmpty)
        result.entries.forEach { XCTAssert($0.error.isEmpty) }
    }
    
    func testUlamDoesNotCompile() throws {
        let ulamDoesNotCompile = TestbenchTests
            .submission
            .appendingPathComponent("ulam")
            .appendingPathComponent("doesNotCompile")

        let testbench = Testbench(config: TestbenchTests.configJSONURL)
        
        let testResult = try testbench.performTests(
            submission: ulamDoesNotCompile,
            assignment: 82893)
        
        XCTAssertNil(testResult.runTime)
        
        let errorMsg = try XCTUnwrap(testResult.errorMsg)
        
        XCTAssert(!errorMsg.isEmpty)
    }
    
    func testUlamInfiniteLoop() throws {
        let ulamInfiniteLoop = TestbenchTests
            .submission
            .appendingPathComponent("ulam")
            .appendingPathComponent("infiniteLoop")
        
        let testbench = Testbench(config: TestbenchTests.configJSONURL)

        let testResult = try testbench.performTests(
            submission: ulamInfiniteLoop,
            assignment: 82893)
        
        let errorMsg = try XCTUnwrap(testResult.errorMsg)
        
        XCTAssertNil(testResult.runTime)
        
        XCTAssertEqual(errorMsg, "Die maximale Laufzeit des Programmes von 10.0 Sekunden wurde überschritten.")
    }

    func testUlamProgramCrash() throws {
        let ulamProgramCrash = TestbenchTests
            .submission
            .appendingPathComponent("ulam")
            .appendingPathComponent("programCrash")

        let testbench = Testbench(config: TestbenchTests.configJSONURL)
        
        let testResult = try testbench.performTests(
            submission: ulamProgramCrash,
            assignment: 82893)
        
        let errorMsg = try XCTUnwrap(testResult.errorMsg)
        
        XCTAssertEqual(errorMsg, "Das Programm beendete sich mit Statuscode 11.")
    }
    
    func testHuffmanSuccessful() throws {
        print(Self.tmpDirectory)
        
        let huffmanSuccessful = TestbenchTests
            .submission
            .appendingPathComponent("huffman")
            .appendingPathComponent("successful")

        let testbench = Testbench(config: TestbenchTests.configJSONURL)
        
        let result = try testbench.performTests(submission: huffmanSuccessful, assignment: 9)
        
        XCTAssertNil(result.errorMsg)

        XCTAssert(!result.entries.isEmpty)
        result.entries.forEach { XCTAssert($0.error.isEmpty) }
    }
}
