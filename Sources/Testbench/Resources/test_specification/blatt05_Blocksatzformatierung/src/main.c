/**
 * @mainpage
 * 
 * <h2>Projekt Blocksatzformatierung</h2>
 * In diesem Projekt werden Textzeilen im Blocksatz formatiert.
 */

/**
 * @file
 * Mainfile für die Blocksatzformatierung
 * 
 * @author Ulrike Griefahn, Alexander Schmitz
 * @date 2019-08-07
 */

/* ===========================================================================
 * Includes 
 * ======================================================================== */

#include <stdio.h>
#include <stdlib.h>

#include "justify_line.h"



/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/**
 * Testet die Funktion justify_line.
 * 
 * @return immer EXIT_SUCCESS
 */
int main(void)
{
    {
        char input[] = "123456789 345678901 567890123 789012345 901234567 123456789 234567890";
        char result[MAX_LINE_LENGTH + 1] = {0};
        justify_line(input, MAX_LINE_LENGTH, result);
        printf("|%s|\n", input);
        printf("|%s|\n\n", result);
    }
    {
        char input[] = "123456789 12345678901  4567890123 56789012345  8901234567  0123456789  234567890123456";
        char result[MAX_LINE_LENGTH + 1] = "xxxxxxxxxxxxxxxxxxx";
        justify_line(input, 80, result);
        printf("|%s|\n", input);
        printf("|%s|\n\n", result);
    }
    {
        char input[] = " 1234567 3456789 4567890 56789012 78901234 901234567 234567890";
        char result[MAX_LINE_LENGTH + 1] = {0};
        justify_line(input, MAX_LINE_LENGTH, result);
        printf("|%s|\n", input);
        printf("|%s|\n\n", result);
    }
    {
        char input[] = "   1234567 3456789 4567890 56789012 78901234 901234567 234567890";
        char result[MAX_LINE_LENGTH + 1] = {0};
        justify_line(input, MAX_LINE_LENGTH, result);
        printf("|%s|\n", input);
        printf("|%s|\n\n", result);
    }
    {
        char input[] = "123456789 345678901 567890123 789012345 901234567 123456789 234567890 ";
        char result[MAX_LINE_LENGTH + 1] = {0};
        justify_line(input, MAX_LINE_LENGTH, result);
        printf("|%s|\n", input);
        printf("|%s|\n\n", result);
    }
    {
        char input[] = "123456789 345678901 567890123 789012345 901234567 123456789 234567890     ";
        char result[MAX_LINE_LENGTH + 1] = {0};
        justify_line(input, MAX_LINE_LENGTH, result);
        printf("|%s|\n", input);
        printf("|%s|\n\n", result);
    }
    {
        char input[] = "123456789 345678901   567890123 789012345     901234567 123456789 234567890";
        char result[MAX_LINE_LENGTH + 1] = {0};
        justify_line(input, MAX_LINE_LENGTH, result);
        printf("|%s|\n", input);
        printf("|%s|\n\n", result);
    }
    {
        char input[] = "   123456789 567890123   901234567    345678901     789012345 1234   ";
        char result[MAX_LINE_LENGTH + 1] = {0};
        justify_line(input, MAX_LINE_LENGTH, result);
        printf("|%s|\n", input);
        printf("|%s|\n\n", result);
    }
    {
        char input[] = "";
        char result[MAX_LINE_LENGTH + 1] = {0};
        justify_line(input, MAX_LINE_LENGTH, result);
        printf("|%s|\n", input);
        printf("|%s|\n\n", result);
    }
    {
        char input[] = " ";
        char result[MAX_LINE_LENGTH + 1] = {0};
        justify_line(input, MAX_LINE_LENGTH, result);
        printf("|%s|\n", input);
        printf("|%s|\n\n", result);
    }
    {
        char input[] = "               ";
        char result[MAX_LINE_LENGTH + 1] = {0};
        justify_line(input, MAX_LINE_LENGTH, result);
        printf("|%s|\n", input);
        printf("|%s|\n\n", result);
    }
    {
        char input[] = "123456789 123456789 123456789 123456789 123456789 123456789 123456789 1234567890";
        char result[MAX_LINE_LENGTH + 1] = {0};
        justify_line(input, MAX_LINE_LENGTH, result);
        printf("|%s|\n", input);
        printf("|%s|\n\n", result);
    }
    {
        char input[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
        char result[MAX_LINE_LENGTH + 1] = {0};
        justify_line(input, MAX_LINE_LENGTH, result);
        printf("|%s|\n", input);
        printf("|%s|\n\n", result);
    }
    return (EXIT_SUCCESS);
}

