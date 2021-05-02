#include <stdbool.h>

#ifndef TESTBENCH_LOGGING
#define	TESTBENCH_LOGGING

extern void log_result(int task_id, bool successful, char* reason);

extern void pollute_stack();

#endif
