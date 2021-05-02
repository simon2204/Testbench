/**
 * @file
 * In diesem Modul werden die Huffman-Komprmierung und die 
 * Dieses Modul realisiert den Komprimierung und Dekomprimierung anhand der 
 * Huffman-Kodierung. Um eine Dekomprimierung zu ermoeglichen, wird beim
 * Komprimieren ein Header von folgendem Format in die Dateien geschrieben:
 * 
 * <UL>
 * <LI> -1x 4 Byte: unsigned int, welcher die Anzahl der
 *                  Zeichen/Haeufigkeits-Paare im Header angibt.
 * <LI> -1x 4 Byte: unsigned int, welcher festlegt wie viele
 *                  Bits des letzten Bytes in der Datei noch mit
 *                  sinnvollen Daten belegt sind.
 * <LI> -Nx 5 Byte: Diese bestehen aus einem Character-Byte
 *                  welches ein Zeichen beschreibt und einem
 *                  unsigned int, welcher die Haeufigkeit
 *                  des Zeichens in der zu komprimierenden Datei
 *                  enthaelt. N steht fuer den Wert verschiedener
 *                  Zeichen in der Ausgangsdatei.
 * </UL>
 * 
 * @author S.Schmidt, U. Griefahn
 * @date 2017-01-12
 *
 * ------------------------------------------------------------------------ */

#ifndef HUFFMAN_H
#define	HUFFMAN_H
/* ------------------------------------------------------------------------- */


/* ============================================================================
 * Funktions-Prototypen
 * ========================================================================= */

/**
 * Komprimiert den Inhalt der Eingabedatei in_filename und schreibt das 
 * Ergebnis in die Ausgabedatei out_filename. Bei einem Fehler wird das 
 * Programm abgebrochen.
 * 
 * @param in_filename   Name der Eingabedatei
 * @param out_filename  Name der Ausgabedatei
 */
extern void compress(char *in_filename, char *out_filename);

/**
 * Dekomprimiert den Inhalt der Eingabedatei in_filename und 
 * schreibt das Ergebnis in die Ausgabedatei out_filename. Bei einem Fehler
 * wird das Programm abgebrochen.
 * 
 * @param in_filename   Name der Eingabedatei
 * @param out_filename  Name der Ausgabedatei
 */
extern void decompress(char *in_filename, char *out_filename);

/* ------------------------------------------------------------------------- */
#endif	/* HUFFMAN_H */

