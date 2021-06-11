# Erstellen einer Testbechkonfigurationsdatei

Konfiguriere die Testbench mit einer externen Datei.

## Überblick

Damit die `Testbench` flexibler verwendet werden kann und die entsprechenden Eingaben zur Konfigurations
sehr lang werden können, wird anstelle von Eingaben über die Kommandozeile eine Konfigurationsdatei verwendet.
Die Konfigurationsdatei wird im JSON-Format definiert.
Hier ein Beispiel einer Konfigurationsdatei, um Lösungen der Praktikumsaufgaben aus PPR zu testen.

```json
{
    "workingDirectory": "/Users/Simon/Desktop/TestbenchDirectories/working_directory",
    "testSpecificationDirectory": "/Users/Simon/Desktop/TestbenchDirectories/test_specification",
    "compiler": "/usr/bin/gcc",
    "buildOptions": ["-O", "-Wall"],
    "assignments": [
        {
            "id": 1,
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
```

Das `workingDirectory` gibt den Pfad zu einem leeren Ordner an, worin die Testbench arbeiten kann.
Dort wird aus dem Quelltext der Einreichungen zu den Praktikumsaufgaben und dem Quelltext,
der benötigt wird, um die entsprechende Praktikumsaufgabe zu testen, ein Programm erzeugt,
welches eine Logdatei erzeugt, in die die entsprechenden Auswertungen der Testfälle geschrieben werden.
```json
"workingDirectory": "/Users/Simon/Desktop/TestbenchDirectories/working_directory"
```

Das `testSpecificationDirectory` gibt den Pfad zum Ordner an,
der die Spezifikationen aller Praktikumsaufgaben enthält,
die getestet werden können.
In dem jeweiligen Ordner einer Spezifikation zu einer Pratikumsaufgabe,
befindet sich mindestens eine Konfigurationsdatei zu dem Testen der Praktikumsaufgabe
und weitere Dateien, die zum Testen benötigt werden.
```json
"testSpecificationDirectory": "/Users/Simon/Desktop/TestbenchDirectories/test_specification"
```

Pfad zum C-Compiler, welcher verwendet werden soll.
```json
"compiler": "/usr/bin/gcc"
```

Die `buildOptions` enthalten die einzelnen Kommandozeilenargumente, die dem `compiler` übergeben werden.
Die `buildOptions` werden für jede Kompilierung der verwendeten Quelltexte übergeben.
In der jeweiligen Konfigurationsdatei einer Praktikumsaufgabe kann diese Option überschrieben werden
und dem Compiler andere oder auch keine `buildOptions` übergeben werden.
```json
"buildOptions": ["-O", "-Wall"]
```

Die `assignments` enthalten die Praktikumsaufgaben, die getestet werden können,
die `id` mit der sich eine Praktikumsaufgabe eindeutich zuordnen lässt,
der `name` der Praktikumsaufgabe und
der Pfad zur Konfigurationsdatei der Praktikumsaufgabe relativ zum Pfad des `testSpecificationDirectory`.
In diesem Beispiel ist lautet Pfad zum `testSpecificationDirectory`:
```
/Users/Simon/Desktop/TestbenchDirectories/test_specification
```
und der `filePath` zur Konfigurationsdatei der Ulam-Praktikumsaufgabe:
```
blatt01_Ulam/test-configuration.json
```
dann muss die Konfigurationsdatei der Ulam-Praktikumsaufgabe am folgenden absoluten Pfad liegen:
```
/Users/Simon/Desktop/TestbenchDirectories/test_specification/blatt01_Ulam/test-configuration.json
```
```json
"assignments": [
    {
        "id": 1,
        "name": "Ulam",
        "filePath": "blatt01_Ulam/test-configuration.json"
    }
]
```

## Topics

### Group


