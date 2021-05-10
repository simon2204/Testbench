//
//  ppr_tb_logging_json.h
//  PPRTestbenchLogging
//
//  Created by Simon Schöpke on 05.05.21.
//

#ifndef ppr_tb_logging_json_h
#define ppr_tb_logging_json_h

#define LOGGING_SIZE 10000

/**
 * Protokolliert in der Datei #ASSERT_FILENAME, dass ein weiterer Testfall
 * durchgeführt wurde. Dazu wird die in der Datei ein neues JSON Objekt
 * eingefügt.
 */
extern void ppr_tb_log_testcase(int id, int groupId, char *info, char *expected, char *actual, char* error, int total);

extern void pollute_stack(void);

#endif /* ppr_tb_logging_json_h */
