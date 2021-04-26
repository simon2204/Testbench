/**
 * @mainpage Bin�rer Heap
 *
 * Dieses Projekt realisiert einen bin�ren Heap, dessen Elemente  
 * void-Zeiger sind.
 * 
 * @file
 * Dieses Modul realisiert einen bin�ren Heap und stellt Funktionen zur
 * Verf�gung, um Elemente einzuf�gen und l�schen zu k�nnen.
 *
 * @author Ulrike Griefahn
 * @date 2012-12-19
 */

/* ------------------------------------------------------------------------ */
#ifndef _BINARY_HEAP_H
#define _BINARY_HEAP_H
/* ------------------------------------------------------------------------ */


/* ===========================================================================
 * Header-Dateien
 * ======================================================================== */

#include <stdbool.h>


/* ===========================================================================
 * Typ-Definitionen
 * ======================================================================== */

/**
 * Typ f�r Zeiger auf Funktionen, die Heap-Elemente vergleichen
 */
typedef int (*HEAP_ELEM_COMP)(void *, void *);

/**
 * Typ f�r Zeiger auf Funktionen, die eine textuelle Darstellung der 
 * Heap-Elemente liefern
 */
typedef void (*HEAP_ELEM_PRINT)(void *);


/* ===========================================================================
 * Funktionsprototypen
 * ======================================================================== */

/**
 * Initialisiert den Heap.
 * 
 * @param compare_fct   Zeiger auf Funktion zum Vergleich der Heap-Elemente
 * @param print_fct     Zeiger auf Funktion f�r textuelle Ausgabe eines
 *                      Heap-Elements
 */
extern void heap_init(HEAP_ELEM_COMP compare_fct, HEAP_ELEM_PRINT print_fct);


/**
 * L�scht den Heap, d.h. gibt den Speicherplatz frei und setzt alle globalen
 * Variablen zur�ck.
 */
extern void heap_destroy(void);

/**
 * Liefert die Anzahl der Elemente im Heap.
 * 
 * @return      Anzahl Elemente im Heap
 */
extern int heap_get_size(void);

/**
 * F�gt ein neues Element in den Heap ein.
 *
 * @param element - das einzuf�gende Element
 */
extern void heap_insert(void *element);


/**
 * Entfernt das kleinste Element aus dem Heap (Wurzelement) und liefert es
 * im Parameter min_element zur�ck.
 *
 * @param min_element - das kleinste Element des Heaps, wenn der Heap nicht
 *              leer ist.
 * @return true, wenn ein Element zur�ckgegeben werden konnte
 *              false, wenn der Heap bei Aufruf bereits leer ist
 */
extern bool heap_extract_min(void **min_element);


/**
 * (nur zu Testzwecken) Ausgabe der Heap-Elemente in Baumdarstellung
 */
extern void heap_print(void);

/* ------------------------------------------------------------------------ */
#endif
