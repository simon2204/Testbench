/**
 * @file
 * In diesem Modul werden Textzeilen im Blocksatz formatiert.
 *
 * @author  Ulrike Griefahn
 * @date    2014-11-10
 */

#ifndef _JUSTIFY_H
#define _JUSTIFY_H
/* ------------------------------------------------------------------------- */


/* ===========================================================================
 * Makros
 * ======================================================================== */

/**
 * Maximale Länge der Textzeilen
 */
#define MAX_LINE_LENGTH 100


/* ===========================================================================
 * Funktionsprototypen
 * ======================================================================== */

 /**
  * Formatiert eine Zeile im Blocksatz. Die Zeilenbreite wird dabei durch die
  * Konstante #MAX_LINE_LENGTH vorgegeben. Die Lücken werden gleichmäßig durch
  * Leerzeichen aufgefüllt. Gibt es nicht gleichviele Leerzeichen für alle
  * Lücken, erhalten die sich weiter links befindlichen Lücken ein Leerzeichen
  * mehr.
  * 
  * Es wird davon ausgegangen, dass die zu formatierende Zeile p_line nicht
  * mehr als #MAX_LINE_LENGTH Zeichen.
  *
  * @param p_line               Zeile, die formatiert werden soll.
  * @param target_line_length   Zielzeilenlänge im Blocksatz
  * @param p_justified_line     Zeile im Blocksatz
  */
extern void justify_line(char *p_line, int target_line_length, 
        /*out*/ char *p_justified_line);

/* ------------------------------------------------------------------------ */
#endif /* _JUSTIFY_H */
