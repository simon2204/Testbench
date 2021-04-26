/* ===========================================================================
 * Header-Dateien einbinden
 * ======================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "data.h"


/* ===========================================================================
 * Makros
 * ======================================================================== */

/**
 * Makro zur Prüfung ob die Speicherallokation erfolgreich war: Ist die
 * Übergebene Variable NULL, wird das Programm mit einer Fehlermeldung
 * abgebrochen.
 */
#define ENSURE_ENOUGH_MEMORY(VAR, FUNCTION) \
{if (VAR == NULL) { printf(FUNCTION ": not enough memory\n"); \
                    exit(EXIT_FAILURE); }}


/* ===========================================================================
 * Strukturdefinitionen
 * ======================================================================== */

/**
 * Testet das Blatt09
 */
struct Data
{
    /**
     * Komponente, die beinhaltet, ob die Struktur geloescht werden sollte
     */
    bool destruction_requested;
};


/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: data_new
 * ------------------------------------------------------------------------ */
extern struct Data *data_new()
{
    /* Speicher für die Struktur allokieren */
    struct Data *p_data =
            (struct Data *) malloc(sizeof (struct Data));
    ENSURE_ENOUGH_MEMORY(p_data, "data_new");

    /* Komponenten der Struktur initialisieren */
    p_data->destruction_requested = false;

    return p_data;
}

/* ---------------------------------------------------------------------------
 * Funktion: data_destroy
 * ------------------------------------------------------------------------ */
extern void data_pretend_destroy(struct Data **pp_data)
{
    if (pp_data != NULL && *pp_data != NULL)
    {

#ifdef DEBUG
        /* Ausgabe der zu löschenden Daten zu Debugzwecken */
        printf("- Loesche struct Data ");
        data_print(*pp_data);
        printf(" \n");
#endif

        (*pp_data)->destruction_requested = true;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: data_destroy
 * ------------------------------------------------------------------------ */
extern void data_destroy(struct Data **pp_data)
{
    if (pp_data != NULL && *pp_data != NULL)
    {

#ifdef DEBUG
        /* Ausgabe der zu löschenden Daten zu Debugzwecken */
        printf("- Loesche struct Data ");
        data_print(*pp_data);
        printf(" \n");
#endif

        free(*pp_data);
        *pp_data = NULL;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: data_get_destruction_requested
 * ------------------------------------------------------------------------ */
extern bool data_get_destruction_requested(const struct Data *p_data)
{
    bool result = false;
    if (p_data != NULL)
    {
        result = p_data->destruction_requested;
    }
    return result;
}

/* ---------------------------------------------------------------------------
 * Funktion: data_set_destruction_requested
 * ------------------------------------------------------------------------ */
extern void data_set_destruction_requested(struct Data *p_data, bool destruction_requested)
{
    p_data->destruction_requested = destruction_requested;
}

/* ---------------------------------------------------------------------------
 * Funktion: data_print
 * ------------------------------------------------------------------------ */
extern void data_print(const struct Data *p_data)
{
    if (p_data != NULL)
    {
        printf("destruction requested: ");
        if (p_data->destruction_requested)
        {
            printf("true");
        }
        else
        {
            printf("false");
        }
    }
}
