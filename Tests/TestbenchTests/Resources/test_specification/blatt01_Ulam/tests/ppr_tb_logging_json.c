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

/* ======================================================================
 * Makros
 * ====================================================================*/

/**
 * Name der Datei, in der die Testfälle
 * zwischengespeichert wird, damit sie auch nach Absturz des Programmes
 * noch verfügbar ist
 */
#define ASSERT_FILENAME "ppr_tb_asserts_json.log"


#define JSON_FORMAT "{\"id\": %d, \"groupId\": %d, \"info\": \"%s\", \"expected\": \"%s\", \"actual\": \"%s\", \"error\": \"%s\", \"total\": %d}\n"


/* ======================================================================
 * Funktionsdefinitionen
 * ====================================================================*/

extern void ppr_tb_log_testcase(int id, int groupId, char *info, char *expected, char *actual, char* error, int total)
{
    FILE* stream;

    stream = fopen(ASSERT_FILENAME, "a");
    
    if(stream == NULL)
    {
        printf("cannot open assert log \"" ASSERT_FILENAME "\"\n");
        exit(EXIT_FAILURE);
    }
    
    fprintf(stream, JSON_FORMAT, id, groupId, info, expected, actual, error, total);
      
    fclose(stream);
}

// the variable junk is not used. gcc prints out a warning which we don't want to have in the feedback report.
// the pragma statement ignores this type of warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
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
#pragma GCC diagnostic pop
