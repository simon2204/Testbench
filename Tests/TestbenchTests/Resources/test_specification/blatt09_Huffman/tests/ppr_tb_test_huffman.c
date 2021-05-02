/**
 * @file
 * Dieses Modul enthaelt Testfaelle, mit denen die Funktionen der Huffman-
 * Kodierung getestet werden.
 *
 * @author  Ulrike Griefahn
 * @date    2014-02-04
 */


/* ============================================================================
 * Header-Dateien
 * ========================================================================= */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>    /* MS-DOS/WINDOWS */

#ifdef TESTBENCH
#include "ppr_tb_logging.h"
#endif


/* ============================================================================
 * Funktionsprotoytpen
 * ========================================================================= */

bool ppr_tb_compare_filesizes(
        char *in_filename, char *hc_filename, char *hd_filename);
bool ppr_tb_compare_files(char *in_filename, char *hd_filename);


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
        printf("%%SUITE_STARTING%% huffman_testsuite\n");
        printf("%%SUITE_STARTED%%\n");
    }
    if (strcmp(argv[1], "-end") == 0)
    {
        printf("%%SUITE_FINISHED%% time=0\n");
    }
    if (strcmp(argv[1], "-start") == 0)
    {
        printf("%%TEST_STARTED%% %s (huffman_testsuite)\n", argv[2]);
    }
    if (strcmp(argv[1], "-finish") == 0)
    {
        printf("%%TEST_FINISHED%% time=0 %s (huffman_testsuite)\n", argv[2]);
    }
    if (strcmp(argv[1], "-cmp") == 0)
    {
        char *in_filename = argv[2];
        char *hc_filename = argv[3];
        char *hd_filename = argv[4];

        if (ppr_tb_compare_filesizes(in_filename, hc_filename, hd_filename)
                && ppr_tb_compare_files(in_filename, hd_filename))
        {
            printf("[OK]\n");
        }
        else
        {
            printf("[FAILED]\n");
            printf("%%TEST_FAILED%% time=0 testname=%s (huffman_testsuite) message=compression and decompression do not work correct\n", argv[5]);
        }
    }
    
    return(EXIT_SUCCESS);
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
    else
    {
        char *in_filename = argv[1];
        char *hc_filename = argv[2];
        char *hd_filename = argv[3];

        if (ppr_tb_compare_filesizes(in_filename, hc_filename, hd_filename)
                && ppr_tb_compare_files(in_filename, hd_filename))
        {
            ppr_tb_log_assert();
        }
    }
    
    return(EXIT_SUCCESS);
}
#endif


/* ---------------------------------------------------------------------------
 * Funktion: ppr_tb_compare_filesizes
 * ------------------------------------------------------------------------- */
bool ppr_tb_compare_filesizes(
        char *in_filename, char *hc_filename, char *hd_filename)
{       
    struct stat attribut; /* Struktur f�r Datei-Eigenschaften */
    int size_infile; /* Gr��e der �bergebenen Dateien */
    int size_hcfile;
    int size_hdfile;
	bool ok = true;
    
    printf("Groesse der Dateien\n");

    if (stat(in_filename, &attribut) == -1)
    {
        size_infile = -1;
        printf("[ERROR] * %s: existiert nicht\n", in_filename);
        ok = false;
    }
    else
    {
        size_infile = attribut.st_size;
        printf(" * %-25s: %8d\n", in_filename, size_infile);
    }

    if (stat(hc_filename, &attribut) == -1)
    {
        size_hcfile = -1;
        printf("[ERROR] * %s: existiert nicht\n", hc_filename);
        ok = false;
    }
    else
    {
        size_hcfile = attribut.st_size;
        printf(" * %-25s: %8d\n", hc_filename, size_hcfile);
    }

    if (stat(hd_filename, &attribut) == -1)
    {
        size_hdfile = -1;
        printf("[ERROR] * %s: existiert nicht\n", hd_filename);
        ok = false;
    }
    else
    {
        size_hdfile = attribut.st_size;
        printf(" * %-25s: %8d\n", hd_filename, size_hdfile);
    }

    if (size_infile != -1 && size_hcfile != -1
            && size_infile > 2000 && size_infile < size_hcfile)
    {
        printf("[ERROR] Die komprimierte Datei %s ist groesser als die "
               "Originaldatei %s.\n", hc_filename, in_filename);
        ok = false;
    }

    if (size_infile != -1 && size_hdfile != -1
            && size_infile != size_hdfile)
    {
        printf("[ERROR] Die Original-Datei %s und die dekomprimierte Datei %s\n"
               "        haben eine unterschiedliche Groesse.\n",
               in_filename, hd_filename);
        ok = false;
    }
    
    return ok;
}

                    
/* ---------------------------------------------------------------------------
 * Funktion: ppr_tb_compare_files
 * ------------------------------------------------------------------------- */
bool ppr_tb_compare_files(char *in_filename, char *hd_filename)
{      
    bool ok;
    
    FILE *in_stream = fopen(in_filename, "rb");
    if (in_stream == NULL)
    {
        printf("[ERROR] Die Datei %s konnte nicht geoeffnet werden.\n",
               in_filename);
        exit(EXIT_FAILURE);
    }

    FILE *hd_stream = fopen(hd_filename, "rb");
    if (hd_stream == NULL)
    {
        printf("[ERROR] Die Datei %s konnte nicht geoeffnet werden.\n",
               hd_filename);
        exit(EXIT_FAILURE);
    }

    int char1 = fgetc(in_stream);
    int char2 = fgetc(hd_stream);
    int pos = 1; /* Die Position des aktuellen Zeichens */

    while (char1 != EOF && char2 != EOF && char1 == char2)
    {
        char1 = fgetc(in_stream);
        char2 = fgetc(hd_stream);
        pos++;
    }

    if (char1 == EOF && char2 == EOF)
    {
        ok = true;
        printf("[OK] Die Dateien %s und %s sind identisch.\n", 
                in_filename, hd_filename);
    }
    else
    {
        ok = false;
        printf("[ERROR] Die Dateien %s und %s sind NICHT identisch.\n"
               "        Sie unterscheiden sich ab Position %d: "
               "'%2x' - '%2x'\n",
               in_filename, hd_filename, pos, (unsigned int) char1, (unsigned int) char2);
    }

    fclose(in_stream);
    fclose(hd_stream);
    
    return ok;
}
