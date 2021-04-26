/**
 * @file
 * Dieses Modul enthaelt Testfaelle, mit denen das Kopieren von Vektoren mit
 * Bitoperationen ueberprueft wird.
 *
 * @author  Ulrike Griefahn, Alexander Schmitz
 * @date    2019-07-29
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


/* ===========================================================================
 * Vorgaben der Aufgabenstellung
 * ======================================================================== */

#define BUF_SIZE 4096

extern void test_rd_chars_wr_bits(char in[], int count, char out[]);
extern void test_rd_bits_wr_chars(char in[], int count, char out[]);

/* ============================================================================
 * Typdefinitionen (Tests)
 * ========================================================================= */

typedef enum
{
    READ_CHARS_WRITE_BITS,
    READ_BITS_WRITE_CHARS
} MODUS;

typedef void (*TEST_FCT)(char *, char *);


/* ===========================================================================
 * Prototypen der Test-Funktionen
 * ======================================================================== */

static void ppr_tb_test_empty_string(TEST_FCT test, int no, MODUS mod);
static void ppr_tb_test_pattern_string(TEST_FCT test, int no, MODUS mod);
static void ppr_tb_test_init_string(TEST_FCT test, int no, MODUS mod);

static void ppr_tb_assert_equal(char* msg, char* expectation, char* out);

/* ===========================================================================
 * Definition der Test-Funktionen
 * ======================================================================== */

static void ppr_tb_test_rd_chars_wr_bits()
{
    ppr_tb_test_empty_string((TEST_FCT) test_rd_chars_wr_bits, 1, READ_CHARS_WRITE_BITS);
    ppr_tb_test_pattern_string((TEST_FCT) test_rd_chars_wr_bits, 2, READ_CHARS_WRITE_BITS);
    ppr_tb_test_init_string((TEST_FCT) test_rd_chars_wr_bits, 3, READ_CHARS_WRITE_BITS);
}

static void ppr_tb_test_rd_bits_wr_chars()
{
    ppr_tb_test_empty_string((TEST_FCT) test_rd_bits_wr_chars, 5, READ_BITS_WRITE_CHARS);
    ppr_tb_test_pattern_string((TEST_FCT) test_rd_bits_wr_chars, 6, READ_BITS_WRITE_CHARS);
    ppr_tb_test_init_string((TEST_FCT) test_rd_bits_wr_chars, 7, READ_BITS_WRITE_CHARS);
}

static void ppr_tb_test_empty_string(TEST_FCT test, int no, MODUS mod)
{
    char *testcase = "empty_string (io_testsuite)";

    char in[BUF_SIZE] = {0};
    char out[BUF_SIZE] = {0};
    char expectation[BUF_SIZE] = {0};

    if (mod == READ_CHARS_WRITE_BITS)
    {
        printf("\n========================================================");
        printf("\nTestfall %d: Leeren String testen (read chars write bits)\n", no);

        char* content_str = "";
        char* expectation_str = "";
        strncpy(in, content_str, strlen(content_str));
        strncpy(expectation, expectation_str, strlen(expectation_str));
    }
    else
    {
        printf("\n========================================================");
        printf("\nTestfall %d: Leeren String testen (read bits write chars)\n", no);

        char* content_str = "";
        char* expectation_str = "";
        strncpy(in, content_str, strlen(content_str));
        strncpy(expectation, expectation_str, strlen(expectation_str));
    }

    test(in, out);

    ppr_tb_assert_equal(testcase, expectation, out);
}

static void ppr_tb_test_pattern_string(TEST_FCT test, int no, MODUS mod)
{
    char *testcase = "pattern_string (io_testsuite)";

    char in[BUF_SIZE] = {0};
    char out[BUF_SIZE] = {0};
    char expectation[BUF_SIZE] = {0};

    if (mod == READ_CHARS_WRITE_BITS)
    {
        printf("\n========================================================");
        printf("\nTestfall %d: String mit \"aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxX\" "
               "testen (read chars write bits)\n", no);

        char* content_str = "aAbBcCdDeEfFgGhH"
                            "iIjJkKlLmMnNoOpP"
                            "qQrRsStTuUvVwWxX";
        char* expectation_str = "UUUUUU";
        strncpy(in, content_str, strlen(content_str));
        strncpy(expectation, expectation_str, strlen(expectation_str));
    }
    else
    {
        printf("\n========================================================");
        printf("\nTestfall %d: String mit \"1234567890\" "
               "testen (read bits write chars)\n", no);

        char* content_str = "1234567890";
        char* expectation_str = "00110001"
                                "00110010"
                                "00110011"
                                "00110100"
                                "00110101"
                                "00110110"
                                "00110111"
                                "00111000"
                                "00111001"
                                "00110000";
        strncpy(in, content_str, strlen(content_str));
        strncpy(expectation, expectation_str, strlen(expectation_str));
    }

    test(in, out);

    ppr_tb_assert_equal(testcase, expectation, out);
}

static void ppr_tb_test_init_string(TEST_FCT test, int no, MODUS mod)
{
    char* testcase = "init_string (io_testsuite)";

    char in1[BUF_SIZE] = {0};
    char out1[BUF_SIZE] = {0};
    char expectation1[BUF_SIZE] = {0};

    char in2[BUF_SIZE] = {0};
    char out2[BUF_SIZE] = {0};
    char expectation2[BUF_SIZE] = {0};

    if (mod == READ_CHARS_WRITE_BITS)
    {
        printf("\n========================================================");
        printf("\nTestfall %d: Erst \"aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxX\", "
               "danach \"abCdefGHijKlmnOPqrStuvWXyzAbcdEF\" testen (read chars write bits)\n", no);

        char* content_str_1 = "aAbBcCdDeEfFgGhH"
                              "iIjJkKlLmMnNoOpP"
                              "qQrRsStTuUvVwWxX";
        char* expectation_str_1 = "UUUUUU";
        strncpy(in1, content_str_1, strlen(content_str_1));
        strncpy(expectation1, expectation_str_1, strlen(expectation_str_1));

        char* content_str_2 = "abCdefGH"
                              "ijKlmnOP"
                              "qrStuvWX"
                              "yzAbcdEF";
        char* expectation_str_2 = "####";
        strncpy(in2, content_str_2, strlen(content_str_2));
        strncpy(expectation2, expectation_str_2, strlen(expectation_str_2));
    }
    else
    {
        printf("\n========================================================");
        printf("\nTestfall %d: Erst \"1234567890\", "
               "danach \"0192837465\" testen (read bits write chars)\n", no);

        char* content_str_1 = "1234567890";
        char* expectation_str_1 = "00110001"
                                  "00110010"
                                  "00110011"
                                  "00110100"
                                  "00110101"
                                  "00110110"
                                  "00110111"
                                  "00111000"
                                  "00111001"
                                  "00110000";
        strncpy(in1, content_str_1, strlen(content_str_1));
        strncpy(expectation1, expectation_str_1, strlen(expectation_str_1));

        char* content_str_2 = "0192837465";
        char* expectation_str_2 = "00110000"
                                  "00110001"
                                  "00111001"
                                  "00110010"
                                  "00111000"
                                  "00110011"
                                  "00110111"
                                  "00110100"
                                  "00110110"
                                  "00110101";
        strncpy(in2, content_str_2, strlen(content_str_2));
        strncpy(expectation2, expectation_str_2, strlen(expectation_str_2));
    }

    test(in1, out1);
    test(in2, out2);

    ppr_tb_assert_equal(testcase, expectation2, out2);
}

/* ----------------------------------------------------------------------------
 * Funktion: ppr_tb_assert_equal
 * ------------------------------------------------------------------------- */
static void ppr_tb_assert_equal(char* msg, char* expectation, char* out)
{
    bool ok = true;
    int error_pos;
    int i;

    for (i = 0; i < BUF_SIZE && ok; i++)
    {
        if (expectation[i] != out[i])
        {
            ok = false;
            error_pos = i;
        }
    }
    if (!ok)
    {
#ifndef TESTBENCH
        printf("%%TEST_FAILED%% time=0 testname=%s "
               "message=expected result: %s, but was: %s\n",
               msg, expectation, out);
#endif
        printf("[ERROR]: Zeichen an Position %d ist nicht korrekt: (erwartet: %c, erhalten: %c)\n",
               error_pos, expectation[error_pos], out[error_pos]);
        printf("    expected:<[\n       '%s'\n"
               "    ]> but was:<[\n       '%s']>\n\n",
               expectation, out);

        fflush(stdout);
    }

    if (ok)
    {
        printf("[OK]\n\n");
        fflush(stdout);

#ifdef TESTBENCH
        ppr_tb_log_assert();
#endif
    }
}

/* ----------------------------------------------------------------------------
 * Funktion: main
 * ------------------------------------------------------------------------- */
#ifndef TESTBENCH

int main(void)
{
    printf("%%SUITE_STARTING%% io_testsuite\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test_rd_chars_wr_bits (io_testsuite)\n");
    ppr_tb_test_rd_chars_wr_bits();
    printf("%%TEST_FINISHED%% time=0 test_rd_chars_wr_bits (io_testsuite)\n");

    printf("%%TEST_STARTED%% test_rd_bits_wr_chars (io_testsuite)\n");
    ppr_tb_test_rd_bits_wr_chars();
    printf("%%TEST_FINISHED%% time=0 test_rd_bits_wr_chars (io_testsuite)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
#endif

#ifdef TESTBENCH

int main(int argc, char **argv)
{
    ppr_tb_write_total_assert(6);

    ppr_tb_test_rd_chars_wr_bits();
    ppr_tb_test_rd_bits_wr_chars();

    ppr_tb_write_summary("", argv[1]);

    return (EXIT_SUCCESS);
}
#endif
