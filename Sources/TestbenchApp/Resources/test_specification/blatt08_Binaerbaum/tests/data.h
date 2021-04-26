/**
 * @file
 * Dieses Modul definiert eine Datenstruktur, die das Blatt09 auf korrekte
 * Funktion testet.
 * 
 * @author  Carsten Carow
 * @date    2013-12-04
 */

/* ------------------------------------------------------------------------- */
#ifndef _SIMPLE_TESTER_H
#define _SIMPLE_TESTER_H
/* ------------------------------------------------------------------------- */

#include <stdbool.h>

/**
 * Erzeut eine neue Struktur.
 * @return          die neu erzeugte Struktur
 */
extern struct Data *data_new();

/**
 * Tut so als wenn die Struktur und ihr Inhalt geloescht wird.
 * Setzt den Wert "destruction_requested" auf true.
 *
 * @param pp_data - die zu löschende Struktur
 */
extern void data_pretend_destroy(struct Data **pp_data);

/**
 * Löscht die Struktur und ihren Inhalt. Setzt den Übergebenen Zeiger auf NULL.
 *
 * @param pp_data - die zu löschende Struktur
 */
extern void data_destroy(struct Data **pp_data);

/**
 * Liefert den Wert "destruction_requested".
 * 
 * @param p_data   die Übergebene Struktur
 * @return         True, falls die Loeschung angefordert wurde. Sonst false.
 */
extern bool data_get_destruction_requested(const struct Data *p_data);

/**
 * Setzt den Wert "destruction_requested".
 * 
 * @param p_data     die Ã¼bergebene Struktur
 * @param destruction_requested  Den boolschen Wert, der zugewiesen werden soll.

 */
extern void data_set_destruction_requested(struct Data *p_data, bool destruction_requested);

/**
 * Gibt die Daten der übergebenen Struktur auf dem Bildschirm aus.
 * 
 * @param p_data   die auszugebende Struktur
 */
extern void data_print(const struct Data *p_data);

/* ------------------------------------------------------------------------ */
#endif
