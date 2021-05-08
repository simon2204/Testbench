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

#include "ppr_tb_logging_json.h"


/* ===========================================================================
 * Prototypen der Aufgabenstellung
 * ======================================================================== */

extern int ulam_max(int a_0);
extern int ulam_twins(int limit);
extern int ulam_multiples(int limit, int number);


/**
 * Vergleicht das gelieferte Ergebnis mit dem erwarteten Ergebnis 
 * (Ist-Soll-Vergleich) und gibt abhaengig davon, ob der Vergleich eine 
 * Abweichung ergeben hat oder nicht, eine entsprechende Meldung aus.
 *
 * @param testcase       Name des Testfalls
 * @param fct            Name der Funktion, die aufgerufen wurde.
 * @param a0_bzw_limit   abhaengig vom Namen der Funktion (1-ter Parameter)
 *                       handelt es sich um a0 oder limit
 * @param number         gibt die Anzahl der gesuchten Mehrlinge an, falls
 *                       der Wert kleiner -1 ist, andernfalls wird der Parameter
 *                       ignoriert
 * @param expected       das erwartete Ergebnis (Sollwert)
 * @param result         das gelieferte Ergebnis (Istwert)
 *
 * @return               true, falls das gelieferte Ergebnis
 *                       (Istwert) mit dem erwarteten Ergebnis (Sollwert)
 *                       uebereinstimmt. false, sonst
 */
static void ppr_tb_assert_equal(char *testcase, char *function,
                                int a0_bzw_limit, int number,
                                int expected, int result,
                                int id, int groupId,
                                int total);


/* ============================================================================
 * Funktionsdefinitionen
 * ========================================================================= */


/* ----------------------------------------------------------------------------
 * Funktion: ppr_tb_test_ulam_max
 * ------------------------------------------------------------------------- */
void ppr_tb_test_ulam_max(void)
{
    int a0;
    int expected;
    int result;

    char *fct = "ulam_max";
    
    printf("========================================================\n");
    printf("Ueberpruefe Testfaelle ( U L A M _ M A X ):\n");
    printf("========================================================\n");
    
    /* ulam_max(-1) = -1 */
    char *test_case1 = "Testfall 1 ulam_max: Ungueltiger Wert fuer Parameter a_0";
    a0 = -1;
    expected = -1;
    result = ulam_max(a0);
    ppr_tb_assert_equal(test_case1, fct, a0, -2, expected, result, 1, 1, 18);
    
    /* ulam_max(0) = -1 */
    char *test_case2 = "Testfall 2 ulam_max: Ungueltiger Wert fuer Parameter a_0";
    a0 = 0;
    expected = -1;
    result = ulam_max(a0);
    ppr_tb_assert_equal(test_case2, fct, a0, -2, expected, result, 2, 1, 18);
    
    /* ulam_max(1) = 1 */
    char *test_case3 = "Testfall 3 ulam_max: Gueltige Werte fuer Parameter a_0";
    a0 = 1;
    expected = 1;
    result = ulam_max(a0);
    ppr_tb_assert_equal(test_case3, fct, a0, -2, expected, result, 3, 1, 18);
    
    /* ulam_max(2) = 2 */
    char *test_case4 = "Testfall 4 ulam_max: Gueltige Werte fuer Parameter a_0";
    a0 = 2;
    expected = 2;
    result = ulam_max(a0);
    ppr_tb_assert_equal(test_case4, fct, a0, -2, expected, result, 4, 1, 18);
    
    /* ulam_max(3) = 16 */
    char *test_case5 = "Testfall 5 ulam_max: Gueltige Werte fuer Parameter a_0";
    a0 = 3;
    expected = 16;
    result = ulam_max(a0);
    ppr_tb_assert_equal(test_case5, fct, a0, -2, expected, result, 5, 1, 18);
    
    /* ulam_max(4) = 4 */
    char *test_case6 = "Testfall 6 ulam_max: Gueltige Werte fuer Parameter a_0";
    a0 = 4;
    expected = 4;
    result = ulam_max(a0);
    ppr_tb_assert_equal(test_case6, fct, a0, -2, expected, result, 6, 1, 18);
    
    /* ulam_max(5) = 16 */
    char *test_case7 = "Testfall 7 ulam_max: Gueltige Werte fuer Parameter a_0";
    a0 = 5;
    expected = 16;
    result = ulam_max(a0);
    ppr_tb_assert_equal(test_case7, fct, a0, -2, expected, result, 7, 1, 18);
}

/* ----------------------------------------------------------------------------
 * Funktion: ppr_tb_test_ulam_twins
 * ------------------------------------------------------------------------- */
void ppr_tb_test_ulam_twins(void)
{
    int limit;
    int expected;
    int result;
    
    char *fct = "ulam_twins";
    
    printf("========================================================\n");
    printf("Ueberpruefe Testfaelle ( U L A M _ T W I N S ):\n");
    printf("========================================================\n");
    
    /* ulam_twins(0) = -1 */
    char *test_case8 = "Testfall 8 ulam_twins: Ungueltiger Wert fuer Parameter limit";
    limit = 0;
    expected = -1;
    result = ulam_twins(limit);
    ppr_tb_assert_equal(test_case8, fct, limit, -2, expected, result, 8, 2, 18);
    
    /* ulam_twins(5) = -1 */
    char *test_case9 = "Testfall 9 ulam_twins: ULAM-Zwilling nicht vollstaendig im Intervall enthalten";
    limit = 5;
    expected = -1;
    result = ulam_twins(limit);
    ppr_tb_assert_equal(test_case9, fct, limit, -2, expected, result, 9, 2, 18);
    
    /* ulam_twins(6) = 5 */
    char *test_case10 = "Testfall 10 ulam_twins: Gueltige Werte fuer Parameter limit";
    limit = 6;
    expected = 5;
    result = ulam_twins(limit);
    ppr_tb_assert_equal(test_case10, fct, limit, -2, expected, result, 10, 2, 18);
}

/* ----------------------------------------------------------------------------
 * Funktion: ppr_tb_test_ulam_multiples
 * ------------------------------------------------------------------------- */
void ppr_tb_test_ulam_multiples(void)
{
    int limit;
    int number;
    int expected;
    int result;
    
    char *fct = "ulam_multiples";
    
    printf("========================================================\n");
    printf("Ueberpruefe Testfaelle ( U L A M _ M U L T I P L E S ):\n");
    printf("========================================================\n");
    
    /* ulam_multiples(0, 2) = -1 */
    char *test_case11 = "Testfall 11 ulam_multiples: Ungueltiger Wert fuer Parameter limit";
    limit = 0;
    number = 2;
    expected = -1;
    result = ulam_multiples(limit, number);
    ppr_tb_assert_equal(test_case11, fct, limit, number, expected, result, 11, 3, 18);
    
    /* ulam_multiples(10, 0) = -1 */
    char *test_case12 = "Testfall 12 ulam_multiples: Ungueltiger Wert fuer Parameter number";
    limit = 10;
    number = 0;
    expected = -1;
    result = ulam_multiples(limit, number);
    ppr_tb_assert_equal(test_case12, fct, limit, number, expected, result, 12, 3, 18);
    
    /* ulam_multiples(5, 2) = -1 */
    char *test_case13 = "Testfall 13 ulam_multiples: Mehrling fuer number=2 nicht vollstaendig im Intervall enthalten";
    limit = 5;
    number = 2;
    expected = -1;
    result = ulam_multiples(limit, number);
    ppr_tb_assert_equal(test_case13, fct, limit, number, expected, result, 13, 3, 18);
    
    /* ulam_multiples(109, 4) = -1 */
    char *test_case14 = "Testfall 14 ulam_multiples: Mehrling fuer number=4 nicht vollstaendig im Intervall enthalten";
    limit = 109;
    number = 4;
    expected = -1;
    result = ulam_multiples(limit, number);
    ppr_tb_assert_equal(test_case14, fct, limit, number, expected, result, 14, 3, 18);
    
    /* ulam_multiples(110, 4) = 107 */
    char *test_case15 = "Testfall 15 ulam_multiples: Gueltige Werte fuer Parameter limit und number";
    limit = 110;
    number = 4;
    expected = 107;
    result = ulam_multiples(limit, number);
    ppr_tb_assert_equal(test_case15, fct, limit, number, expected, result, 15, 3, 18);
    
    /* ulam_multiples(111, 4) = 108 */
    char *test_case16 = "Testfall 16 ulam_multiples: Gueltige Werte fuer Parameter limit und number";
    limit = 111;
    number = 4;
    expected = 108;
    result = ulam_multiples(limit, number);
    ppr_tb_assert_equal(test_case16, fct, limit, number, expected, result, 16, 3, 18);
    
    /* ulam_multiples(1000, 2) = 982 */
    char *test_case17 = "Testfall 17 ulam_multiples: Gueltige Werte fuer Parameter limit und number";
    limit = 1000;
    number = 2;
    expected = 982;
    result = ulam_multiples(limit, number);
    ppr_tb_assert_equal(test_case17, fct, limit, number, expected, result, 17, 3, 18);
    
    /* ulam_multiples(391, 2) = 386 */
    char *test_case18 = "Testfall 18 ulam_multiples: Gueltige Werte fuer Parameter limit und number";
    limit = 391;
    number = 6;
    expected = 386;
    result = ulam_multiples(limit, number);
    ppr_tb_assert_equal(test_case18, fct, limit, number, expected, result, 18, 3, 18);
}

/* ----------------------------------------------------------------------------
 * Funktion: ppr_tb_assert_equal
 * ------------------------------------------------------------------------- */
static void ppr_tb_assert_equal(char *testcase, char *function,
                                int a0_bzw_limit, int number, 
                                int expected, int result,
                                int id, int groupId,
                                int total)
{
    char expected_str[100] = {0};
    char actual_str[100] = {0};
    char functionHead[100] = {0};
    char error_buf[1000] = {0};
    
    sprintf(expected_str, "%d", expected);
    sprintf(actual_str, "%d", result);
    
    if (result != expected)
    {
        sprintf(error_buf, "[Error]");
    }
    
    if (number >= -1)
    {
        sprintf(functionHead, "%s(%d, %d)", function, a0_bzw_limit, number);
    }
    else
    {
        sprintf(functionHead, "%s(%d)\n", function, a0_bzw_limit);
    }
    
    ppr_tb_log_testcase(id, groupId, testcase, expected_str, actual_str, error_buf, total);
}

/* ----------------------------------------------------------------------------
 * Funktion: main
 * ------------------------------------------------------------------------- */


int main(int argc, char **argv)
{
    ppr_tb_test_ulam_max();
    ppr_tb_test_ulam_twins();
    ppr_tb_test_ulam_multiples();
    
    return (EXIT_SUCCESS);
}
