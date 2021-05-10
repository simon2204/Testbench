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
#include <sys/stat.h>


#include "ppr_tb_logging_json.h"


/* ============================================================================
 * Funktionsprotoytpen
 * ========================================================================= */

bool ppr_tb_compare_filesizes(
        char *in_filename, char *hc_filename, char *hd_filename, char *error_buf);
bool ppr_tb_compare_files(char *in_filename, char *hd_filename, char *error_buf);


/* ============================================================================
 * Funktionsdefinitionen
 * ========================================================================= */


/* ---------------------------------------------------------------------------
 * Funktion: main
 * ------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
    char *in_filename = argv[1];
    char *hc_filename = argv[2];
    char *hd_filename = argv[3];
    
    int id = atoi(argv[4]);
    int groupId = atoi(argv[5]);
    int total = atoi(argv[6]);
    
    char *info = NULL;
    
    if (argc > 7)
    {
        info = argv[7];
    }
    
    char error_buf[LOGGING_SIZE] = {0};

    if (ppr_tb_compare_filesizes(in_filename, hc_filename, hd_filename, error_buf))
    {
        ppr_tb_compare_files(in_filename, hd_filename, error_buf);
    }
    
    ppr_tb_log_testcase(id, groupId, info, NULL, NULL, error_buf, total);
    
    return(EXIT_SUCCESS);
}


/* ---------------------------------------------------------------------------
 * Funktion: ppr_tb_compare_filesizes
 * ------------------------------------------------------------------------- */
bool ppr_tb_compare_filesizes(
        char *in_filename, char *hc_filename, char *hd_filename, char *error_buf)
{
    struct stat attribut; /* Struktur für Datei-Eigenschaften */
    long long size_infile; /* Größe der übergebenen Dateien */
    long long size_hcfile;
    long long size_hdfile;
    bool ok = true;
    
    printf("Grösse der Dateien\n");

    if (stat(in_filename, &attribut) == -1)
    {
        size_infile = -1;
        sprintf(error_buf + strlen(error_buf),
                "* %s: existiert nicht",
                in_filename);
        ok = false;
    }
    else
    {
        size_infile = attribut.st_size;
        printf(" * %-25s: %8lld\n", in_filename, size_infile);
    }

    if (stat(hc_filename, &attribut) == -1)
    {
        size_hcfile = -1;
        sprintf(error_buf + strlen(error_buf),
                "* %s: existiert nicht",
                hc_filename);
        ok = false;
    }
    else
    {
        size_hcfile = attribut.st_size;
        printf(" * %-25s: %8lld\n", hc_filename, size_hcfile);
    }

    if (stat(hd_filename, &attribut) == -1)
    {
        size_hdfile = -1;
        sprintf(error_buf + strlen(error_buf),
                "* %s: existiert nicht",
                hd_filename);
        ok = false;
    }
    else
    {
        size_hdfile = attribut.st_size;
        printf(" * %-25s: %8lld\n", hd_filename, size_hdfile);
    }

    if (size_infile != -1 && size_hcfile != -1
            && size_infile > 2000 && size_infile < size_hcfile)
    {
        sprintf(error_buf + strlen(error_buf),
                "Die komprimierte Datei %s ist größer als die "
                "Originaldatei %s.",
                hc_filename, in_filename);
        ok = false;
    }

    if (size_infile != -1 && size_hdfile != -1
            && size_infile != size_hdfile)
    {
        sprintf(error_buf + strlen(error_buf),
                "Die Original-Datei %s und die dekomprimierte Datei %s\n"
                "haben eine unterschiedliche Größe.",
                in_filename, hd_filename);
        ok = false;
    }
    
    return ok;
}

                    
/* ---------------------------------------------------------------------------
 * Funktion: ppr_tb_compare_files
 * ------------------------------------------------------------------------- */
bool ppr_tb_compare_files(char *in_filename, char *hd_filename, char *error_buf)
{
    bool ok;
    
    FILE *in_stream = fopen(in_filename, "rb");
    if (in_stream == NULL)
    {
        sprintf(error_buf,
                "Die Datei %s konnte nicht geöffnet werden.",
                in_filename);
        
        exit(EXIT_FAILURE);
    }

    FILE *hd_stream = fopen(hd_filename, "rb");
    if (hd_stream == NULL)
    {
        sprintf(error_buf,
                "Die Datei %s konnte nicht geöffnet werden.",
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
      
        sprintf(error_buf,
                "Die Dateien %s und %s sind NICHT identisch.\n"
                "        Sie unterscheiden sich ab Position %d: "
                "'%2x' - '%2x'",
                in_filename, hd_filename, pos, (unsigned int) char1, (unsigned int) char2);
    }

    fclose(in_stream);
    fclose(hd_stream);
    
    return ok;
}
