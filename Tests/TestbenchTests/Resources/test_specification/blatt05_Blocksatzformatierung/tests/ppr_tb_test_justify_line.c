/**
 * @file
 * Dieses Modul enthaelt Testfaelle, mit denen die zu realisierenden Funktionen
 * zur Blocksatzformatierung getestet werden.
 *
 * @author  Ulrike Griefahn
 * @date    2014-02-03
 */

/* ============================================================================
 * Header-Dateien
 * ========================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifdef TESTBENCH
#include "ppr_tb_logging.h"
#endif


/* ============================================================================
 * Vorgaben der Aufgabenstellung
 * ========================================================================= */

#define MAX_LINE_LENGTH 100
#define TARGET_LINE_LENGTH 80

extern void justify_line(char *, int, char *);


/* ============================================================================
 * Funktionsprototypen (Tests)
 * ========================================================================= */

/**
 * Wird aufgerufen, falls das erwartete mit dem gelieferten Ergebnis
 * uebereinstimmt.
 */
void ppr_tb_print_ok(void);

/**
 * Vergleicht die Elemente, die als String uebergeben werden, auf
 * Gleichheit. Falls sich die Elemente unterscheiden, erfolgt eine
 * entsprechende Ausgabe auf dem Bildschirm.
 *
 * @param input     Zeile, die formatiert wurde
 * @param expected  erwartete Zeile im Blocksatz
 * @param result    berechnete Zeile im Blocksatz
 */
static void ppr_tb_assert_equal(char *input, char *expected, char *result);


/* ============================================================================
 * Testbench - Funktionsdefinitionen (CUnit Test Suite)
 * ========================================================================= */

/* ----------------------------------------------------------------------------
 * Funktion: ppr_tb_print_ok
 * ------------------------------------------------------------------------- */
void ppr_tb_print_ok(void)
{   
    printf("[OK]\n\n");
    fflush(stdout);
              
#ifdef TESTBENCH
    ppr_tb_log_assert();
#endif
}

/* ----------------------------------------------------------------------------
 * Funktion: ppr_tb_assert_equal
 * ------------------------------------------------------------------------- */
static void ppr_tb_assert_equal(char *input, char *expected, char *result)
{
    if (strcmp(expected, result) == 0)
    {
        ppr_tb_print_ok();
    }
    else
    {
        printf("\n[ERROR]\n"
               "   Aufruf von justify_line(...) mit Zeile\n"
               "    \"%s\"\n"
               "   expected:<[\n"
               "    \"%s\"\n"
               "   ]> but was:<[\n"
               "    \"%s\"\n"
               "   ]>\n", input, expected, result);

        fflush(stdout);
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: ppr_tb_test_justify_line 
 * ------------------------------------------------------------------------- */
void ppr_tb_test_justify_line()
{
    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 1: "
               "Zeile mit 70 Zeichen, 10 Leerzeichen in 6 Wortluecken verteilen\n");
        {
            char input[]    = "123456789 345678901 567890123 789012345 901234567 123456789 234567890";
            char expected[] = "123456789   345678901   567890123   789012345   901234567   123456789  234567890";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, TARGET_LINE_LENGTH, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }
    
    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 2: "
               "Zeile mit 76 Zeichen, 6 Wortlücken, Zielzeilenlänge 80\n");
        {
            char input[]    = "123456789 12345678901  4567890123 56789012345  8901234567  0123456789  234567890123456";
            char expected[] = "123456789 12345678901 4567890123 56789012345 8901234567 0123456789 234567890123456";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, TARGET_LINE_LENGTH, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }

    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 3: "
               "Zeile mit einem Leerzeichen zu Beginn\n");
        {
            char input[] = " 1234567 3456789 4567890 56789012 78901234 901234567 234567890";
            char expected[] = "1234567     3456789    4567890    56789012    78901234    901234567    234567890";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, TARGET_LINE_LENGTH, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }

    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 4: "
               "Zeile mit mehreren Leerzeichen zu Beginn\n");
        {
            char input[] = "   1234567 3456789 4567890 56789012 78901234 901234567 234567890";
            char expected[] = "1234567     3456789    4567890    56789012    78901234    901234567    234567890";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, TARGET_LINE_LENGTH, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }

    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 5:"
               "Zeile mit einem abschliessenden Leerzeichen\n");
        {
            char input[] = "123456789 345678901 567890123 789012345 901234567 123456789 234567890 ";
            char expected[] = "123456789   345678901   567890123   789012345   901234567   123456789  234567890";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, TARGET_LINE_LENGTH, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }

    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 6: "
               "Zeile mit mehreren abschliessenden Leerzeichen\n");
        {
            char input[] = "123456789 345678901 567890123 789012345 901234567 123456789 234567890     ";
            char expected[] = "123456789   345678901   567890123   789012345   901234567   123456789  234567890";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, TARGET_LINE_LENGTH, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }

    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 7: "
               "Zeile mit mehreren vergroesserten Luecken in der Mitte\n");
        {
            char input[] = "123456789 345678901   567890123 789012345     901234567 123456789 234567890";
            char expected[] = "123456789   345678901   567890123   789012345   901234567   123456789  234567890";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, TARGET_LINE_LENGTH, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }

    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 8: "
               "Zeile mit mehreren vergroesserten Luecken am Anfang, Ende und in der Mitte\n");
        {
            char input[] = "   123456789 567890123   901234567    345678901     789012345 1234   ";
            char expected[] = "123456789       567890123      901234567      345678901      789012345      1234";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, TARGET_LINE_LENGTH, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }
    
    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 9: "
               "Zielzeilenlänge 72\n");
        {
            char input[] = "   123456789 567890123   901234567    345678901     789012345 1234   ";
            char expected[] = "123456789     567890123     901234567     345678901    789012345    1234";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, 72, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }
    
    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 10: "
               "Leerzeile --> Keine Formatierung\n");
        {
            char input[] = "";
            char expected[] = "";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, TARGET_LINE_LENGTH, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }

    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 11: "
               "Zeile mit einem Leerzeichen --> \"\"\n");
        {
            char input[] = " ";
            char expected[] = "";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, TARGET_LINE_LENGTH, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }

    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 12: "
               "Zeile mit mehreren Leerzeichen --> \"\"\n");
        {
            char input[] = "               ";
            char expected[] = "";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, TARGET_LINE_LENGTH, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }

    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 13: "
               "Zeile mit maximaler Laenge --> keine Formatierung\n");
        {
            char input[] = "123456789 123456789 123456789 123456789 123456789 123456789 123456789 1234567890";
            char expected[] = "123456789 123456789 123456789 123456789 123456789 123456789 123456789 1234567890";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, TARGET_LINE_LENGTH, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }

    {
        printf("-------------------------------------------------------------------"
               "\nTestfall 14: "
               "Zeile mit einem Wort und der maximalen Laenge --> keine Formatierung\n");
        {
            char input[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
            char expected[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
            char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
            justify_line(input, TARGET_LINE_LENGTH, result);
            ppr_tb_assert_equal(input, expected, result);
        }
    }
}



/* ----------------------------------------------------------------------------
 * Funktion: main
 * ------------------------------------------------------------------------- */
#ifndef TESTBENCH
int main(void)
{
    printf("%%SUITE_STARTING%% justify_line_testsuite\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  test_justify_line (justify_line_testsuite)\n");
    ppr_tb_test_justify_line();
    printf("%%TEST_FINISHED%% time=0 test_justify_line (justify_line_testsuite)\n");
    
    printf("%%SUITE_FINISHED%% time=0\n");
    
    return (EXIT_SUCCESS);
}
#endif

#ifdef TESTBENCH
int main(int argc, char **argv)
{   
    ppr_tb_write_total_assert(14);
    ppr_tb_test_justify_line();
    
    ppr_tb_write_summary("", argv[1]);
    
    return (EXIT_SUCCESS);
}
#endif
