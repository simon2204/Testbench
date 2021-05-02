/**
 * @file
 * In diesem Modul werden die Huffman-Komprimierung und die 
 * Huffman-Dekomprimierung realisiert.
 *
 * @author Ulrike Griefahn
 * @date 2017-01-12
 */

#ifndef HUFFMAN_H
#define	HUFFMAN_H
/* ------------------------------------------------------------------------- */


/* ============================================================================
 * Funktions-Prototypen
 * ========================================================================= */

/**
 * Testet das io-Modul, indem bytewise aus dem Eingangspuffer gelesen wird 
 * und bitweise in den Ausgangspuffer geschrieben wird.
 * 
 * @param in_filename Voller Dateiname (mit Pfad) des Input-File 
 * @param out_filename Voller Dateiname (mit Pfad) des Output-File
 */
extern void test_rd_chars_wr_bits(char in_filename[], char out_filename[]);

/**
 * Testet das io-Modul, indem bitwise aus dem Eingangspuffer gelesen wird 
 * und byteweise in den Ausgangspuffer geschrieben wird.
 * 
 * @param in_filename Voller Dateiname (mit Pfad) des Input-File 
 * @param out_filename Voller Dateiname (mit Pfad) des Output-File
 */
extern void test_rd_bits_wr_chars(char in_filename[], char out_filename[]);

/* ------------------------------------------------------------------------- */
#endif	/* HUFFMAN_H */

