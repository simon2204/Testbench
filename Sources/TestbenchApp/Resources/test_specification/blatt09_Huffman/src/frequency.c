/* ===========================================================================
 * Header-Dateien einbinden
 * ======================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "huffman_common.h"
#include "frequency.h"


/* ===========================================================================
 * Makros
 * ======================================================================== */

/**
 * Makro zur Prüfung ob die Speicherallokation erfolgreich war: Ist die
 * übergebene Variable NULL, wird das Programm mit einer Fehlermeldung
 * abgebrochen.
 */
#define ASSERT_NOT_NULL(VAR) \
{if (VAR == NULL) { \
    fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno));\
    exit(EXIT_FAILURE); \
}}


/* ===========================================================================
 * Strukturdefinitionen
 * ======================================================================== */

/**
 * Setzt Buchstaben mit einer Häufigkeit in Beziehung
 */
struct _FREQUENCY
{
    /**
     * Komponente für den Buchstaben
     */
    int letter;
    /**
     * Komponente für die Anzahl der Vorkommen des Buchstabens
     */
    int count;
};


/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: frequency_create
 * ------------------------------------------------------------------------ */
extern FREQUENCY *frequency_create(const int letter, const int count)
{
    /* Speicher f�r die Struktur allokieren */
    FREQUENCY *p_frequency = malloc(sizeof (FREQUENCY));
    ASSERT_NOT_NULL(p_frequency);

    /* Komponenten der Struktur initialisieren */
    p_frequency->letter = letter;
    p_frequency->count = count;

    return p_frequency;
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_destroy
 * ------------------------------------------------------------------------ */
extern void frequency_destroy(FREQUENCY **pp_frequency)
{
    if (pp_frequency != NULL && *pp_frequency != NULL)
    {

#ifdef DEBUG
        /* Ausgabe der zu löschenden Daten zu Debugzwecken */
        printf("- Loesche struct Frequency ");
        frequency_print(*pp_frequency);
        printf(" \n");
#endif
        free(*pp_frequency);
        *pp_frequency = NULL;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_get_letter
 * ------------------------------------------------------------------------ */
extern int frequency_get_letter(const FREQUENCY *p_frequency)
{
    if (p_frequency != NULL)
    {
        return p_frequency->letter;
    }

    return NO_LETTER;
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_get_count
 * ------------------------------------------------------------------------ */
extern int frequency_get_count(const FREQUENCY *p_frequency)
{
    if (p_frequency != NULL)
    {
        return p_frequency->count;
    }

    return -1;
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_set_letter
 * ------------------------------------------------------------------------ */
extern void frequency_set_letter(FREQUENCY *p_frequency, 
                                    const char letter)
{
    if (p_frequency != NULL)
    {
        p_frequency->letter = letter;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_set_count
 * ------------------------------------------------------------------------ */
extern void frequency_set_count(FREQUENCY *p_frequency, 
                                   const int count)
{
    if (p_frequency != NULL)
    {
        p_frequency->count = count;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_print
 * ------------------------------------------------------------------------ */
extern void frequency_print(const FREQUENCY *p_frequency)
{
    if (p_frequency != NULL)
    {
        printf("[%d: %d]", p_frequency->letter, p_frequency->count);
        
    }
}
