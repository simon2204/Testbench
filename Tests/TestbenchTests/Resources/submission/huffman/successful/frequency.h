/**
 * @file
 * Dieses Modul definiert eine Datenstruktur, mit der Zeichen mit einer
 * Häufigkeit in Beziehung gesetzt werden können, und stellt Funktionen
 * zu ihrer Verwaltung zur Verfügung.
 * 
 * @author  Ulrike Griefahn
 * @date    2015-12-17
 */

/* ------------------------------------------------------------------------- */
#ifndef _FREQUENCY_H
#define _FREQUENCY_H
/* ------------------------------------------------------------------------- */

/* ===========================================================================
 * Typdefinitionen
 * ======================================================================== */

/**
 * Setzt Buchstaben mit einer Häufigkeit in Beziehung
 */
typedef struct _FREQUENCY FREQUENCY;


/* ===========================================================================
 * Symbolische Konstanten
 * ======================================================================== */

/**
 * Wert, der an den Aufrufer von get_letter_from_frequency gegeben wird,
 * wenn im Objekt kein Zeichen abgelegt ist.
 */
#define NO_LETTER -1


/* ===========================================================================
 * Funktionsprototypen
 * ======================================================================== */

/**
 * Erzeut eine neue Struktur mit dem übergebenen Buchstaben und der übergebenen 
 * Häufigkeit. 
 *
 * @param letter    der abzulegende Buchstabe
 * @param count     die abzulegende Häufigkeit
 * @return          die neu erzeugte Struktur
 */
extern FREQUENCY *frequency_create(const int letter, const int count);

/**
 * Löscht die Struktur und ihren Inhalt. Setzt den übergebenen Zeiger auf NULL.
 *
 * @param pp_frequency - die zu löschende Struktur
 */
extern void frequency_destroy(FREQUENCY **pp_frequency);

/**
 * Liefert den in der Struktur gespeicherten Buchstaben.
 * 
 * @param p_frequency   die übergebene Struktur
 * @return              Buchstabe der übergebenen Frequency-Struktur
 */
extern int frequency_get_letter(const FREQUENCY *p_frequency);

/**
 * Liefert die Häufigkeit der übergebenen Frequency-Struktur.
 * 
 * @param p_frequency   die übergebene Struktur
 * @return              Häufigkeit der übergebenen Frequency-Struktur oder -1, 
 *                      wenn keine Struktur übergeben wurde.
 */
extern int frequency_get_count(const FREQUENCY *p_frequency);

/**
 * 'ndert den Buchstaben der übergebenen Struktur.
 *
 * @param p_frequency   Zeiger auf die zu ändernde Struktur
 * @param letter        der einzutragende Buchstabe
 */
extern void frequency_set_letter(FREQUENCY *p_frequency, const char letter);

/**
 * Ändert die Häufigkeit in der übergebenen Struktur.
 * 
 * @param p_frequency   - Zeiger auf die zu ändernde Struktur
 * @param count         - die einzutragende Häufigkeit
 */
extern void frequency_set_count(FREQUENCY *p_frequency, const int count);

/**
 * Gibt die Daten der übergebenen Struktur auf dem Bildschirm aus.
 * 
 * @param p_frequency   die auszugebende Struktur
 */
extern void frequency_print(const FREQUENCY *p_frequency);

/* ------------------------------------------------------------------------ */
#endif
