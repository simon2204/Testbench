#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "testbench_logging.h"


#define MAX_SIZE 10
extern double get_determinant(double matrix[MAX_SIZE][MAX_SIZE], int size);


void matrix_to_string(double matrix[MAX_SIZE][MAX_SIZE], int matrix_size, char* result)
{
    if(matrix_size > MAX_SIZE)
    {
        strcat(result, "[...]");
        return;
    }
    strcat(result, "[");
    for(int i = 0; i < matrix_size; i++)
    {
        strcat(result, "[");
        for(int j = 0; j < matrix_size; j++)
        {
            char buffer[128];
            snprintf(buffer, sizeof buffer, "%.2f", matrix[i][j]);
            strcat(result, buffer);

            if(j != matrix_size -1)
            {
                strcat(result, ", ");
            }
        }
        strcat(result, "]");

        if(i != matrix_size -1)
        {
            strcat(result, ", ");
        }
    }
    strcat(result, "]");
    strcat(result, "\0");
}


void test_get_determinant(int task_id, double input_val[MAX_SIZE][MAX_SIZE], int matrix_size, double expected_result) 
{
    double result = get_determinant(input_val, matrix_size);

    char matrix_str[2048] = {0};
    matrix_to_string(input_val, matrix_size, matrix_str);


    char buffer[4096] = {0};
    snprintf(buffer, sizeof buffer, "get_determinant(%s, %d) gab den Wert %f zurück. Erwartet wurde der Wert %f.", matrix_str, matrix_size, result, expected_result);
    log_result(task_id, fabs(result - expected_result) < 0.01, buffer);
}


int main(int argc, char **argv)
{   
    {
        double matrix[MAX_SIZE][MAX_SIZE] = {{1}};
        pollute_stack();
        test_get_determinant(1, matrix, 1, 1.0);
    }
    

    {
        double matrix[MAX_SIZE][MAX_SIZE] = {
            {1, 2},
            {3, 4}
        };
        pollute_stack();
        test_get_determinant(2, matrix, 2, -2.0);
    }
    

    {
        double matrix[MAX_SIZE][MAX_SIZE] = {
            {-1, -2},
            {-3, -4}
        };
        pollute_stack();
        test_get_determinant(3, matrix, 2, -2.0);
    }
    

    {
        double matrix[MAX_SIZE][MAX_SIZE] = {
            {0, 1, 2},
            {3, 2, 1},
            {1, 1, 0}
        };
        pollute_stack();
        test_get_determinant(4, matrix, 3, 3.0);
    }
    
    {
        double matrix[MAX_SIZE][MAX_SIZE] = {
            {-1.1, -2.2, -3.4},
            {-3.2, -2.7, -1.3},
            {-1.2, -1.6, -0.7}
        };
        pollute_stack();
        test_get_determinant(5, matrix, 3, -4.68);
    }
    
    {
        double matrix[MAX_SIZE][MAX_SIZE] = {
            {1,  2, 3},
            {4, -5, 6},
            {7,  8, 9}
        };
        pollute_stack();
        test_get_determinant(6, matrix, 3, 120.0);
    }

    {
        double matrix[MAX_SIZE][MAX_SIZE] = {
            {1, -1,  2  , -3},
            {4,  0,  3.5,  1},
            {2, -5,  1  ,  0},
            {3, -1, -1  ,  2}
        };
        pollute_stack();
        test_get_determinant(7, matrix, 4, 184.5);
    }
    

    {
        double matrix[MAX_SIZE][MAX_SIZE];
        for (int row = 0; row < MAX_SIZE; row++)
        {
            for (int column = 0; column < MAX_SIZE; column++)
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
        pollute_stack();
        test_get_determinant(8, matrix, 10, -4411917.34);
    }


    {
        double matrix[MAX_SIZE][MAX_SIZE];
        pollute_stack();
        test_get_determinant(9, matrix, 0, 0.00);
    }
    

    {
        double matrix[MAX_SIZE][MAX_SIZE];
        pollute_stack();
        test_get_determinant(10, matrix, MAX_SIZE + 1, 0.00);
    }

    return (EXIT_SUCCESS);
}




