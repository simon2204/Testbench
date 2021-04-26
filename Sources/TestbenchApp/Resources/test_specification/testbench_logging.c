#include "testbench_logging.h"
#include <stdio.h>

extern void log_result(int task_id, bool successful, char* reason)
{
    char buffer[4096] = {0};
    snprintf(buffer, sizeof buffer, "%d\t%s\t%s\n", task_id, successful ? "success": "failed", reason);
    
    FILE* file = fopen("testresult.csv", "a");
    if(file == NULL)
    {
        fprintf(stderr, "CAN NOT OPEN FILE: testresult.csv!");
    }
    fputs(buffer, file);
    fclose(file);
}

// the variable junk is not used. gcc prints out a warning which we don't want to have in the feedback report.
// the pragma statement ignores this type of warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
extern void pollute_stack()
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
