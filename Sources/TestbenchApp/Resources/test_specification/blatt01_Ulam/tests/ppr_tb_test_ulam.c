#include <stdio.h>
#include <stdlib.h>
#include "testbench_logging.h"


extern int ulam_max(int a_0);
extern int ulam_twins(int limit);
extern int ulam_multiples(int limit, int number);



void test_ulam_max(int task_id, int input_val, int expected_result)
{
    int result = ulam_max(input_val);
    char buffer[4096];
    snprintf(buffer, sizeof buffer, "ulam_max(%d) gab den Wert %d zurück. Erwartet wurde der Wert %d.", input_val, result, expected_result);
    log_result(task_id, expected_result == result, buffer);
}

void test_ulam_twins(int task_id, int input_val, int expected_result)
{
    int result = ulam_twins(input_val);
    char buffer[4096];
    snprintf(buffer, sizeof buffer, "ulam_twins(%d) gab den Wert %d zurück. Erwartet wurde der Wert %d.", input_val, result, expected_result);
    log_result(task_id, expected_result == result, buffer);
}

void test_ulam_multiples(int task_id, int input_val_1, int input_val_2, int expected_result)
{
    int result = ulam_multiples(input_val_1, input_val_2);
    char buffer[4096];
    snprintf(buffer, sizeof buffer, "ulam_multiples(%d, %d) gab den Wert %d zurück. Erwartet wurde der Wert %d.", input_val_1, input_val_2, result, expected_result);
    log_result(task_id, expected_result == result, buffer);
}



int main(int argc, char **argv)
{
    
    /* ulam_max(-1) = -1 */
    pollute_stack();
    test_ulam_max(1, -1, -1);
    
    /* ulam_max(0) = -1 */
    pollute_stack();
    test_ulam_max(2, 0, -1);
    
    /* ulam_max(1) = 1 */
    pollute_stack();
    test_ulam_max(3, 1, 1);
    
    /* ulam_max(2) = 2 */
    pollute_stack();
    test_ulam_max(4, 2, 2);
    
    /* ulam_max(3) = 16 */
    pollute_stack();
    test_ulam_max(5, 3, 16);
    
    /* ulam_max(4) = 4 */
    pollute_stack();
    test_ulam_max(6, 4, 4);
    
    /* ulam_max(5) = 16 */
    pollute_stack();
    test_ulam_max(7, 5, 16);
    



    /* ulam_twins(0) = -1 */
    pollute_stack();
    test_ulam_twins(8, 0, -1);
    
    /* ulam_twins(5) = -1 */
    pollute_stack();
    test_ulam_twins(9, 5, -1);
    
    /* ulam_twins(6) = 5 */
    pollute_stack();
    test_ulam_twins(10, 6, 5);




    /* ulam_multiples(0, 2) = -1 */
    pollute_stack();
    test_ulam_multiples(11, 0, 2, -1);
    
    /* ulam_multiples(10, 0) = -1 */
    pollute_stack();
    test_ulam_multiples(12, 10, 0, -1);
    
    /* ulam_multiples(5, 2) = -1 */
    pollute_stack();
    test_ulam_multiples(13, 5, 2, -1);
    
    /* ulam_multiples(109, 4) = -1 */
    pollute_stack();
    test_ulam_multiples(14, 109, 4, -1);
    
    /* ulam_multiples(110, 4) = 107 */
    pollute_stack();
    test_ulam_multiples(15, 110, 4, 107);
    
    /* ulam_multiples(111, 4) = 108 */
    pollute_stack();
    test_ulam_multiples(16, 111, 4, 108);
    
    /* ulam_multiples(1000, 2) = 982 */
    pollute_stack();
    test_ulam_multiples(17, 1000, 2, 982);
    
    /* ulam_multiples(391, 6) = 386 */
    pollute_stack();
    test_ulam_multiples(18, 391, 6, 386);

    
    return (EXIT_SUCCESS);
}

