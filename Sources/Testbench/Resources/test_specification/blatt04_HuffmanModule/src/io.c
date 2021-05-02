/* ============================================================================
 * Includes
 * ========================================================================= */

#include <string.h>

#include "huffman_common.h"
#include "io.h"


/* ============================================================================
 * Symbolische Konstanten
 * ========================================================================= */

/**
 * Blockgröße, mit der aus der Eingabedatei gelesen und in die Ausgabedatei 
 * geschrieben wird.
 */
#define BUF_SIZE 4096


/* ============================================================================
 * Makros
 * ========================================================================= */

/**
 * Liefert das Bit von C an der Position POS. Ist POS gleich 0, wird  
 * das höchstwertigste Bit geliefert, für POS gleich 7 wird das 
 * niederwertigste Bit geliefert. Es wird davon ausgegangen, dass POS einen
 * Wert zwischen 0 und 7 hat. Ansonsten ist die Rückgabe undefiniert.
 */
#define GET_BIT(C, POS) ((C) >> (7 - (POS)) & (unsigned char) 0x01)

/**
 * Schreibt das Bit BIT an der Position POS in das Zeichen C. Ist POS 
 * gleich 0, wird das höchstwertigste Bit geliefert, für POS gleich 7 wird  
 * das niederwertigste Bit geliefert. Es wird davon ausgegangen, dass POS 
 * einen Wert zwischen 0 und 7 hat. Ansonsten ist die Rückgabe undefiniert.
 */
#define PUT_BIT(C, BIT, POS) ((C) | ((unsigned char) (BIT) << (7 - (POS))))


/* ============================================================================
 * Funktions-Prototypen
 * ========================================================================= */


/* ============================================================================
 * Globale Variablen
 * ========================================================================= */

/** Puffer für den Eingabestrom */
static unsigned char in_buffer[BUF_SIZE];

/** Enthält die erste freie Position des Puffers nach dem letzten Zeichen */
static int last_in_pos;

/** Aktuelle Position im Eingabepuffer */
static int curr_in_pos;

/** Das aktuelle Zeichen im Eingangspuffer */
static unsigned char curr_in_char;

/** Aktuelle Bit-Position im aktuellen Zeichen im Eingangspuffer */
static int curr_in_bit_pos;

/** Puffer für den Ausgabestrom */
static unsigned char out_buffer[BUF_SIZE];

/** Nächste freie Position im Ausgabepuffer */
static int last_out_pos;

/** das aktuell Zeichen im Ausgangspuffer */
static unsigned char curr_out_char;
    
/** die aktuelle Bit-Position im aktuellen Zeichen im Ausgangspuffer */
static int curr_out_bit_pos;


/* ============================================================================
 * Funktions-Definitionen
 * ========================================================================= */

/* ----------------------------------------------------------------------------
 * Initialisieren der Puffer
 * ------------------------------------------------------------------------- */

extern void init_in(char text[])
{
    memcpy(in_buffer, text, strlen(text));
    last_in_pos = (int) strlen(text);
    curr_in_pos = 0;
    
    curr_in_char = '\0';
    curr_in_bit_pos = 8;
}

extern void init_out(void)
{  
    last_out_pos = 0;   
    
    curr_out_char = '\0';
    curr_out_bit_pos = 0;
}

/* ----------------------------------------------------------------------------
 * nur zu Testzwecken
 * ------------------------------------------------------------------------- */

extern void get_out_buffer(char buffer[])
{
    int i;
    
    if (curr_out_bit_pos > 0) 
    {
        write_char((unsigned char) curr_out_char);
        curr_out_bit_pos = 0;
        curr_out_char = '\0';
    }
    
    for (i = 0; i < last_out_pos; i++)
    {
        buffer[i] = (char) out_buffer[i];
    }
}


/* ----------------------------------------------------------------------------
 * Byteweises Lesen und Schreiben
 * ------------------------------------------------------------------------- */

extern bool has_next_char(void)
{
    return curr_in_pos < last_in_pos;
}

extern unsigned char read_char(void)
{
    /* Nächstes Zeichen aus dem Buffer lesen */
    unsigned char c = in_buffer[curr_in_pos];
    curr_in_pos++;

    return c;
}

extern void write_char(unsigned char c)
{
    /* 
     * Schreibt das Zeichen in den Puffer. 
     */
    /* Zeichen an nächste freie Pufferposition schreiben */
    out_buffer[last_out_pos] = c;
    last_out_pos++;
 }

/* ----------------------------------------------------------------------------
 * Bitweises Lesen und Schreiben
 * ------------------------------------------------------------------------- */

extern bool has_next_bit(void)
{
    return curr_in_bit_pos < 8 || has_next_char();
}

extern BIT read_bit(void)
{
    /* 
     * Liest so lange aus dem Puffer, bis dieser leer ist. Ist dieser leer,
     * wird der Inhalt des Puffers aus der Eingabedatei erneut gefüllt.
     */

    /* das aktuelle Bit */
    BIT bit;
    
    /* das allererste Zeichen holen, weil statische Variable nicht mit 
     * Rückgabe einer Funktion initialisiert werden kann */   
    if (curr_in_bit_pos % 8 == 0 && has_next_char())
    {
        curr_in_char = read_char();
        curr_in_bit_pos = 0;
    }
    
    /* Bit aus dem aktuellen Zeichen auslesen und weitersetzen */
    bit = GET_BIT(curr_in_char, curr_in_bit_pos);
    curr_in_bit_pos++;
    
    return bit;
}

extern void write_bit(BIT bit)
{
    /* 
     * Schreibt so lange in den Puffer, bis dieser voll ist. Ist dieser voll,
     * wird der Inhalt des Puffers in die Ausgabedatei geschrieben und der 
     * Puffer erneut gefüllt.
     */
    
    /* Bit im aktuellen Zeichen setzen */
    curr_out_char = PUT_BIT(curr_out_char, bit, curr_out_bit_pos);
    curr_out_bit_pos++;
    
    /* Wenn Byte voll, dann Zeichen schreiben */
    if (curr_out_bit_pos == 8)
    {
        write_char((unsigned char) curr_out_char);
        curr_out_bit_pos = 0;
        curr_out_char = '\0';
    }
}
