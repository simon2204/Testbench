// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "Testbench",
    platforms: [.macOS(.v10_13)],
    products: [
        .library(name: "Testbench", targets: ["Testbench"])
    ],
    dependencies: [
        .package(url: "https://github.com/weichsel/ZIPFoundation.git", .upToNextMajor(from: "0.9.0"))
    ],
    targets: [
        .target(
            name: "Testbench",
            dependencies: ["ZIPFoundation"],
            resources: [.copy("Resources")]
        ),
        .testTarget(
            name: "TestbenchTests",
            dependencies: ["Testbench"],
            resources: [.copy("Resources")]
        ),
    ]
)
