/**
 * @mainpage 
 * 
 * <h1>Projekt MATRIX</h1>
 * 
 * Dieses Projekt dient zur Berechnung von Determinanten quadratischer
 * Matrizen, die Gleitpunktzahlen enthalten.
 *
 * @author  Ulrike Griefahn
 * @date    2014-10-09
 */

/* ==========================================================================*/

/**
 * @file
 * Dieses Modul dient zur Berechnung von Determinanten quadratischer
 * Matrizen, die Gleitpunktzahlen enthalten.
 *
 * @author  Ulrike Griefahn
 * @date    2014-10-09
 */


/* ============================================================================
 * Header-Dateien 
 * ========================================================================= */

#include <stdio.h>


/* ============================================================================
 * Symbolische Konstanten
 * ========================================================================= */

/**
 * Die maximale Zeilen- und Spaltenanzahl einer quadratischen Matrix
 */
#define MAX_SIZE 10


/* ============================================================================
 * Funktionsprototypen
 * ========================================================================= */

/**
 * Berechnet die Determinante einer quadratischen Matrix nach dem Laplaceschen
 * Entwicklungssatz.
 *
 * Es wird davon ausgegangen, dass die aktuelle Größe der Matrix (Parameter 
 * size) mindestens 1 und maximal MAX_SIZE ist, andernfalls wird 
 * 0.0 als Wert geliefert.
 *
 * @param matrix    Matrix, deren Determinante berechnet werden soll.
 * @param size      aktuelle Größe (Zeilen und Spalten) der quadratischen
 *                  Matrix. Die Werte liegen im oberen linken Ausschnitt des 
 *                  2-dimens. Vektors matrix.
 * @return          Die Determinante der Matrix
 */
double get_determinant(double matrix[][MAX_SIZE], int size);

/**
 * Schreibt die Untermatrix der Matrix source in die Matrix target. Die 
 * Untermatrix entsteht dadurch, dass aus der Matrix source eine Zeile und 
 * eine Spalte entfernt werden.
 * 
 * Es wird davon ausgegangen, dass die Parameter folgende Bedingungen erfüllen:
 *  - 1 <= size <= MAX_SIZE 
 *  - 1 <= remove_row
 *  - remove_col <= size 
 * Andernfalls ist das Verhalten der Funktion undefiniert.
 * 
 * @param source        Die Matrix, deren Untermatrix bestimmt werden soll.
 * @param target        Die Matrix, in die die Untermatrix geschrieben werden 
 *                      soll.
 * @param remove_row    Die Zeile, die entfernt werden soll, um die Untermatrix
 *                      zu erzeugen.
 * @param remove_column Die Spalte, die entfernt werden soll, um die
 *                      Untermatrix zu erzeugen.
 * @param size          Die aktuelle Größe der Eingangsmatrix
 */
void get_sub_matrix(double source[][MAX_SIZE], double target[][MAX_SIZE],
                    int remove_row, int remove_column, int size);

/**
 * Gibt eine Matrix auf dem Bildschirm aus. Ist die Größe der Matrix nicht im
 * Intervall [1..MAX_SIZE] wird die Ausgabe mit einer Fehlermeldung abgebrochen.
 * 
 * @param matrix    Die Matrix, die auf dem Bildschirm ausgegeben werden soll.
 *                  Diese muss ein 2-dimensionales Array der Größe 
 *                  [MAX_SIZE][MAX_SIZE] sein. Die Werte liegen im oberen 
 *                  linken Ausschnitt des 2-dimens. Vektors matrix.
 * @param size      tatsächliche Größe der Matrix
 */
void print_matrix(double matrix[][MAX_SIZE], int size);


/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: get_determinant
 * ------------------------------------------------------------------------ */
double get_determinant(double matrix[][MAX_SIZE], int size)
{   
    /* die zu berechnende Determinante */
    double det;
    /* Vektor für die Untermatrizen */
    double sub_matrix[MAX_SIZE][MAX_SIZE];
    /* die Spalte, die aus der Matrix entfernt wird. */
    short int column;

    if (size < 1 || size > MAX_SIZE)
    {
        /* Für eine leere oder zu große Matrix kann keine Determinante berechnet
         * werden. Es wird 0.0 geliefert. */
        printf("FEHLER: Die Determinante kann nicht berechnet werden.\n");
        det = 0.0;
    }
    else if (size == 1)
    {
        /* 1x1 Matrix */
        det = matrix[0][0];
    }
    else if (size == 2)
    {
        /* 2*2-Matrix */
        det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    else
    {
        /* Mit dem Entwicklungssatz wird die Determinante der Matrix nach
         * der ersten Zeile (0) entwickelt. */
        det = 0.0;
        for (column = 0; column < size; column++)
        {
            get_sub_matrix(matrix, sub_matrix, 0, column, size);
            det += matrix[0][column]
                    * ((column % 2 == 0) ? 1 : -1)
                    * get_determinant(sub_matrix, size - 1);
        }
    }
    return det;
}

/* --------------------------------------------------------------------------
 * Funktion: get_sub_matrix
 * ----------------------------------------------------------------------- */
void get_sub_matrix(double source[][MAX_SIZE], double target[][MAX_SIZE],
                    int remove_row, int remove_column, int size)
{

    /* aktuelle Zeile in der source-Matrix. */
    short int source_row = 0;
    /* aktuelle Spalte in der source-Matrix. */
    short int source_column = 0;
    /* aktuelle Zeile in der target-Matrix. */
    short int target_row = 0;
    /* aktuelle Spalte in der target-Matrix. */
    short int target_column = 0;

    /* Iteration über alle Zeilen und Spalten und Kopieren von Zellen von der
     * Quellmatrix in die Zielmatrix. Bis auf die Zellen in Zeile remove_row
     * und in Spalte remove_column werden alle Zellen in die Zielmatrix 
     * target übernommen. */
    for (source_row = 0; source_row < size; source_row++)
    {
        if (source_row != remove_row)
        {
            target_column = 0;
            for (source_column = 0; source_column < size; source_column++)
            {
                if (source_column != remove_column)
                {
                    /* Zelle üernehmen */
                    target[target_row][target_column] =
                            source[source_row][source_column];
                    target_column++;
                }
            }
            target_row++;
        }
    }
}

/* --------------------------------------------------------------------------
 * Funktion: print_matrix
 * ----------------------------------------------------------------------- */
void print_matrix(double matrix[][MAX_SIZE], int size)
{
    short int row;
    short int column;

    if (size < 1 || size > MAX_SIZE)
    {
        printf("FEHLER: Die Matrix kann nicht ausgegeben werden.\n");
        return;
    }
    for (row = 0; row < size; row++)
    {
        /* Kopf- oder Trennzeile */
        for (column = 0; column < size; column++)
        {
            printf("+-------");
        }
        printf("+\n");
        
        for (column = 0; column < size; column++)
        {
            printf("| %5.1f ", matrix[row][column]);
        }
        printf("|\n");
    }
    /* letzte Zeile */
    for (column = 0; column < size; column++)
    {
        printf("+-------");
    }
    printf("+\n");
}

/* ========================================================================= */
/* Testet die Matrix-Funktionen mit dem Beispiel vom Übungszettel            */
/* ========================================================================= */

#include <assert.h>
#include <float.h>

/**
 * Testet die Determinantenberechnung
 * 
 * @return immer 0
 */
int main(void)
{
    double det;
    
    double matrix[][MAX_SIZE] 
        = {{0.0, 1.0, 2.0}, {3.0, 2.0, 1.0}, {1.0, 1.0, 0.0}};
    
    det = get_determinant(matrix, 3);
    assert(3.0 - DBL_EPSILON <= det && det <= 3.0 + DBL_EPSILON);
    
    return (0);
}