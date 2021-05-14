//
//  ppr_tb_logging_json.c
//  PPRTestbenchLogging
//
//  Created by Simon Schöpke on 05.05.21.
//

#include "ppr_tb_logging_json.h"

/* ======================================================================
 * Header-Dateien
 * ====================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "replace_substring.h"

/* ======================================================================
 * Makros
 * ====================================================================*/

/**
 * Name der Datei, in der die Testfälle
 * zwischengespeichert wird, damit sie auch nach Absturz des Programmes
 * noch verfügbar ist.
 */
#define ASSERT_FILENAME "ppr_tb_asserts_json.log"

#define JSON_FORMAT "{\"id\": %d, \"groupId\": %d, \"info\": \"%s\", \
\"expected\": \"%s\", \"actual\": \"%s\", \"error\": \"%s\", \"total\": %d}\n"

#define REPLACE "\n"

#define WITH "\\n"

/* ======================================================================
 * Funktionsdefinitionen
 * ====================================================================*/

extern void ppr_tb_log_testcase(int id, int groupId,
                                char info[LOGGING_SIZE], char expected[LOGGING_SIZE],
                                char actual[LOGGING_SIZE], char error[LOGGING_SIZE],
                                int total)
{
    FILE* stream;
    
    stream = fopen(ASSERT_FILENAME, "a");
    
    if(stream == NULL)
    {
        printf("cannot open assert log \"" ASSERT_FILENAME "\"\n");
        exit(EXIT_FAILURE);
    }
    
    char info_new_line_escaped[LOGGING_SIZE * 2] = {0};
    char expected_new_line_escaped[LOGGING_SIZE * 2] = {0};
    char actual_new_line_escaped[LOGGING_SIZE * 2] = {0};
    char error_new_line_escaped[LOGGING_SIZE * 2] = {0};
    
    replace_substring(info, REPLACE, WITH, info_new_line_escaped);
    replace_substring(expected, REPLACE, WITH, expected_new_line_escaped);
    replace_substring(actual, REPLACE, WITH, actual_new_line_escaped);
    replace_substring(error, REPLACE, WITH, error_new_line_escaped);
    
    fprintf(stream, JSON_FORMAT,
            id, groupId,
            info_new_line_escaped, expected_new_line_escaped,
            actual_new_line_escaped, error_new_line_escaped,
            total);
      
    fclose(stream);
}

// the variable junk is not used. gcc prints out a warning which we don't want to have in the feedback report.
// the pragma statement ignores this type of warning

extern void pollute_stack(void)
{
    const int size = 4096;
    char junk[size];
    char letter = 'A';
    
    for(int i = 0; i < size; i++) {
        junk[i] = letter;

        if(letter == 'Z')
            letter = 'A';
        else
            letter++;
    }
}
