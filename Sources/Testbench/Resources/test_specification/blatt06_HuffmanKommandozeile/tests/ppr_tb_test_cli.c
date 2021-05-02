/**
 * @file
 * Dieses Modul enthaelt Testfaelle, mit denen die Funktion des Command 
 * Line Interfaces getestet wird.
 *
 * @author  Christopher Huber
 * @date    2015-09-09
 */


/* ============================================================================
 * Header-Dateien
 * ========================================================================= */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#ifdef TESTBENCH
#include "ppr_tb_logging.h"
#endif


/* ============================================================================
 * Funktionsprotoytpen
 * ========================================================================= */

/**
 * max. zulaessiger Rueckgabewert im Fehlerfall
 */
#define RETVAL_MAX 4

bool ppr_tb_compare_retvals(int expected, int result);
bool ppr_tb_compare_files(char *expected_filename, char *result_filename, char *test_case);


/* ============================================================================
 * Funktionsdefinitionen
 * ========================================================================= */

/* ---------------------------------------------------------------------------
 * Funktion: main
 * ------------------------------------------------------------------------- */

#ifndef TESTBENCH
int main(int argc, char **argv)
{    
    if (strcmp(argv[1], "-init") == 0)
    {
        printf("%%SUITE_STARTING%% cli_testsuite\n");
        printf("%%SUITE_STARTED%%\n");
    }
    if (strcmp(argv[1], "-end") == 0)
    {
        printf("%%SUITE_FINISHED%% time=0\n");
    }
    if (strcmp(argv[1], "-start") == 0)
    {
        printf("%%TEST_STARTED%% %s (cli_testsuite)\n", argv[2]);
    }
    if (strcmp(argv[1], "-finish") == 0)
    {
        printf("%%TEST_FINISHED%% time=0 %s (cli_testsuite)\n", argv[2]);
    }
    if (strcmp(argv[1], "-retval") == 0)
    {
        if (ppr_tb_compare_retvals(atoi(argv[2]), atoi(argv[3])))
        {
            printf("[OK]\n");
        }
        else
        {
            printf("[FAILED]\n");
            printf("%%TEST_FAILED%% time=0 testname=%s (cli_testsuite) message=wrong return value\n", argv[4]);
        }
    }
    if (strcmp(argv[1], "-cmp") == 0)
    {
        char *expected_filename = argv[2];
        char *result_filename = argv[3];
        
        if (ppr_tb_compare_files(expected_filename, result_filename, argv[4]))
        {
            printf("[OK]\n");
        }
        else
        {
            printf("[FAILED]\n");
            printf("%%TEST_FAILED%% time=0 testname=%s (cli_testsuite) message=files are not equal\n", argv[4]);
        }
    }

    return (EXIT_SUCCESS);
}
#endif

#ifdef TESTBENCH

int main(int argc, char **argv)
{
    if (strcmp(argv[1], "-summary") == 0)
    {
	ppr_tb_write_total_assert(atoi(argv[2]));
        ppr_tb_write_summary("", argv[3]);
    }
    else if (strcmp(argv[1], "-retval") == 0)
    {
        if (ppr_tb_compare_retvals(atoi(argv[2]), atoi(argv[3])))
        {
            ppr_tb_log_assert();
        }
    }
    else
    {
        char *expected_filename = argv[1];
        char *result_filename = argv[2];
        
        if (ppr_tb_compare_files(expected_filename, result_filename, argv[4]))
        {
            ppr_tb_log_assert();
        }
    }

    return (EXIT_SUCCESS);
}
#endif

/* ---------------------------------------------------------------------------
 * Funktion: ppr_tb_compare_retvals
 * ------------------------------------------------------------------------- */
bool ppr_tb_compare_retvals(int expected, int result)
{ /* Rueckgabewert der Benutzeranwendung wird ausgewertet */

    bool ok;
    
    /*
     * 0: Erfolgreiche Ausfuehrung
	 * 1: Unbekannter Fehler
	 * 2: Fehler in der Kommandozeile
	 * 3: Datei- bzw. IO-Fehler
	 * 4: Fehler beim Komprimieren oder Dekomprimieren 
     */
    
    if (expected == result)
    {
        /* ------------------------------------------------------------
         * erwartet: 0, geliefert: 0
         *   ODER
         * erwartet: 1, geliefert: 1
         *   ODER
         * erwartet: 2, geliefert: 2
         *   ODER
         * erwartet: 3, geliefert: 3
         *   ODER
         * erwartet: 4, geliefert: 4
         * --------------------------------------------------------- */
        printf("\n[OK] Exit Status: %d\n", result);
        ok = true;
    }
    else if ((result > RETVAL_MAX) || (result < 0))
    {
        /* ------------------------------------------------------------
         * result außerhalb der zulaessigen return Werte
         * --------------------------------------------------------- */
        printf("\n[ERROR] Exit Status: %d\n", result);
        ok = false;
    }
    else if (expected != result)
    {
		/* ------------------------------------------------------------
		 * erwarteter Wert entspricht nicht dem gelieferten Wert.
		 * --------------------------------------------------------- */
        printf("\n[ERROR] Exit Status:\n");
        printf("        expected:<[\n");
        printf("        %d\n", expected);
        printf("        ]> but was:<[\n");
        printf("        %d", result);
        printf("\n        ]>\n");
        
        ok = false;
    }
    else
    {
        printf("\nError Testbench\n");
        ok = false;
    }
    
    return ok;
}

/* ---------------------------------------------------------------------------
 * Funktion: ppr_tb_compare_files
 * ------------------------------------------------------------------------- */
bool ppr_tb_compare_files(char *expected_filename, char *result_filename, char *test_case)
{
    bool ok;

    FILE *expected_stream = fopen(expected_filename, "rb");
    if (expected_stream == NULL)
    {
        printf("[ERROR] Die Datei %s konnte nicht geoeffnet werden.\n",
               expected_filename);
        printf("%%TEST_FINISHED%% time=0 %s (cli_testsuite)\n", test_case);
        exit(EXIT_SUCCESS);
    }

    FILE *result_stream = fopen(result_filename, "rb");
    if (result_stream == NULL)
    {
        printf("[ERROR] Die Datei %s konnte nicht geoeffnet werden.\n",
               result_filename);
        printf("%%TEST_FINISHED%% time=0 %s (cli_testsuite)\n", test_case);
        exit(EXIT_SUCCESS);
    }

    int expected_char = fgetc(expected_stream);
    int result_char = fgetc(result_stream);

    int line = 1; /* Die Position des aktuellen Zeichens */
    int col = 1;

    while (expected_char != EOF && result_char != EOF
            && (expected_char == result_char
            || (expected_char == 10 && result_char == 13)
            || (expected_char == 13 && result_char == 10)))
    {
        if (expected_char == 10 || expected_char == 13)
        {
            line++;
            col = 0;
        }
        if (expected_char == 13)
        {
            expected_char = fgetc(expected_stream);
        }
        if (result_char == 13)
        {
            result_char = fgetc(result_stream);
        }
        expected_char = fgetc(expected_stream);
        result_char = fgetc(result_stream);
        col++;
    }

    if (expected_char == EOF && result_char == EOF)
    {
        printf("[OK] Die Dateien %s und %s sind identisch.\n",
               expected_filename, result_filename);
        ok = true;
    }
    else
    {
        char cmd[200];
        printf("[ERROR] Die Dateien %s und %s sind NICHT identisch.\n"
               "        Sie unterscheiden sich ab Zeile %d und Spalte %d: "
               "ASCII-Codes: '%3d' - '%3d'\n\n",
               expected_filename, result_filename, line, col, 
               expected_char, result_char);
        printf("Ausgabe des IST-Ergebnisses, Datei %s:\n", 
               result_filename);
        printf("------------------------------------------------------\n");
        fflush(stdout);
        strcpy(cmd, "cat -nvET ");
        strcat(cmd, result_filename);
        system(cmd);

        printf("\nVergleich von IST- und SOLL-Ergebnis\n");
        printf("------------------------------------------------------\n");
        fflush(stdout);
        strcpy(cmd, "diff ");
        strcat(cmd, expected_filename);
        strcat(cmd, " ");
        strcat(cmd, result_filename);
        system(cmd);
        printf("------------------------------------------------------\n");
        fflush(stdout);

        ok = false;
    }

    fclose(expected_stream);
    fclose(result_stream);
    
    return ok;
}
