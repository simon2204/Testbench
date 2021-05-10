/**
 * @file
 * Dieses Modul enthaelt Testfaelle, mit denen die Berechnung von 
 * Determinanten quadratischer Matrizen ueberprueft wird.
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
#include <math.h>
#include <string.h>

#include "ppr_tb_logging_json.h"


/* ===========================================================================
 * Prototypen der Aufgabenstellung
 * ======================================================================== */

#define MAX_SIZE 10

double get_determinant(double matrix[MAX_SIZE][MAX_SIZE], int size);



/* ===========================================================================
 * Prototypen der Test-Funktionen
 * ======================================================================== */

/**
 * Vergleicht das gelieferte Ergebnis mit dem erwarteten Ergebnis 
 * (Ist-Soll-Vergleich) und gibt abhaengig davon, ob der Vergleich eine 
 * Abweichung ergeben hat oder nicht, eine entsprechende Meldung aus.
 *
 * @param testcase       Name des Testfalls
 * @param expected       das erwartete Ergebnis (Sollwert)
 * @param result         das gelieferte Ergebnis (Istwert)
 *
 * @return               true, falls das gelieferte Ergebnis
 *                       (Istwert) mit dem erwarteten Ergebnis (Sollwert)
 *                       uebereinstimmt. false, sonst
 */
static void ppr_tb_assert_equal(char *testcase,
                                double matrix[MAX_SIZE][MAX_SIZE], int size,
                                double expected, double result,
                                int id, int groupId,
                                int total);
void ppr_tb_print_ok(void);
/**
 * Gibt eine Matrix auf dem Bildschirm aus. Ist die Groesse der Matrix nicht im
 * Intervall [1..MAX_SIZE] wird die Ausgabe mit einer Fehlermeldung abgebrochen.
 * 
 * @param matrix    Die Matrix, die auf dem Bildschirm ausgegeben werden soll.
 *                  Diese muss ein 2-dimensionales Array der Groesse 
 *                  [MAX_SIZE][MAX_SIZE] sein.
 * @param size      tatsaechliche Groesse der Matrix
 */
void ppr_tb_print_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size, char output[1000]);


/* ===========================================================================
 * Definitionen der Test-Funktionen
 * ======================================================================== */

void ppr_tb_test_get_determinant(void)
{
    
    double expected;
    double result;
    int size;
   
    char *test_case1 = "Testfall 1: "
                       "Gültige Werte: 1x1-Matrix";
    {
        /* Testfall 1: Gueltige Werte: 1x1-Matrix */
        double matrix[MAX_SIZE][MAX_SIZE] = {{1}};
        size = 1;
        expected = 1.0;
        result = get_determinant(matrix, size);
        ppr_tb_assert_equal(test_case1, matrix, size, expected, result, 1, 1, 10);
    }
    
    char *test_case2 = "Testfall 2: "
                       "Gültige Werte: 2x2-Matrix";
    {
        /* Testfall 2: Gueltige Werte: 2x2-Matrix */
        double matrix[MAX_SIZE][MAX_SIZE] = {
            {1, 2},
            {3, 4}
        };
        size = 2;
        expected = -2.0;
        result = get_determinant(matrix, size);
        ppr_tb_assert_equal(test_case2, matrix, size, expected, result, 2, 1, 10);
    }
    
    char *test_case3 = "Testfall 3: "
                       "Gültige Werte: 2x2-Matrix";
    {
        /* Testfall 3: Gueltige Werte: 2x2-Matrix */
        double matrix[MAX_SIZE][MAX_SIZE] ={
            {-1, -2},
            {-3, -4}
        };
        size = 2;
        expected = -2.0;
        result = get_determinant(matrix, size);
        ppr_tb_assert_equal(test_case3, matrix, size, expected, result, 3, 1, 10);
    }
    
    char *test_case4 = "Testfall 4: "
                       "Gültige Werte: 3x3-Matrix";
    {
        /* Testfall 4: Gueltige Werte: 3x3-Matrix */
        double matrix[MAX_SIZE][MAX_SIZE] ={
            {0, 1, 2},
            {3, 2, 1},
            {1, 1, 0}
        };
        size = 3;
        expected = 3.0;
        result = get_determinant(matrix, size);
        ppr_tb_assert_equal(test_case4, matrix, size, expected, result, 4, 1, 10);
    }
    
    char *test_case5 = "Testfall 5: "
                       "Gültige Werte: 3x3-Matrix";
    {
        /* Testfall 5: Gueltige Werte: 3x3-Matrix */
        double matrix[MAX_SIZE][MAX_SIZE] ={
            {-1.1, -2.2, -3.4},
            {-3.2, -2.7, -1.3},
            {-1.2, -1.6, -0.7}
        };
        size = 3;
        expected = -4.68;
        result = get_determinant(matrix, size);
        ppr_tb_assert_equal(test_case5, matrix, size, expected, result, 5, 1, 10);
    }
    
    char *test_case6 = "Testfall 6: "
                       "Gültige Werte: 3x3-Matrix";
    {
        /* Testfall 6: Gueltige Werte: 3x3-Matrix */
        double matrix[MAX_SIZE][MAX_SIZE] ={
            {1,  2, 3},
            {4, -5, 6},
            {7,  8, 9}
        };
        size = 3;        
        expected = 120.00;
        result = get_determinant(matrix, size);
        ppr_tb_assert_equal(test_case6, matrix, size, expected, result, 6, 1, 10);
    }

    char *test_case7 = "Testfall 7: "
                       "Gültige Werte: 4x4-Matrix";
    {
        /* Testfall 7: Gueltige Werte: 4x4-Matrix */
        double matrix[MAX_SIZE][MAX_SIZE] = {
            {1, -1,  2  , -3},
            {4,  0,  3.5,  1},
            {2, -5,  1  ,  0},
            {3, -1, -1  ,  2}
        };
        size = 4;        
        expected = 184.50;
        result = get_determinant(matrix, size);
        ppr_tb_assert_equal(test_case7, matrix, size, expected, result, 7, 1, 10);
    }
    
    char *test_case8 = "Testfall 8: "
                       "Gültige Werte: 10x10-Matrix";
    {
        /* Testfall 8: Gueltige Werte: 10x10-Matrix */
        double matrix[MAX_SIZE][MAX_SIZE];
        int row;
        int column;
        size = MAX_SIZE;
        expected = -4411917.34;
        for (row = 0; row < MAX_SIZE; row++)
        {
            for (column = 0; column < MAX_SIZE; column++)
            {
                if (row == column)
                {
                    matrix[row][column] = 0;
                }
                else
                {
                    matrix[row][column] =
                            (row + 1) * (((row + column) % 2 != 0) ? -1 : 1) 
                            + ((double) column + 1) / 10;
                }
            }
        }
        result = get_determinant(matrix, size);
        ppr_tb_assert_equal(test_case8, matrix, size, expected, result, 8, 1, 10);
    }
    
        char *test_case9 = "Testfall 9: "
                           "Ungültiger Wert für Parameter size: 0"
                           "\n(--> Determinante kann nicht berechnet werden.)";
    {
        /* Testfall 9: Ungueltiger Wert fuer Parameter size: 0 
         *             --> Determinante kann nicht berechnet werden. */
        double matrix[MAX_SIZE][MAX_SIZE];
        size = 0;
        expected = 0.00;
        result = get_determinant(matrix, size);
        ppr_tb_assert_equal(test_case9, matrix, size, expected, result, 9, 1, 10);
    }

    char *test_case10 = "Testfall 10: "
                        "Ungültiger Wert für Parameter size: MAX_SIZE + 1 "
                        "\n(--> Determinante kann nicht berechnet werden.)";
    {
        /* Testfall 10: Ungueltiger Wert fuer Parameter size: MAX_SIZE + 1 
         *              --> Determinante kann nicht berechnet werden. */
        double matrix[MAX_SIZE][MAX_SIZE];
        size = MAX_SIZE + 1;
        expected = 0.00;
        result = get_determinant(matrix, size);
        ppr_tb_assert_equal(test_case10, matrix, size, expected, result, 10, 1, 10);
    }
}


/* ----------------------------------------------------------------------------
 * Funktion: ppr_tb_assert_equal
 * ------------------------------------------------------------------------- */
static void ppr_tb_assert_equal(char *testcase, 
                                double matrix[MAX_SIZE][MAX_SIZE], int size,
                                double expected, double result,
                                int id, int groupId,
                                int total)
{
    char expected_str[100] = {0};
    char actual_str[100] = {0};
    char functionHead[100] = {0};
    char error_buf[1000] = {0};
    
    sprintf(expected_str, "%f", expected);
    sprintf(actual_str, "%f", result);
    sprintf(functionHead, "get_determinant(matrix, %d)", size);
    
    if (fabs(result - expected) < 0.01)
    {
        
    }
    else
    {
        sprintf(error_buf, "[ERROR]\n"
                "   Aufruf von get_determinant(matrix, %d)\n"
                "   expected:<[\n"
                "   %8.2f\n"
                "   ]> but was:<[\n"
                "   %8.2f\n"
                "   ]>\n", size, expected, result);
       
        unsigned long error_buf_size = strlen(error_buf);
        
        char *error_buf_last_pos = error_buf + error_buf_size;
        
        ppr_tb_print_matrix(matrix, size, error_buf_last_pos);
    }
    
    ppr_tb_log_testcase(id, groupId, testcase, expected_str, actual_str, error_buf, total);
}

/* --------------------------------------------------------------------------
 * Funktion: tb_print_matrix
 * ----------------------------------------------------------------------- */
void ppr_tb_print_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size, char output[1000])
{
    short int row;
    short int column;

    if (size < 1 || size > MAX_SIZE)
    {
        return;
    }
    for (row = 0; row < size; row++)
    {
        /* Kopf- oder Trennzeile */
        for (column = 0; column < size; column++)
        {
            printf("+------");
        }
        printf("+\n");
        
        for (column = 0; column < size; column++)
        {
            printf("| %4.1f ", matrix[row][column]);
        }
        printf("|\n");
    }
    /* letzte Zeile */
    for (column = 0; column < size; column++)
    {
        printf("+------");
    }
    printf("+\n");
}

/* ----------------------------------------------------------------------------
 * Funktion: main
 * ------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
    ppr_tb_test_get_determinant();
    
    return (EXIT_SUCCESS);
}



