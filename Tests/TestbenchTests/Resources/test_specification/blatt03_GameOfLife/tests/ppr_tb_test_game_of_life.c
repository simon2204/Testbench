/**
 * @file
 * Dieses Modul enthaelt Testfaelle, mit denen die Berechnung mit der
 * Ulam-Funktion ueberprueft wird.
 *
 * @author  Ulrike Griefahn
 * @date    2014-01-31
 */


/* ============================================================================
 * Header-Dateien
 * ========================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ppr_tb_logging_json.h"


/* ===========================================================================
 * Vorgaben der Aufgabenstellung
 * ======================================================================== */

#define ALL_ROWS 10
#define ALL_COLUMNS 10

void get_generation_as_string(char string[]);
void set_generation_from_string(char string[]);
bool set_next_generation(void);


/* ============================================================================
 * Globale Variablen (Tests)
 * ========================================================================= */

/**
 * Anfangsgeneration
 */
static char source_gen[ALL_ROWS * ALL_COLUMNS + 1];

/**
 * Zielgeneration
 */
static char expected_gen[ALL_ROWS * ALL_COLUMNS + 1];

/**
 * Ergebnisgeneration
 */
static char result_gen[ALL_ROWS * ALL_COLUMNS + 1];


/* ===========================================================================
 * Prototypen der Test-Funktionen
 * ======================================================================== */

/**
 * Vergleicht die erwartete Generation mit der berechneten und gibt, wenn
 * ungleich, die Ausgangsgeneration, die erwartete und die berechnete
 * Generation am Bildschirm aus. Die Funktion vergliecht zusätzlich auch den
 * erwarteten und berechneten Wert für Generation verändert und gibt, falls
 * ungleich die beiden Werte am Bildschirm aus.
 *
 * @param msg                   Testcase
 * @param source_gen            Ausgangsgeneration
 * @param expected_gen          erwartete Generation
 * @param result_gen            berechnete Generation
 * @param expected_changed      erwarteter Wert für Generation verändert
 * @param result_changed        berechneter Wert für Generation verändert
 */
static void ppr_tb_assert_equal(char *info,
                                char* source_gen, char* expected_gen, char *result_gen,
                                bool expected_changed, bool result_changed,
                                int id, int groupId, int total);

/**
 * Gibt auf dem Bildschirm aus, dass ausgehend von der Generation source
 * die Generation target erwartet und die Generation result berechnet wurde.
 *
 * @param source    die Ausgangsgeneration
 * @param result    die erwartete Generation
 * @param target    die berechnete Generation
 */
static void ppr_tb_print_generation_error(char *source, char *target, char *result, char output[10000]);

/**
 * Gibt auf dem Bildschirm aus, dass der Wert target erwartet und der Wert
 * result berechnet wurde.
 *
 * @param result    der erwartete Wert
 * @param target    der berechnete Wert
 */
static void ppr_tb_print_changed_error(bool expected, bool result, char output[10000]);


/**
 * Prototypen der Testfälle
 */
void ppr_tb_test_01(void);
void ppr_tb_test_02(void);
void ppr_tb_test_03(void);
void ppr_tb_test_04(void);
void ppr_tb_test_05(void);
void ppr_tb_test_06(void);
void ppr_tb_test_07(void);
void ppr_tb_test_08(void);
void ppr_tb_test_09(void);
void ppr_tb_test_10(void);
void ppr_tb_test_11(void);


/* ************************************************************************** */
void ppr_tb_test_set_generation_from_string(void)
{
    char *test_case1 = "Testfall 1: "
    "Teste wiederholte Ausführung von set_generation_from_string\n"
    "    1. Setze Diagonale von links oben nach rechts unten\n"
    "       (Ergebnis wird als Ausgangsgeneration für 2. verwendet."
    "    2. Setze Diagonale von rechts oben nach links unten";

    strcpy(source_gen,      "1000000000"
                            "0100000000"
                            "0010000000"
                            "0001000000"
                            "0000100000"
                            "0000010000"
                            "0000001000"
                            "0000000100"
                            "0000000010"
                            "0000000001");

    strcpy(expected_gen,    "0000000001"
                            "0000000010"
                            "0000000100"
                            "0000001000"
                            "0000010000"
                            "0000100000"
                            "0001000000"
                            "0010000000"
                            "0100000000"
                            "1000000000");

    set_generation_from_string(source_gen);
    set_generation_from_string(expected_gen);
    get_generation_as_string(result_gen);

    ppr_tb_assert_equal(test_case1, source_gen, expected_gen, result_gen,
                        true, true, 1, 1, 11);
}


/* ************************************************************************** */
void ppr_tb_test_set_next_generation(void)
{
    ppr_tb_test_02();
    ppr_tb_test_03();
    ppr_tb_test_04();
    ppr_tb_test_05();
    ppr_tb_test_06();
    ppr_tb_test_07();
    ppr_tb_test_08();
    ppr_tb_test_09();
    ppr_tb_test_10();
    ppr_tb_test_11();
}

void ppr_tb_test_02(void)
{
    bool result_changed;

    char *test_case2 = "Testfall 2: "
    "Teste 1 Lebewesen (Mitte, Rand, Ecken) - 0 Nachbar(n)";

    strcpy(source_gen,      "1000100001"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "1000100001"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "1000010001");

    strcpy(expected_gen,    "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000");

    set_generation_from_string(source_gen);
    get_generation_as_string(source_gen);
    result_changed = set_next_generation();
    get_generation_as_string(result_gen);

    ppr_tb_assert_equal(test_case2, source_gen, expected_gen, result_gen,
                        true, result_changed, 2, 1, 11);
}

void ppr_tb_test_03(void)
{
    bool result_changed;

    char *test_case3 = "Testfall 3: "
    "Teste 1 Lebewesen (Mitte, Rand, Ecken) - 1 Nachbar(n)";

    strcpy(source_gen,      "1100110001"
                            "0000000001"
                            "0000000000"
                            "1000000000"
                            "1000100001"
                            "0000010001"
                            "0000000000"
                            "0000000000"
                            "0000100000"
                            "1100100011");

    strcpy(expected_gen,    "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000");

    set_generation_from_string(source_gen);
    get_generation_as_string(source_gen);
    result_changed = set_next_generation();
    get_generation_as_string(result_gen);

    ppr_tb_assert_equal(test_case3, source_gen, expected_gen, result_gen,
                        true, result_changed, 3, 1, 11);
}

void ppr_tb_test_04(void)
{
    bool result_changed;

    char *test_case4 = "Testfall 4: "
    "Teste 1 Lebewesen (Mitte, Rand, Ecken) - 2 Nachbar(n)";

    strcpy(source_gen,      "1100110011"
                            "0100100001"
                            "0000000000"
                            "1000010000"
                            "1000100011"
                            "1001000001"
                            "0000000000"
                            "0000000000"
                            "1100110011"
                            "1000100001");

    strcpy(expected_gen,    "1100110011"
                            "1100110011"
                            "0000000000"
                            "0000000000"
                            "1100100011"
                            "0000000011"
                            "0000000000"
                            "0000000000"
                            "1100110011"
                            "1100110011");

    set_generation_from_string(source_gen);
    get_generation_as_string(source_gen);
    result_changed = set_next_generation();
    get_generation_as_string(result_gen);

    ppr_tb_assert_equal(test_case4, source_gen, expected_gen, result_gen,
                        true, result_changed, 4, 1, 11);
}

void ppr_tb_test_05(void)
{
    bool result_changed;

    char *test_case5 = "Testfall 5: "
    "Teste 1 Lebewesen (Mitte, Rand, Ecken) - 3 Nachbar(n)";

    strcpy(source_gen,      "1101100011"
                            "1101100011"
                            "0000000000"
                            "1001100011"
                            "1100100011"
                            "1000010000"
                            "0000000000"
                            "0000000000"
                            "1101110011"
                            "1100100011");

    strcpy(expected_gen,    "1101100011"
                            "1101100011"
                            "1110000000"
                            "1101100011"
                            "1101110011"
                            "1100000000"
                            "0000000000"
                            "0000100000"
                            "1111110011"
                            "1111110011");

    set_generation_from_string(source_gen);
    get_generation_as_string(source_gen);
    result_changed = set_next_generation();
    get_generation_as_string(result_gen);

    ppr_tb_assert_equal(test_case5, source_gen, expected_gen, result_gen,
                        true, result_changed, 5, 1, 11);
}

void ppr_tb_test_06(void)
{
    bool result_changed;

    char *test_case6 = "Testfall 6: "
    "Teste 1 Lebewesen (Mitte, Rand) - 4 Nachbar(n)";

    strcpy(source_gen,      "0001100000"
                            "0001110000"
                            "0000000000"
                            "1100000011"
                            "1100110011"
                            "0101110001"
                            "0000000000"
                            "0000000000"
                            "0001110000"
                            "0001100000");

    strcpy(expected_gen,    "0001010000"
                            "0001010000"
                            "0000100000"
                            "1100000011"
                            "0001010000"
                            "1111010011"
                            "0000100000"
                            "0000100000"
                            "0001010000"
                            "0001010000");

    set_generation_from_string(source_gen);
    get_generation_as_string(source_gen);
    result_changed = set_next_generation();
    get_generation_as_string(result_gen);

    ppr_tb_assert_equal(test_case6, source_gen, expected_gen, result_gen,
                        true, result_changed, 6, 1, 11);
}

void ppr_tb_test_07(void)
{
    bool result_changed;

    char *test_case7 = "Testfall 7: "
    "Teste 1 Lebewesen (rechter Rand) - "
    "Leben am gegenüber liegendem Rand";

    strcpy(source_gen,      "0000000011"
                            "1000000000"
                            "0000000000"
                            "0000000000"
                            "0000000011"
                            "1000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000");

    strcpy(expected_gen,    "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000");

    set_generation_from_string(source_gen);
    get_generation_as_string(source_gen);
    result_changed = set_next_generation();
    get_generation_as_string(result_gen);

    ppr_tb_assert_equal(test_case7, source_gen, expected_gen, result_gen,
                        true, result_changed, 7, 1, 11);
}

void ppr_tb_test_08(void)
{
    bool result_changed;

    char *test_case8 = "Testfall 8: "
    "Teste 0 Lebewesen (Mitte, Rand, Ecke) - 2 Nachbar(n)";

    strcpy(source_gen,      "0100010010"
                            "1000100010"
                            "0000000000"
                            "0000100010"
                            "0100000000"
                            "1000010010"
                            "0000000000"
                            "0000000000"
                            "0101100011"
                            "0100000000");

    strcpy(expected_gen,    "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0010000000"
                            "0010000000");

    set_generation_from_string(source_gen);
    get_generation_as_string(source_gen);
    result_changed = set_next_generation();
    get_generation_as_string(result_gen);

    ppr_tb_assert_equal(test_case8, source_gen, expected_gen, result_gen,
                        true, result_changed, 8, 1, 11);
}

void ppr_tb_test_09(void)
{
    bool result_changed;

    char *test_case9 = "Testfall 9: "
    "Teste 0 Lebewesen (Mitte, Rand, Ecke) - 3 Nachbar(n)";

    strcpy(source_gen,      "0101010010"
                            "1100100011"
                            "0000000000"
                            "1000100010"
                            "0100010010"
                            "1000010010"
                            "0000000000"
                            "0000000000"
                            "1101110011"
                            "0100000010");

    strcpy(expected_gen,    "1110100011"
                            "1110100011"
                            "1100000011"
                            "0000000000"
                            "1100110111"
                            "0000000000"
                            "0000000000"
                            "0000100000"
                            "1110100011"
                            "1110100011");

    set_generation_from_string(source_gen);
    get_generation_as_string(source_gen);
    result_changed = set_next_generation();
    get_generation_as_string(result_gen);

    ppr_tb_assert_equal(test_case9, source_gen, expected_gen, result_gen,
                        true, result_changed, 9, 1, 11);
}

void ppr_tb_test_10(void)
{
    bool result_changed;

    char *test_case10 = "Testfall 10: "
    "Teste 0 Lebewesen (Mitte, Rand) - 4 Nachbar(n)";

    strcpy(source_gen,      "0001010000"
                            "0000110000"
                            "0000000000"
                            "1000100011"
                            "0100010010"
                            "1101010010"
                            "0000000000"
                            "0000000000"
                            "0001110000"
                            "0001000000");

    strcpy(expected_gen,    "0000010000"
                            "0000110000"
                            "0000110000"
                            "0000000011"
                            "0110010110"
                            "1110100000"
                            "0000000000"
                            "0000100000"
                            "0001100000"
                            "0001000000");

    set_generation_from_string(source_gen);
    get_generation_as_string(source_gen);
    result_changed = set_next_generation();
    get_generation_as_string(result_gen);

    ppr_tb_assert_equal(test_case10, source_gen, expected_gen, result_gen,
                        true, result_changed, 10, 1, 11);
}

void ppr_tb_test_11(void)
{
    bool result_changed;
    int i;

    char *test_case11 = "Testfall 11: "
    "Teste GLIDER mit 32 Generationen";

    strcpy(source_gen,      "0100000000"
                            "0010000000"
                            "1110000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000");

    strcpy(expected_gen,    "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000000"
                            "0000000011"
                            "0000000011");

    set_generation_from_string(source_gen);
    get_generation_as_string(source_gen);
    for (i = 1; i <= 32; i++)
    {
        result_changed = set_next_generation();
    }
    get_generation_as_string(result_gen);

    ppr_tb_assert_equal(test_case11, source_gen, expected_gen, result_gen,
                        false, result_changed, 11, 1, 11);
}

/* ----------------------------------------------------------------------------
 * Funktion: main
 * ------------------------------------------------------------------------- */


int main(int argc, char **argv)
{
    ppr_tb_test_set_generation_from_string();
    ppr_tb_test_set_next_generation();

    return (EXIT_SUCCESS);
}


/* ----------------------------------------------------------------------------
 * Funktion: ppr_tb_assert_equal
 * ------------------------------------------------------------------------- */
static void ppr_tb_assert_equal(char *info,
        char* source_gen, char* expected_gen, char *result_gen,
        bool expected_changed, bool result_changed,
        int id, int groupId, int total)
{
    char error_buf[1000] = {0};

//    bool ok = true;
//    if (strcmp(expected_gen, result_gen) != 0)
//    {
//        ppr_tb_print_generation_error(source_gen,
//                                      expected_gen,
//                                      result_gen,
//                                      error_buf);
//        ok = false;
//    }
//
//    if (expected_changed != result_changed)
//    {
//        ppr_tb_print_changed_error(expected_changed,
//                                   result_changed,
//                                   error_buf);
//        ok = false;
//    }

    ppr_tb_log_testcase(id, groupId, info, expected_gen, result_gen, error_buf, total);
}

/* ----------------------------------------------------------------------------
 * Funktion: tb_print_generation_error
 * ------------------------------------------------------------------------- */
static void ppr_tb_print_generation_error(char *source, char *target, char *result, char output[10000])
{
    int row, column;

    sprintf(output + strlen(output),
            "\n[ERROR]\n"
            "    Ausgangsgeneration:<["
            "    expected:<[  "
            "    but was:<[ \n");

    for (row = 0; row < ALL_ROWS; row++)
    {
        sprintf(output + strlen(output),
                "      ");
        for (column = 0; column < ALL_COLUMNS; column++)
        {
            sprintf(output + strlen(output),
                    "%c",
                    source[row * ALL_COLUMNS + column]);
        }
        sprintf(output + strlen(output),
                "               ");
        for (column = 0; column < ALL_COLUMNS; column++)
        {
            sprintf(output + strlen(output),
                    "%c",
                    target[row * ALL_COLUMNS + column]);
        }
        sprintf(output + strlen(output),
                "      ");
        for (column = 0; column < ALL_COLUMNS; column++)
        {
            sprintf(output + strlen(output),
                    "%c",
                    result[row * ALL_COLUMNS + column]);
        }
        sprintf(output + strlen(output),
                "\n");
    }

    sprintf(output + strlen(output),
            "    ]>                   "
            "    ]>           "
            "    ]> \n");
}

/* ----------------------------------------------------------------------------
 * Funktion: tb_print_changed_error
 * ------------------------------------------------------------------------- */
static void ppr_tb_print_changed_error(bool expected, bool result, char output[10000])
{
    sprintf(output + strlen(output),
            "[ERROR]\n    Aufruf von set_next_generation()\n"
            "    expected:<[\n        %s (Wert: %d)\n"
            "    ]> but was:<[\n        %s (Wert: %d)]>\n\n",
            (expected == true) ? "Generation verändert"
                               : "Generation NICHT verändert",
            expected,
            (result == true) ? "Generation verändert"
                             : (result == false)
                                ? "Generation NICHT verändert"
                                : "Rückgabewert nicht aus {0, 1}",
            result);
}
