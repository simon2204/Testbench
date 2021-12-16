//
//  Config.swift
//  
//
//  Created by Simon Schöpke on 25.04.21.
//

func createConfigJSON(
    workingDirectory: String,
    testSpecification: String)
-> String {
    """
    {
        "workingDirectory": "\(workingDirectory)",
        "testSpecificationDirectory": "\(testSpecification)",
        "compiler": "/usr/bin/gcc",
        "buildOptions": ["-O", "-Wall"],
        "assignments": [
            {
                "id": 82893,
                "name": "Ulam",
                "filePath": "blatt01_Ulam/test-configuration.json"
            },
            {
                "id": 2,
                "name": "Matrix",
                "filePath": "blatt02_Matrix/test-configuration.json"
            },
            {
                "id": 3,
                "name": "GameOfLife",
                "filePath": "blatt03_GameOfLife/test-configuration.json"
            },
            {
                "id": 4,
                "name": "Huffman Module",
                "filePath": "blatt04_HuffmanModule/test-configuration.json"
            },
            {
                "id": 5,
                "name": "Bocksatzformatierung",
                "filePath": "blatt05_Blocksatzformatierung/test-configuration.json"
            },
            {
                "id": 6,
                "name": "Huffman Kommandozeile",
                "filePath": "blatt06_HuffmanKommandozeile/test-configuration.json"
            },
            {
                "id": 7,
                "name": "Binärer Heap",
                "filePath": "blatt07_BinaererHeap/test-configuration.json"
            },
            {
                "id": 8,
                "name": "Binärbaum",
                "filePath": "blatt08_Binaerbaum/test-configuration.json"
            },
            {
                "id": 9,
                "name": "Huffman",
                "filePath": "blatt09_Huffman/test-configuration.json"
            }
        ]
    }
    """
}


