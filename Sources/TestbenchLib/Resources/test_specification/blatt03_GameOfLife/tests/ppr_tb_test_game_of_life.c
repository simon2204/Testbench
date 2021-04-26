#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "testbench_logging.h"


#define ALL_ROWS 10
#define ALL_COLUMNS 10

extern void get_generation_as_string(char string[]);
extern void set_generation_from_string(char string[]);
extern bool set_next_generation();


void testfall_1()
{   
    char source_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    
    char expected_gen[ALL_ROWS * ALL_COLUMNS + 1];
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

    char result_gen[ALL_ROWS * ALL_COLUMNS + 1];
    get_generation_as_string(result_gen);
    
    log_result(1, strcmp(expected_gen, result_gen) == 0, "Failed");
}

void testfall_2(void)
{
    char source_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    
    char expected_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    set_next_generation();

    char result_gen[ALL_ROWS * ALL_COLUMNS + 1];
    get_generation_as_string(result_gen);

    log_result(2, strcmp(expected_gen, result_gen) == 0, "Failed");
}

void testfall_3(void)
{
    char source_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    
    char expected_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    set_next_generation();

    char result_gen[ALL_ROWS * ALL_COLUMNS + 1];
    get_generation_as_string(result_gen);
    
    log_result(3, strcmp(expected_gen, result_gen) == 0, "Failed");
}

void testfall_4(void)
{
    char source_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    
    char expected_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    set_next_generation();

    char result_gen[ALL_ROWS * ALL_COLUMNS + 1];
    get_generation_as_string(result_gen);
    
    log_result(4, strcmp(expected_gen, result_gen) == 0, "Failed");
}

void testfall_5(void)
{
    char source_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    
    char expected_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    set_next_generation();

    char result_gen[ALL_ROWS * ALL_COLUMNS + 1];
    get_generation_as_string(result_gen);
    
    log_result(5, strcmp(expected_gen, result_gen) == 0, "Failed");
}

void testfall_6(void)
{
    char source_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    
    char expected_gen[ALL_ROWS * ALL_COLUMNS + 1];
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

    set_next_generation();

    char result_gen[ALL_ROWS * ALL_COLUMNS + 1];
    get_generation_as_string(result_gen);
    
    log_result(6, strcmp(expected_gen, result_gen) == 0, "Failed");
}

void testfall_7(void)
{
    char source_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    
    char expected_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    set_next_generation();

    char result_gen[ALL_ROWS * ALL_COLUMNS + 1];
    get_generation_as_string(result_gen);
    
    log_result(7, strcmp(expected_gen, result_gen) == 0, "Failed");
}

void testfall_8(void)
{
    char source_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    
    char expected_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    set_next_generation();

    char result_gen[ALL_ROWS * ALL_COLUMNS + 1];
    get_generation_as_string(result_gen);
    
    log_result(8, strcmp(expected_gen, result_gen) == 0, "Failed");
}

void testfall_9(void)
{
    char source_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    
    char expected_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    set_next_generation();

    char result_gen[ALL_ROWS * ALL_COLUMNS + 1];
    get_generation_as_string(result_gen);
    
    log_result(9, strcmp(expected_gen, result_gen) == 0, "Failed");
}

void testfall_10(void)
{
    char source_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    
    char expected_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    set_next_generation();

    char result_gen[ALL_ROWS * ALL_COLUMNS + 1];
    get_generation_as_string(result_gen);
    
    log_result(10, strcmp(expected_gen, result_gen) == 0, "Failed");
}

void testfall_11(void)
{

    char source_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    
    char expected_gen[ALL_ROWS * ALL_COLUMNS + 1];
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
    for (int i = 1; i <= 32; i++)
    {
        set_next_generation();
    }

    char result_gen[ALL_ROWS * ALL_COLUMNS + 1];
    get_generation_as_string(result_gen);
    
    log_result(11, strcmp(expected_gen, result_gen) == 0, "Failed");
}


int main(int argc, char **argv)
{   
    pollute_stack();
    testfall_1();
    
    pollute_stack();
    testfall_2();
    
    pollute_stack();
    testfall_3();
    
    pollute_stack();
    testfall_4();
    
    pollute_stack();
    testfall_5();
    
    pollute_stack();
    testfall_6();
    
    pollute_stack();
    testfall_7();
    
    pollute_stack();
    testfall_8();
    
    pollute_stack();
    testfall_9();
    
    pollute_stack();
    testfall_10();
    
    pollute_stack();
    testfall_11();
    
    return (EXIT_SUCCESS);
}
