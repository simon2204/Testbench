/**
 * @file
 * In diesem Modul wird der Dateizugriff realisiert. Die zu lesenden und
 * zu schreibenden Daten werden gepuffert, so dass blockweise gelesen und 
 * geschrieben wird. Das Modul bietet Funktionen an, um bit- und byteweise 
 * zu lesen und zu schreiben.
 *
 * @author Ulrike Griefahn
 * @date 2019-11-07
 */

#ifndef IO_H
#define	IO_H
/* ------------------------------------------------------------------------- */

/* ============================================================================
 * Funktions-Prototypen
 * ========================================================================= */

/**
 * Initialisiert den Eingabepuffer mit der übergebenen Zeichenkette
 * 
 * @param text
 */
void init_in(char text[]);

/**
 * Initialisiert den Ausgabepuffer als leer
 */
void init_out(void);


/**
 * Nur zu Testzwecken: Liefert den Ausgabepuffer
 * 
 * @return Ausgabepuffer
 */
extern void get_out_buffer(char buffer[]);


/**
 * Liefert true, wenn noch mindestens ein weiteres Zeichen vorhanden ist.
 * 
 * @return 
 */
extern bool has_next_char(void);

/**
 * Liefert das nächste Zeichen aus dem Eingabestrom
 * @return 
 */
extern unsigned char read_char(void);

/**
 * Schreibt das Zeichen in den Ausgabestrom
 * 
 * @param c 
 */
extern void write_char(unsigned char c);

/**
 * Liefert true, wenn noch mindestens ein weiteres Bit vorhanden ist.
 * 
 * @return 
 */
extern bool has_next_bit(void);

/**
 * Liefert das nächste Bit aus dem Eingabestrom
 * @return 
 */
extern BIT read_bit(void);

/**
 * Schreibt das Zeichen c, das nur den Zahlwert 0 oder 1 haben darf in den 
 * Ausgabestrom
 * 
 * @param c 
 */
extern void write_bit(BIT c);

/* ------------------------------------------------------------------------- */
#endif	/* IO_H */
