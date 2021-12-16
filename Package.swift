// swift-tools-version:5.5
import PackageDescription

let package = Package(
    name: "Testbench",
    platforms: [
       .macOS(.v10_15)
    ],
    products: [
        .library(name: "Testbench", targets: ["Testbench"])
    ],
    dependencies: [
        // 💧 A server-side Swift web framework.
        .package(url: "https://github.com/vapor/vapor.git", from: "4.0.0"),
        .package(url: "https://github.com/weichsel/ZIPFoundation.git", .upToNextMajor(from: "0.9.0"))
    ],
    targets: [
        .target(
            name: "App",
            dependencies: [
                .product(name: "Vapor", package: "vapor"),
                .target(name: "Testbench")
            ],
            swiftSettings: [
                .unsafeFlags(["-cross-module-optimization"], .when(configuration: .release))
            ]
        ),
        .target(
            name: "Testbench",
            dependencies: ["ZIPFoundation"]
        ),
        .executableTarget(
            name: "Run",
            dependencies: ["App"]
        ),
        .testTarget(name: "AppTests",
                    dependencies: [
                        .target(name: "App"),
                        .product(name: "XCTVapor", package: "vapor")]
        ),
        .testTarget(
            name: "TestbenchTests",
            dependencies: ["Testbench"],
            resources: [.copy("Resources")]
        ),
    ]
)
