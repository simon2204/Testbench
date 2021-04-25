/**
 * @file  wait_and_exit.c
 *        Ueberprueft fortlaufend, ob die verstrichene Zeit groesser ist, 
 *        als die uebergebene Timeout-Zeitspanne. Ist das der Fall, wird der 
 *        entsprechende Prozess (Prozessname wird als Parameter uebergeben) 
 *        beendet.
 *
 *        Ist die symbolische Konstante FUNCTION_TEST definiert, wird 
 *        eine entsprechende Fehlermeldung in die Protokolldatei geschrieben.
 *        Dazu muss die Funktion  tb_print_error_msg_timeout() aufgerufen 
 *        werden.
 *        Die Konstante wird gesetzt durch die Compiler-Option -DFUNCTION_TEST
 *
 * @author C. Huber, basierend auf einer alten Version von F. Bachmann
 *
 * @date 2014-07-23
 */


/* ============================================================================
 * Header-Dateien einbetten
 * ========================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <execinfo.h>
#include <signal.h>

#include "ppr_tb_logging.c"



/* ============================================================================
 * Testbench - Symbolische Konstanten
 * ========================================================================= */

/**
 * max. Anzahl von Kommandozeilenargumenten
 */
#define MAX_ARGS 5

/**
 * max. Anzahl von Zeichen eines Attributs eines Kommandozeilenarguments
 */
#define MAX_ARG_LENGTH 255

/**
 * Option der Kommandozeile fuer das Build-Verzeichnis (Pflichtangabe)
 */
#define BUILDDIR_PARAM "-builddir"

/**
 * Option der Kommandozeile fuer den zu terminierenden Prozess (Pflichtangabe)
 */
#define APP_PARAM "-app"

/**
 * Option der Kommandozeile fuer die Zeitspanne, in der der angegebene Prozess
 * beendet sein muss, andernfalls wird er durch das Signal SIGTERM (Software 
 * termination signal) zur Terminierung veranlasst. Falls kein Wert uebergeben
 * wurde, wird ein Default-Wert herangezogen.
 */
#define TIMEOUT_PARAM "-timeout"

/**
 * Option der Kommandozeile für die Praktikumsleistungen_csv Datei des jeweiligen
 * Tests um bei einem Kill am Ende noch die Testrate erzeugen zu können.
 */
#define CSV_PARAM "-csv"

/**
 * Fehlermeldungstext 
 */
#define MISSING_OPTION "Zu wenige Kommandozeilenparameter, das Programm wird beendet. "

/** 
 * Fehlermeldungstext fuer den Fall, dass der Testfaelle-Prozess gezielt
 * beendet wurde.
 */
#define ERROR_MSG_TIMEOUT "Test nach ueberschreiten des Zeitlimits abgebrochen."

/** Befehl zum Abrufen der Prozessstautsdaten in Textform
 */
#define CMD_PS "ps -s | grep "

/** Umleitung Standardausgabe, bspw in Datei
 */
#define REDIRECT " > "

/** Aktuelles Verzeichnis
 */
#define CURRENT_DIR "./"

/** Zeichen, das bei der Pfadangabe verwendet wird
 */
#define SLASH "/"

/** temporaere Datei, in der die aktuellen Prozessstatusdaten festgehalten 
 *  werden
 */
#define PROCESS_STATUS_FILE "prozess_status.txt"

/** temporaere Datei, in der bestimmte Test-Aktionen festgehalten werden
 */
#define PROTOKOLL_TESTFILES "protokoll_testfiles.txt"

/** Befehl zum Beenden eines Prozesses in Textform (Systemaufruf)
 */
#define CMD_KILL "kill"

/** Signal SIGPIPE zum terminieren einen Prozesses ohne Output
 */
#define SW_TERM_SIGNAL "-13"

/** Standard-Wert fuer die Timeout-Zeitspanne; wird herangezogen, falls 
 *  kein Timeout-Wert uebergeben wurde. Vergeht diese Zeitspanne, 
 *  ohne dass die Testfaelle (ein Prozess) von sich aus endeten, so wird
 *  eine Terminierung dieses Prozesses veranlasst
 */
#define DEFAULT_TIMEOUT 2.0

/** Maximal zulaessige Zeichenlaenge fuer einen Befehl in Textform
 */
#define MAX_LENGTH 255

/** Maximal zulaessige Zeichenlaenge fuer die Prozess-ID in Textform
 */
#define MAX_LENGTH_PID 6

/** Maximale Prozesse die gleichzeitig laufen können.
*/
#define MAX_PROCESS 15

/* ===========================================================================
 * Testbench - Typdefinitionen
 * ======================================================================== */

/**
 * Symbolische Konstanten fuer die Kommandozeilenargumente
 */
enum options {
    NO_OPTION,
    BUILDDIR_OPTION,
    APP_OPTION,
    TIMEOUT_OPTION,
    CSV_OPTION
};

/**
 * Wahrheitswerte.
 */
typedef enum {
    TB_FALSE,
    TB_TRUE
} TB_BOOL;


/* ============================================================================
 * Testbench - Funktionsprototypen
 * ========================================================================= */

/**
 * Diese Funktion wird ausgeführt, nachdem ein Segmentation Fault (sigsegv) 
 * aufgetreten ist (der Prozess das signal sigsegv empfangen hat). 
 * Sie gibt einen Stacktrace aus, um die Absturzursache zu 
 * analysieren und beendet das Programm mit dem Fehlercode 1.
 * 
 * param sig Nummer des Signals
 */
static void sigsegv_handler(int sig);

#ifdef FUNCTION_TEST
/**
 * Dient dazu, eine Timeout-Fehlermeldung auszugeben (Protokolldatei),
 * nachdem eine Prozessterminierung durchgefuehrt worden ist
 *
 */
static void tb_print_error_msg_timeout();
#endif

/**
 * Ordnet einem Kommandozeilenparameter, welcher als String vorliegt eine 
 * nummerische Konstante gemaess "enum_options" zu.
 *
 * @param p_argument    Der zu pruefende Parameter
 * @return              Numerische Konstante des Parameters
 */
static int tb_get_option(char *p_argument);

/**
 * Ordnet die uebergebenen Kommandozeilenparameter in den Vektor options. Die
 * Position einer Option im Vektor options ergibt sich aus der Aufzaehlung
 * "enum options".
 *
 * @param argc      Die Anzahl der Kommandozeilenargumente
 * @param argv      Enthaelt alle Kommandozeilenargumente als Strings
 * @param options   Vektor, der die uebergebenen Argumente in einer
 *                  definierten Reihenfolge (enum_options) enthaelt
 * @return          TB_TRUE, wenn alle Optionen korrekt sind, TB_FALSE sonst
 */
static TB_BOOL tb_classify_options(int argc, char *argv[],
        char options[][MAX_ARG_LENGTH]);

/**
 * Ueberprueft fortlaufend, ob die verstrichene Zeit groesser ist, 
 * als die uebergebene Timeout-Zeitspanne. Ist das der Fall, wird der 
 * entsprechende Prozess (Prozessname wird als Parameter uebergeben) 
 * beendet.
 * 
 * @param argc      Anzahl der uebergebenen Kommandozeilenargumente.
 * @param argv      Vektor der Kommandozeilenargumente.
 * @return          EXIT_FAILURE im Fehlerfall, EXIT_SUCCESS sonst.
 * 
 */
int main(int argc, char *argv[]);


/* ============================================================================
 * Testbench - Funktionsdefinitionen
 * ========================================================================= */


/* ---------------------------------------------------------------------------
 * Funktion: sigsegv_handler
 * ------------------------------------------------------------------------- */
static void sigsegv_handler(int sig) {
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

/* ---------------------------------------------------------------------------
 * Funktion: tb_print_error_msg_timeout
 * ------------------------------------------------------------------------- */
static void tb_print_error_msg_timeout() {
    /* Test wurde abgebrochen...
     * Eine entprechende Fehlermeldung wird ausgegeben.
     */
    printf("[ERROR]\n"
            "   %s\n", ERROR_MSG_TIMEOUT);
    fflush(stdout);
}

/* --------------------------------------------------------------------------
 * Funktion: tb_classify_options
 * ----------------------------------------------------------------------- */
static TB_BOOL tb_classify_options(int argc, char *argv[], char options[][MAX_ARG_LENGTH]) 
{

    /* Bestimmt den Typ des letzten gelesenen Parameters. */
    int option;
    /* Laufvariable ueber alle Elemente des argv. */
    int index;
    /* Gibt an, ob in der Argumentliste ein Fehler gefunden wurde */
    TB_BOOL has_correct_args = TB_TRUE;

    /* Optionen zuruecksetzen */
    for (index = 0; index < MAX_ARGS; index++) 
    {
        options[index][0] = '\0';
    }

    /* Optionen ermitteln */
    for (index = 1; (index < argc && has_correct_args); index = index + 2) 
    {

        option = tb_get_option(argv[index]);

        if (option == NO_OPTION) 
        {
            printf("[ERROR] Testbench: Option %s unbekannt.\n", argv[index]);
            has_correct_args = TB_FALSE;
        } 
        else if (index + 1 >= argc) 
        {
            printf("[ERROR] Testbench: Parameter zu Option %s fehlt.\n", argv[index]);
            has_correct_args = TB_FALSE;
        } 
        else 
        {
            strcpy(options[option], argv[index + 1]);
        }
    }

    return has_correct_args;
}

/* --------------------------------------------------------------------------
 * Funktion: tb_get_option
 * ----------------------------------------------------------------------- */
static int tb_get_option(char *p_argument) 
{
    int option;

    if (strcmp(p_argument, BUILDDIR_PARAM) == 0) 
    {
        option = BUILDDIR_OPTION;
    } 
    else if (strcmp(p_argument, APP_PARAM) == 0) 
    {
        option = APP_OPTION;
    } 
    else if (strcmp(p_argument, TIMEOUT_PARAM) == 0) 
    {
        option = TIMEOUT_OPTION;
    } 
    else if (strcmp(p_argument, CSV_PARAM) == 0) 
    {
        option = CSV_OPTION; 
    } 
    else 
    {
        option = NO_OPTION;
    }

    return option;
}

/* ----------------------------------------------------------------------------
 * Funktion: main
 * ------------------------------------------------------------------------- */
int main(int argc, char *argv[]) 
{

    /* Variablendeklaration fuer die Zeitmessung */
    clock_t time_start;
    double time_used;
    double timeout;

    /* Variablendeklaration fuer die Verarbeitung der Prozesstatusdaten (PID)
     */

    /* Prozessstatusdatei */
    FILE *CSV;

    /* Aktuell gelesenes Zeichen aus der Prozessstatusdatei */
    int zeichen;

    int spalte = 0;
    int status_code = -1;
    char pid[MAX_PROCESS][MAX_LENGTH_PID];
    int z = 0;
    int s = 0;

    time_used = 0.0;

    /* 
     * Zeitmessung wird gestartet
     */
    time_start = time(NULL);

    /* Installieren des Signalhandlers für den Stacktrace im Falle eines Segmentation Faults */
    signal(SIGSEGV, sigsegv_handler);
    signal(SIGTTIN, sigsegv_handler);
    signal(SIGTTOU, sigsegv_handler);
    signal(SIGPIPE, sigsegv_handler);

    /* --- START Kommandozeilenargumente auswerten ----------------------------- */
    char options[MAX_ARGS][MAX_ARG_LENGTH];

    /*  Programmname */
    char app_name[MAX_ARG_LENGTH] = "";
    strcpy(app_name, argv[0]);

    /* Angabe ob Praktikumsleiustungen_csv übergeben wurde */
    TB_BOOL is_csv = TB_FALSE;

    if (tb_classify_options(argc, argv, options)) 
    {
        /* Pruefen, ob Build-Verzeichnis, bspw. "blatt02/000000000/build" 
         * uebergeben wurde. 
         */
        if (options[BUILDDIR_OPTION][0] == '\0') 
        {
            printf("[ERROR] Testbench %s: "
                    "Benutzerverzeichnis unbekannt.\n", app_name);
            exit(EXIT_FAILURE);
        }
        /* Pruefen, ob Prozessname, bspw. "hpr3_test" angegeben wurde. */
        if (options[APP_OPTION][0] == '\0') 
        {
            printf("[ERROR] Testbench %s: "
                    "Testverzeichnis unbekannt.\n", app_name);
            exit(EXIT_FAILURE);
        }
        /* Pruefen ob CSV Datei angegeben wurde um Praktikumsleistungen zu schreiben */
        if (options[CSV_OPTION][0] != '\0') 
        {
            is_csv = TB_TRUE;
        }
        /* ======== END Kommandozeilenargumente auswerten ==================== */

        /* Falls Timeout nicht uebergeben wurde, wird der Default-Wert herangezogen.
         */
        if (options[TIMEOUT_OPTION][0] == '\0') 
        {
            /* Timeout wurde nicht uebergeben; der Default-Wert wird herangezogen.
             */
            timeout = DEFAULT_TIMEOUT;
        } 
        else 
        {
            /* Timeout wurde uebergeben. 
             */
            timeout = atof(options[TIMEOUT_OPTION]);
        }

        


        /*====================================================================*/
        /*====================================================================*/
        /*
         *  Neuer Ansatz: 
         *      1. PID auslesen durch finden des Programms, dass in die 
         *         praktikumsleistungen.csv Datei schreibt.
         *      2. Schreiben der Prozess ID in eine Statusdatei
         *      3. Einlesen der Statusdatei um PID zu erhalten
         *      4. überprüfen ob Prozessordner im Verzeichnis 
         *                 /proc/PID existiert. Solange überprüfen, bis der 
         *                 Ordner nicht mehr existiert,
         *         dann ist das Programm beendet. Sonst Timeout.
         *
         */
        /*====================================================================*/
        /*====================================================================*/
        /* 1. Prozessstatus-Datei erzeugen, in der die gesuchte PID
         *    enthalten ist
         */
        /* Prozessstatus-Datei (einschl. Pfadangabe) konstruieren */
        char datei[MAX_LENGTH] = CURRENT_DIR;
        strcat(datei, options[BUILDDIR_OPTION]);
        strcat(datei, SLASH);
        strcat(datei, PROCESS_STATUS_FILE);

        /* Befehl zur Erzeugung der Prozesssatus-Daten konstruieren durch 
         * aneinanderhaengen von Teilstrings, bspw.
         * ---------------------------------------------------
         *
         * ps ax | grep ppr_tb_submission 
         * | grep -v cd | grep -v grep 
         * | grep -v build > ./blatt02/build/prozess_status.txt
         * 
         * ---------------------------------------------------
         */

        char cmd1_ps[MAX_LENGTH] = "ps ax | grep ";
        strcat(cmd1_ps, options[APP_OPTION]);
        strcat(cmd1_ps, " | grep -v cd | grep -v grep | grep -v build | awk '{print $1}'");
        strcat(cmd1_ps, REDIRECT);
        strcat(cmd1_ps, datei);

        /* 2. Schreiben der PID in Datei durch Befehl der oben zusammengestezt wurde
         */
        status_code = system(cmd1_ps);

        /* 3. Falls befehl erfolgreich ausgeführt worden ist, auslesen der PID.
         */
        if (status_code == 0) 
        {
        
            /* Prozessstatus-Datei zum Lesen oeffnen */
            CSV = fopen(datei, "r");
            if (NULL == CSV) 
            {

                /* Im Fehlerfall wird die Meldung nicht in die Ausgabedatei 
                 * geschrieben (->stderr)
                 */
                fprintf(stderr, "Fehler beim Oeffnen der Datei %s\n", datei);

                return EXIT_FAILURE;
            }
            /* Aus der Prozessstatus-Datei den Eintrag fuer die PID ermitteln */

            sleep(1);
            for (s = 0; ((zeichen = getc(CSV)) != EOF); s++) 
            {
                if(zeichen == '\n' || zeichen == '\r') 
                {
                    pid[z][s] = '\0';
                    //fprintf(stderr, "PID=%s\n",pid[z]);
                    z++;
                    s = 0;
                    
                } 
                else 
                {
                    pid[z][s] = (char) zeichen;
                }  
        
            }
            
            /* neue Zeile nach EOF mit NULL belegen */
            pid[z+1][0] = '\0';

            /*  i = 0;
             *  zeichen = getc(CSV);
             *  while ((zeichen != EOF)) {
             *      if(zeichen == ' ') break;
             *      pid[i] = (char) zeichen;
             *      fprintf(stderr, "PID %c\n", pid[i]);
             *      i = i + 1;
             *      zeichen = getc(CSV);
             *  }
             *      pid[s] = '\0'; 
             */
        }
        
        /*
         * 4. Ordner prüfen, bis er nicht mehr existiert und Befehl einen Fehler wirft.
         */
        int i = 0;
        for(i = 0; pid[i][0] != '\0'; i++) 
        {
            /* fprintf(stderr,"PID=%s\n", pid[i]); */
            char cmd_ls_pid[MAX_LENGTH] = "ls /proc/";
            strcat(cmd_ls_pid, pid[i]);
            strcat(cmd_ls_pid, " -d > /dev/null 2>&1");
            status_code = system(cmd_ls_pid);

            /* Warte solange die beiden folgenden Bedingungen erfuellt bleiben:
             *
             * 1. Der Testfaelle-Prozess wird unter "/proc/" noch 
             *    aufgefuehrt (status_code = 0) 
             *
             * 2. TIMEOUT-Zeitspanne ist nicht ueberschritten
             */
            
            while ((status_code == 0) && (time_used < timeout)) 
            {
                //sleep(1); /* 1 sec. Pause */
                status_code = system(cmd_ls_pid);
                time_used = (double) (time(NULL) - time_start);
            }

            /*==============================================================================*/
            /*==============================================================================*/

            /* 
             * TIMEOUT-Zeitspanne wurde ueberschritten 
             */
            if (status_code == 0) 
            {

                /*  Den Prozess mit der ermittelten PID terminieren
                 *  (Befehl "kill <PID>"
                 */

                /* Befehl konstruieren zum Terminieren des Prozesses */
                char cmd_kill[MAX_LENGTH] = CMD_KILL;
                strcat(cmd_kill, " ");
                strcat(cmd_kill, SW_TERM_SIGNAL);
                strcat(cmd_kill, " ");
                strcat(cmd_kill, pid[i]);

                /* Prozessterminierung starten, um den entsprechenden Prozess
                 * (Anwendung hpr3_test.exe) zu beenden 
                 */
                system(cmd_kill);

#ifdef FUNCTION_TEST
                /* 
                 * Wegen der Prozessterminierung (Test wird vorzeitig abgebrochen)
                 * wird eine entsprechende Fehlermeldung* (s.u.) in die Protokolldatei 
                 * geschrieben. Dazu wird die Funktion 
                 *           tb_print_error_msg_timeout()
                 * aufgerufen.
                 *
                 * *) Ausschnitt aus der Protokolldatei (Beispiel):
                 * ---------------------------------------------------
                 * /bin/sh: line 1:  1176 Terminated   ./hpr3_test.exe 
                 *  [ERROR]
                 *     Test abgebrochen.
                 * ---------------------------------------------------
                 */
                /*sleep(1);*/ /* 1 sec. Pause */
                
                tb_print_error_msg_timeout();


                if(is_csv == TB_TRUE) 
                {
                    /*
                     *Weiterhin werden die Korrekt durchgeführten Tests am Ende  
                     * ausgegeben.
                     * 
                     * 1. Erzeugen des Pfades zum Build Ordner (/blatt02/build)
                     * 2. Write Summary ausführen mit dem Pfad zum Build Ordner
                     *    und dem Pfad zur CSV Datei
                     */
                    char build[MAX_LENGTH] = "";
                    strcat(build, options[BUILDDIR_OPTION]);
                    strcat(build, SLASH);

                    ppr_tb_write_summary(build, options[CSV_OPTION]);
                }
        


#endif
                printf("Anwendung wurde aufgrund von Zeitüberschreitung beendet.\n");
                return (EXIT_FAILURE);

            } 
            else 
            {
                /* Fall 1 ist eingetreten (s.o.): Der Prozess endete ordnungsgemaess
                 * - von sich aus, innerhalb der vorgegebenen Timeout-Zeitspanne
                 * oder anders formuliert, der Prozess ist/war unter "ps" nicht mehr
                 * zu sehen, d.h. Timeout wurde nicht ueberschritten.
                 * -> OK, do nothing!
                 */
                /*  time_used = (double) (clock() - time_start) / CLOCKS_PER_SEC; */
                /* return (EXIT_SUCCESS);  */
            }
        }
        
        char cmd1_test[MAX_LENGTH] = "";
        strcat(cmd1_test, "test -e ");
        strcat(cmd1_test, options[BUILDDIR_OPTION]);
        strcat(cmd1_test, "/");
        strcat(cmd1_test, "ppr_tb_asserts.log");
        status_code = system(cmd1_test);
        
        /* Anwendung konnte nicht gebaut und somit nicht gestartet werden */
        if (status_code != 0)
        {
            if(is_csv == TB_TRUE) 
            {
                char build[MAX_LENGTH] = "";
                strcat(build, options[BUILDDIR_OPTION]);
                strcat(build, SLASH);
                ppr_tb_write_summary(build, options[CSV_OPTION]);
            }
            printf("Anwendung konnte nicht gebaut und somit auch nicht getestet werden.\n");
            return (EXIT_FAILURE);
        }

        char cmd2_test[MAX_LENGTH] = "";
        strcat(cmd2_test, "test -e ");
        strcat(cmd2_test, options[BUILDDIR_OPTION]);
        strcat(cmd2_test, "/");
        strcat(cmd2_test, "ppr_tb_successful.log");
        status_code = system(cmd2_test);
        
        /* Anwendung wurde gebaut und gestartet, ist aber abgestürzt */
        if (status_code != 0)
        {
            if(is_csv == TB_TRUE) 
            {
                char build[MAX_LENGTH] = "";
                strcat(build, options[BUILDDIR_OPTION]);
                strcat(build, SLASH);
                ppr_tb_write_summary(build, options[CSV_OPTION]);
            }
            //printf("Anwendung wurde gebaut und gestartet, ist aber abgestürzt.\n");
            return (EXIT_FAILURE);
        }

    } 
    else 
    {
        printf("Kommandozeilenargumente unvollständig\n");
        return (EXIT_FAILURE);
    }


    return (EXIT_SUCCESS);
}
