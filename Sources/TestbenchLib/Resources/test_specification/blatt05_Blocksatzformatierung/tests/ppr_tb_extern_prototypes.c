/**
 * @file extern_prototypes.c (blatt06)
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
 * @author  Ulrike Griefahn, Franz Bachmann
 * @date    2013-04-17
 */

 
/* ===========================================================================
 * Funktionsprototypen 
 * ======================================================================== */
 
/* ---------------------------------------------------------------------------
 * justify_line
 * ------------------------------------------------------------------------ */
extern void justify_line(char *p_line, int target_line_length,
                         /*out*/ char *p_justified_line);
