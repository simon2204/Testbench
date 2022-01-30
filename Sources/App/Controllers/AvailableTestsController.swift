//
//  AvailableTestsController.swift
//  
//
//  Created by Simon Schöpke on 26.04.21.
//

import Vapor
import Testbench

struct AvailableTestsController: RouteCollection {
    let app: Application
    
    var testbenchDirectory: URL {
        URL(fileURLWithPath: app.directory.resourcesDirectory)
    }
    
    var config: URL {
        testbenchDirectory.appendingPathComponent("config.json")
    }
    
    var submission: URL {
        testbenchDirectory.appendingPathComponent("submission")
    }
    
    func boot(routes: RoutesBuilder) throws {
        let availableTestsRoute = routes.grouped("api", "available_tests")
        availableTestsRoute.get(use: getAllAvailableTestNames)
    }
    
    func getAllAvailableTestNames(_ req: Request) async throws -> [Assignment] {
        let testbench = Testbench(config: config)
        return try testbench.availableAssignments()
    }
}

extension Assignment: Content {}
