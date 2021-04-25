//
//  File.swift
//  
//
//  Created by Simon Schöpke on 25.04.21.
//

func createConfigJSON(workingDirectoryPath: String,
                      testSpecificationDirectoryPath: String) -> String {
    """
    {
        "workingDirectory": "\(workingDirectoryPath)",
        "testSpecificationDirectory": "\(testSpecificationDirectoryPath)",
        "moodleUsername": "*******",
        "moodlePassword": "*******",
        "moodleURL": "https://moodle.w-hs.de",
        "adminEmails": [ "test@w-hs.de" ],
        "smtpConfiguration": {
            "serverURL": "smtp.w-hs.de",
            "port": 587,
            "username": "********",
            "password": "********",
            "senderEmail": "testbench@w-hs.de"
        },
        "allowedCorsURLs": [
            "http://localhost:8080",
            "http://localhost:3000"
        ],
        "testUser": "****",
        "disableMoodleUpload": false
    }
    """
}


