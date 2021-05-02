/**
 * @file extern_prototypes.c (blatt07)
 *
 * @brief
 * Dieses Modul enthaelt die Prototypen der in den Modulen verwendeten 
 * externen Funktionen und wird bei der statischen Code-Pruefung mit 
 * Splint - insbesondere unter Verwendung des Flag "exportlocal" - 
 * verwendet. Ziel ist es, die vom Benutzer definierten Funktionen
 * aufzudecken, die weder mit dem extern- noch mit dem static-
 * Modifikator versehen wurden (sind also implizit "extern"), d.h. sie 
 * werden durch ensprechende Warnhinweise, die ins Auswertungsprotokoll
 * geschrieben werden, aufgezeigt, bspw. 
 * "Function exported but not used outside btree: btree_print_rek
 * A declaration is exported, but not used outside this module.
 * Declaration can use static qualifier."
 *        
 * Fuer externe Funktionen, die "scheinbar" nicht von aussen aufgerufen 
 * werden, werden die Warnmeldungen hingegegen unterdrueckt.
 *
 * @author  Ulrike Griefahn, Christopher Huber
 * @date    2015-09-09
 */

/* ===========================================================================
 * Includes
 * ======================================================================== */

#include <stdbool.h>
 

/* ===========================================================================
 * Funktionsprototypen 
 * ======================================================================== */
 
/* ---------------------------------------------------------------------------
 * io
 * ------------------------------------------------------------------------ */
extern void open_infile(char filename[]);
extern void close_infile(void);
extern bool is_end_of_infile(char c);
extern int read_char_from_infile(void);
extern void open_outfile(char filename[]);
extern void close_outfile(void);
extern void write_char_to_outfile(char c);

/* ---------------------------------------------------------------------------
 * huffman
 * ------------------------------------------------------------------------ */
extern void compress(char in_filename[], char out_filename[]);
extern void decompress(char in_filename[], char out_filename[]);
