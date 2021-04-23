import XCTest
import class Foundation.Bundle
@testable import TestbenchLib

final class TestbenchLibTests: XCTestCase {
    
    let resources = Bundle.module.resourceURL!
    
    override func setUp() {
        
    }
    
    override func tearDown() {
        
    }
    
    func testFindResources() throws {
        let optionalConfigURL = Bundle.module.url(forResource: "config", withExtension: "json")
        let configURL = try XCTUnwrap(optionalConfigURL)
        let config = try TestbenchConfiguration.loadWithJSONDecoder(from: configURL)
        XCTAssertEqual(config.moodlePassword, "Success")
    }
    
    func testUnzipItem() throws {
        try FileManager.default.unzipItems(at: resources)
        let fileExists = FileManager.default.fileExists(atPath: resources.appendingPathComponent("PPR_P_Blatt03.pdf").path)
        XCTAssertTrue(fileExists)
        
        unzipItemsTearDown()
    }
    
    func unzipItemsTearDown() {
        let file = resources.appendingPathComponent("PPR_P_Blatt03.pdf")
        let folder = resources.appendingPathComponent("__MACOSX")
        try? FileManager.default.removeItem(at: file)
        try? FileManager.default.removeItem(at: folder)
    }

    static var allTests = [
        ("testFindResources", testFindResources),
        ("testUnzipItem", testUnzipItem)
    ]
}
