/**
 * @file
 * Dieses Modul stellt allgemeine Definitionen zur Verfügung
 *
 * @author  Ulrike Griefahn
 * @date    2015-08-28
 */

#ifndef HUFFMAN_COMMON_H
#define HUFFMAN_COMMON_H
/* ------------------------------------------------------------------------ */

/* ===========================================================================
 * Includes
 * ======================================================================== */

#include <stdbool.h>
#include <stdlib.h>


/* ===========================================================================
 * Aufzählungstypen
 * ======================================================================== */

/**
 * Der Typ ist auf 0 und 1 beschränkt.
 */
typedef enum
{
    BIT0 = 0,
    BIT1 = 1
} BIT;


/* ===========================================================================
 * Debug-Anweisungen
 * ======================================================================== */

#ifdef DEBUG
/** Präprozessor-Makro für Debugausgaben */
#include <stdio.h>
#define CPRINT(E) printf(#E " = %c\n", E)
#define DPRINT(E) printf(#E " = %d\n", E)
#define FPRINT(E) printf(#E " = %f\n", E)
#define SPRINT(E) printf(#E " = %s\n", E)
#define XPRINT(E) printf(#E " = %x\n", E)
#else
/** Präprozessor-Makro für Debugausgaben (nicht definiert) */
#define CPRINT(E)
#define DPRINT(E)
#define FPRINT(E)
#define SPRINT(E)
#define XPRINT(E)
#endif

/* ------------------------------------------------------------------------ */
#endif	/* HUFFMAN_COMMON_H */

