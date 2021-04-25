/**
 * @mainpage Huffman-Kodierung
 * 
 * Dieses Projekt realisiert die Huffman-Kodierung. Es können beliebige Dateien
 * komprimiert und wieder dekompriniert werden.
 */

/**
 * @file
 * Hauptmodul der Huffman-Komprimierung
 * 
 * @author Ulrike Griefahn, Alexander Schmitz
 * @date 2019-11-07
 */

/* ===========================================================================
 * Includes 
 * ======================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman_common.h"
#include "huffman.h"

/* ===========================================================================
 * Symbolische Konstanten
 * ======================================================================== */

#define BUFSIZE 4096

/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/**
 * Testet die Funktionen.
 * 
 * @return immer 0
 */
int main(void)
{
    bool err_found = false;
    int i;

    {
        char in[BUFSIZE] = {0};
        char out[BUFSIZE] = {0};
        char expectation[BUFSIZE] = {0};

        strncpy(in, "", BUFSIZE);
        strncpy(expectation, "", 1);

        test_rd_chars_wr_bits(in, out);

        for (i = 0; i < strlen(expectation) && !err_found; i++)
        {
            if (expectation[i] != out[i])
            {
                err_found = true;
                printf("[ERROR]: Test 1 - Zeichen an Position %d ist nicht "
                       "korrekt: (erwartet: %u, erhalten: %u)\n",
                       i, (unsigned int) expectation[i], (unsigned int) out[i]);
            }
        }
    }

    {
        char in[BUFSIZE] = {0};
        char out[BUFSIZE] = {0};
        char expectation[BUFSIZE] = {0};

        strncpy(in,
                "aAbBcCdDeEfFgGhH"
                "iIjJkKlLmMnNoOpP"
                "qQrRsStTuUvVwWxX", BUFSIZE);
        strncpy(expectation, "UUUUUU", BUFSIZE);

        test_rd_chars_wr_bits(in, out);

        for (i = 0; i < strlen(expectation) && !err_found; i++)
        {
            if (expectation[i] != out[i])
            {
                err_found = true;
                printf("[ERROR]: Test 2 - Zeichen an Position %d ist nicht "
                       "korrekt: (erwartet: %d, erhalten: %d)\n",
                       i, (int) expectation[i], (int) out[i]);
            }
        }
    }

    {
        char in[BUFSIZE] = {0};
        char out[BUFSIZE] = {0};
        char expectation[BUFSIZE] = {0};

        strncpy(in, "", BUFSIZE);
        strncpy(expectation, "", BUFSIZE);

        test_rd_bits_wr_chars(in, out);

        for (i = 0; i < strlen(expectation) + 1 && !err_found; i++)
        {
            if (expectation[i] != out[i])
            {
                err_found = true;
                printf("[ERROR]: Test 3 - Zeichen an Position %d ist nicht "
                       "korrekt: (erwartet: %d, erhalten: %d)\n",
                       i, (int) expectation[i], (int) out[i]);
            }
        }
    }

    {
        char in[BUFSIZE] = {0};
        char out[BUFSIZE] = {0};
        char expectation[BUFSIZE] = {0};

        strncpy(in, "1234567890", BUFSIZE);
        strncpy(expectation,
                "00110001"
                "00110010"
                "00110011"
                "00110100"
                "00110101"
                "00110110"
                "00110111"
                "00111000"
                "00111001"
                "00110000", BUFSIZE);

        test_rd_bits_wr_chars(in, out);

        for (i = 0; i < strlen(expectation) && !err_found; i++)
        {
            if (expectation[i] != out[i])
            {
                err_found = true;
                printf("[ERROR]: Test 4 - Zeichen an Position %d ist nicht "
                       "korrekt: (erwartet: %d, erhalten: %d)\n",
                       i, (int) expectation[i], (int) out[i]);
            }
        }
    }

    return (EXIT_SUCCESS);
}
