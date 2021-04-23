//
//  File.swift
//  
//
//  Created by Simon Schöpke on 18.04.21.
//

import Foundation

public struct TestbenchConfiguration: Decodable {
    public let workingDirectory: URL
    public let testSpecificationDirectory: URL
    public let moodleUsername: String
    public let moodlePassword: String
    public let adminEmails: [URL]
    public let smtpConfiguration: SMTPConfiguration
    public let allowedCorsURLs: [URL]
    public let testUser: String
    public let disableMoodleUpload: Bool
}

public struct SMTPConfiguration: Decodable {
    public let serverURL: URL
    public let port: Int
    public let username: String
    public let password: String
    public let senderEmail: URL
}
