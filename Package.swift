// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "Testbench",
    platforms: [.macOS(.v10_13)],
    dependencies: [
        .package(url: "https://github.com/apple/swift-argument-parser", .upToNextMinor(from: "0.4.0")),
        .package(url: "https://github.com/weichsel/ZIPFoundation.git", .upToNextMajor(from: "0.9.0"))
    ],
    targets: [
        .target(
            name: "TestbenchApp",
            dependencies: [
                "TestbenchLib",
                .product(name: "ArgumentParser", package: "swift-argument-parser")
            ],
            resources: [.process("Resources")]
        ),
        .target(
            name: "TestbenchLib",
            dependencies: ["ZIPFoundation"]
        ),
        .testTarget(
            name: "TestbenchLibTests",
            dependencies: ["TestbenchLib"],
            resources: [.copy("Resources")]
        ),
    ]
)
