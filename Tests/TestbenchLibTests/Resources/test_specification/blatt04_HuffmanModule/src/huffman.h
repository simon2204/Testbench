/**
 * @file
 * In diesem Modul werden die Huffman-Komprimierung und die 
 * Huffman-Dekomprimierung realisiert.
 *
 * @author Ulrike Griefahn, Alexander Schmitz
 * @date 2019-11-07
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
 * @param in Byte-Array mit Input-Daten 
 * @param out Leeres Byte-Array zum Befüllen mit Output-Daten
 */
extern void test_rd_chars_wr_bits(char in[], char out[]);

/**
 * Testet das io-Modul, indem bitwise aus dem Eingangspuffer gelesen wird 
 * und byteweise in den Ausgangspuffer geschrieben wird.
 * 
 * @param in Byte-Array mit Input-Daten 
 * @param out Leeres Byte-Array zum Befüllen mit Output-Daten
 */
extern void test_rd_bits_wr_chars(char in[], char out[]);


/* ------------------------------------------------------------------------- */
#endif	/* HUFFMAN_H */

