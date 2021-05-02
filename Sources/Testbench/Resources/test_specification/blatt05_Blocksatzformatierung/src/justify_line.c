/* ===========================================================================
 * Header-Dateien 
 * ======================================================================== */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "justify_line.h"


/* ===========================================================================
 * Funktionsprototypen
 * ======================================================================== */

/**
 * Formatiert eine Zeile im Blocksatz. Leerzeichen werden gleichmäßig
 * in die vorhandenen Lücken verteilt, so dass die Anzahl der Leerzeichen in
 * keiner Lücke um mehr als 1 von anderen Lücken abweicht. Weiter links
 * stehende Lücken können ein Leerzeichen mehr enthalten als weiter rechts
 * stehende Lücken.
 *
 * @param p_line             Zeile, die formatiert werden soll
 * @param p_justified_line   Zeile im Blocksatz
 * @param spacings           Anzahl der Wortzwischenräume der Zeile (>=0)
 * @param characters         Anzahl aller 'echten' Zeichen in p_line (>=0)
 * @param target_line_length Zielzeilenlänge (>=0)
 */
static void do_justify_line(char *p_line, /*out*/ char *p_justified_line,
        int spacings, int characters, int target_line_length);

/**
 * Ermittelt im übergebenen String die Anzahl der 'echten' Zeichen und die  
 * Anzahl der Wortzwischenräume. Leerzeichen am Anfang oder Ende des Strings
 * werden nicht gezählt.
 *
 * @param p_line            Zeile, aus der die Leerzeichen entfernt werden
 * @param spacings          Anzahl der Wortzwischenräume in der Zeile
 * @param characters        Anzahl der 'echten' Zeichen in der Zeile
 */
static void count_chars_and_spacings(char *p_line, /*out*/int *spacings,
                                     /*out*/ int *characters);


/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/* ----------------------------------------------------------------------------
 * Funktion: justify_line
 * ------------------------------------------------------------------------- */
extern void justify_line(char *p_line, int target_line_length,
                         /*out*/ char *p_justified_line)
{
    /* Anzahl aller Zeichen in p_line */
    int characters = 0;

    /* Anzahl aller Wortzwischenräume der Zeile */
    int spacings = 0;

    /* Berechne Anzahl der 'echten' Zeichen und Wortzwischenräume */
    count_chars_and_spacings(p_line, &spacings, &characters);

    /* Formatiere die Zeile */
    do_justify_line(p_line, p_justified_line, spacings, characters, 
                    target_line_length);
}

/* --------------------------------------------------------------------------
 * Funktion: count_chars_and_spacings
 * ------------------------------------------------------------------------ */
static void count_chars_and_spacings(char *p_line, /*out*/int *spacings,
                                     /*out*/ int *characters)
{
    /* Initialisierung mit true, um führende Leerzeichen zu überspringen */
    bool first_gap = true;

    /* Anzahl Zeichen initialisieren */
    *characters = 0;
    
    /* Anzahl Wortzwischenräume initialisieren */
    *spacings = 0;

    /* Zähle alle 'echten' Zeichen und Lücken (jeweils letztes Leerzeichen) */
    while (*p_line != '\0')
    {
        if (*p_line != ' ')
        {
            /* Aktuelles Zeichen zählen */
            (*characters)++;
            
            /* Das nächste Leerzeichen gehört zu einer 'echten' Lücke */
            first_gap = false;
        }
        else
        {
            if (!first_gap && *(p_line + 1) != '\0' && *(p_line + 1) != ' ')
            {
                /* Wortzwischenraum zählen */
                (*spacings)++;
            }
        }
        p_line++;
    }
}

/* --------------------------------------------------------------------------
 * Funktion: do_justify_line
 * ------------------------------------------------------------------------ */
static void do_justify_line(char *p_line, /*out*/ char *p_justified_line,
                          int spacings, int characters, int target_line_length)
{
    /* Feste Anzahl der Leerzeichen, um die jede Lücke ergänzt werden muss. */
    int fix_spaces = 0;
    
    /* Anzahl Leerzeichen, die zusätzlich zu der festen Anzahl von
     * Leerzeichen in die Lücken gefüllt werden. */
    int add_spaces = 0;
    
    /* Initialisierung mit true, um führende Leerzeichen zu überspringen */
    bool first_gap = true;
    
    /* Wenn es Lücken gibt, Anzahl der einzufügenden Leerzeichen berechnen */
    if (spacings > 0)
    {
        fix_spaces = (target_line_length - characters) / spacings;
        add_spaces = (target_line_length - characters) % spacings;
        
        /* Wenn fix_spaces gleich 0 ist, bedeutet dass, dass die Zielzeilenlänge 
         * nicht ausreicht, um zwischen den Wörtern Leerzeichen einzufügen. Zur
         * Worttrennung muss aber dennoch ein Leerzeichen eingefügt werden. Die 
         * formatierte Zeile wird in diesem Fall länger als die Zielzeilenlänge
         */
        if (fix_spaces == 0) 
        {
            fix_spaces = 1;
            add_spaces = 0;
        } 
    }

    /* Durchlaufe die Zeile und fülle dabei die Lücken auf */
    while (*p_line != '\0')
    {
        if (*p_line != ' ')
        {
            /* Aktuelles Zeichen übernehmen */
            *p_justified_line = *p_line;
            p_justified_line++;
            
            first_gap = false;
        }
        else if (!first_gap && *(p_line + 1) != ' ' && *(p_line + 1) != '\0')
        {
            /* Wenn das letzte Leerzeichen einer 'echten' Lücke erreicht ist, 
            * füge Leerzeichen ein, */             
            int i;
            for (i = 0; i < fix_spaces; i++)
            {
                *p_justified_line = ' ';
                p_justified_line++;
            }

            /* Wenn noch zusätzl. Leerzeichen vorhanden, eins hinzufügen */
            if (add_spaces > 0)
            {
                *p_justified_line = ' ';
                p_justified_line++;
                add_spaces--;
            }
        }
        p_line++;
    }
    *p_justified_line = '\0';
}
