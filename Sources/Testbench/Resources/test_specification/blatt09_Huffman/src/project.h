/**
 * @mainpage Huffman-Codierung
 *
 * Mit diesem Projekt steht die Komprimierung und Dekomprimierung 
 * beliebiger Dateien nach dem Huffman-Verfahren zur Verfügung.
 * 
 * @section Benutzung
 *
 * Die Komprimierung bzw. Dekomprimierung wird von der Kommandozeile aus 
 * aufgerufen, bspw. mit:
 * <ul>
 * <li> c:\> huffman -c c:/temp/in.txt
 * <li> c:\> huffman -d -o c:/temp/out.txt c:/temp/in.txt
 * </ul>
 *
 * Die Angabe einer Eingabedatei ist zwingend notwendig, während der Name der 
 * Ausgabedatei weggelassen werden kann. Wird keine Ausgabedatei angegeben, 
 * erfolgt die Ausgabe in eine Datei, deren Name aus dem der Eingabedatei und 
 * einer Erweiterung, .hc bzw. .hd, konstruiert wird. Mit der Option -c wird 
 * die Eingabedatei komprimiert und mit der Option -d wird sie dekomprimiert.
 * Mit der Option -v kann man sich Informationen zur Laufzeit und Größe der 
 * Dateien anziegen lassen.
 *
 * @section Architektur
 * 
 * Zum Projekt gehören die folgenden Module mit den dargestellten 
 * Abhängigkeiten. Ein Pfeil, der von einem Modul M1 zu einem Modul M2 geht, 
 * zeigt an, dass das Modul M1 Funktionen von M2 nutzt.
 * \image html architektur.jpg
 * 
 * @section Modulbeschreibungen
 *
 * @subsection main
 * Dieses Modul enthält die Funktion main. Es prüft die übergebenen 
 * Kommandozeilenargumente. Sind diese fehlerhaft, wird die Ausführung mit 
 * einer Fehlermeldung abgebrochen. Sind sie korrekt, wird die 
 * Huffman-Komprimierung bzw. Huffman-Dekomprimierung entsprechend der 
 * übergebenen Argumente gestartet.
 * 
 * @subsection huffman
 * Dieses Modul realisiert die Komprimierung und Dekomprimierung anhand des 
 * Verfahrens der Huffman-Kodierung. Die Komprimierung einer Datei verläuft 
 * in den folgenden Schritten:
 * <ol>
 * <li> Ermitteln der Häufigkeit der in der Eingabedatei vorkommenden Zeichen
 * <li> Aufbau des optimalen Codebaums aus den Häufigkeiten
 * <li> Ableiten der Codetabelle aus dem Baum 
 * <li> Abspeichern der Häufigkeiten in der Ausgabedatei
 * <li> Kodieren der Zeichen und Ausgabe in die Ausgabedatei
 *</ol>
 *
 * Die Dekomprimierung einer komprimierten Datei verläuft in den folgenden 
 * Schritten:
 * <ol>
 * <li> Einlesen der Häufigkeiten aus der komprimierten Datei
 * <li> Aufbau des optimalen Codebaums aus den Häufigkeiten
 * <li> Dekodieren der der Codetabelle nachfolgenden Zeichen anhand des 
 *      Codebaums und dekomprimierte Ausgabe in die Ausgabedatei.
 * </ol>
 *
 * Um eine komprimierte Datei wieder dekomprimieren zu knnen, wird ein 
 * Header von folgendem Format in die komprimierte Datei geschrieben:
 * <ul>
 * <li> 1 x 4 Byte: Ein Wert (unsigned int), der die Anzahl der 
 *      Zeichenin der Eingabedatei angibt.
 * <li> 1 x 4 Byte: Ein Wert (unsigned int), der die Anzahl der 
 *      Zeichen/Häufigkeits-Paare im Header angibt.
 * <li> n x 5 Byte: Diese Gruppen von jeweils 5 Bytes bestehen aus einem 
 *      char-Byte, das ein Zeichen beschreibt und einem Wert (unsigned int), 
 *      der die Häufigkeit des Zeichens in der zu komprimierenden Datei enthält.
 *      n steht für die Anzahl verschiedener Zeichen in der Ausgangsdatei.
 * </ul>
 *
 * @subsection io
 * 
 * Dieses Modul realisiert den lesenden und schreibenden Zugriff auf Dateien. 
 * Es können Daten in den Einheiten von 1 Bit, 1 Byte oder 4-Bytes gelesen oder
 * geschrieben werden. Bei der Einheit 1 Bit kapselt das Modul den byteweisen 
 * Zugriff auf die Datei.
 * 
 * @subsection frequency
 * 
 * Dieses Modul stellt eine Datenstruktur zur Verfügung, um die Zeichen eines 
 * Textes mit ihren Häufigkeiten in Verbindung zu setzen.
 * 
 * @subsection huffman_common
 * 
 * In diesem Modul werden die gemeinsam verwendeten Definitionen definiert.
 *
 * @subsection b_heap
 * 
 * Dieses Modul realisiert einen binären Heap und stellt Funktionen zur 
 * Verfügung, um Elemente einzufügen und löschen zu können. Für die 
 * Huffman-Kodierung werden die optimalen Codebäume im Heap abgelegt.
 *
 * @subsection btree
 * 
 * Dieses Modul stellt Binärbäume und Funktionen darauf zur Verfügung. Für die 
 * Huffman-Codierung werden die optimalen Codebäume als Binärbäume abgelegt.
 *
 * @subsection btreenode
 * 
 * Dieses Modul wird vom Modul btree verwendet. Es definiert die Knoten der 
 * Binärbäume und stellt Funktionen darauf zur Verfügung.
 *
 * @author Ulrike Griefahn
 * @date 2015-12-17
 */
