/* ======================================================================
 * Header-Dateien
 * ====================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "ppr_tb_logging.h"

/* ======================================================================
 * Makros
 * ====================================================================*/

/**
 * Name der Datei, in der die Zahl der erfolgreichen Testfälle 
 * zwischengespeichert wird, damit sie auch nach Absturz des Programmes 
 * noch verfügbar ist
 */
#define ASSERT_FILENAME "ppr_tb_asserts.log"

/**
 * Name der Datei, in der festgehalten wird, ob das Programm ohne Absturz
 * durchgelaufen ist
 */
#define RUN_SUCCESSFUL_FILENAME "ppr_tb_successful.log"

/**
 * Format-String für fprintf und fscanf, in diesem Format wird die Zahl 
 * in der Datei #ASSERT_FILENAME gespeichert wird.
 * total_asserts;passed_asserts 
 */
#define ASSERT_FORMAT "%03d;%03d\n" 

/**
 * Format String für fprintf der Praktikumsleistung CSV Datei.
 */
#define CSV_FORMAT "%s;%03d\n"

/**
 * Name der Datei mit den Benutzerinformationen
 */
#define USER_PROPERTIES_FILE "UserId.properties"

/**
 * Maximale Länge der Zeilen in den Eingabedateien
 */
#define SIZE 100
    

/* ======================================================================
 * Funktionsdefinitionen
 * ====================================================================*/

extern void ppr_tb_log_assert(void)
{
    int passed_asserts = 0;
    int total_asserts = 0;
    FILE* stream;
    
    errno = 0;

    stream = fopen(ASSERT_FILENAME, "r+");
    if(stream == NULL) 
    {
        if (errno == ENOENT)
        {
            stream = fopen(ASSERT_FILENAME, "w+");
            fprintf(stream, ASSERT_FORMAT, 0, 0);
            rewind(stream);
        }
        if (stream == NULL) 
        {
            printf("cannot open assert log \"" ASSERT_FILENAME "\"\n");
            exit(EXIT_FAILURE);
        }       
    }
      
    fscanf(stream, ASSERT_FORMAT, &total_asserts, &passed_asserts);
    passed_asserts++;
    
    rewind(stream);
    fprintf(stream, ASSERT_FORMAT, total_asserts, passed_asserts); 
    
    fclose(stream);
}


extern void ppr_tb_write_summary(char* directory, char* exercise)
{
    int passed_asserts;
    int total_asserts;
    int rate;
    
    FILE* stream;
    
    /* Pfad zum ASSERT_FILE erstellen. Wichtig für den Aufruf aus 
     * ppr_tb_wait_and_exit bei einem Kill Signal.*/
    char assert_file[255] = "";
    strcat(assert_file, directory);
    strcat(assert_file, ASSERT_FILENAME);
    
    stream = fopen(assert_file, "r");
    if (stream == NULL)
    {
        passed_asserts = 0;
        total_asserts = 1;
    }
    else
    {
        fscanf(stream, ASSERT_FORMAT, &total_asserts, &passed_asserts);
        
        fclose(stream); 
    }
    
    rate = passed_asserts * 100 / total_asserts;
    
    printf("\n");
    printf("+-------------------------------------------------------------+\n");
    printf("| Tests (total): %2d, Tests (passed): %2d, Rating: %3d %%        |\n", 
           total_asserts, passed_asserts, rate);
    printf("+-------------------------------------------------------------+\n");
    printf("\n");
    
    char success_file[255] = "";
    strcat(success_file, directory);
    strcat(success_file, RUN_SUCCESSFUL_FILENAME);
    
    stream = fopen(success_file, "w");
    if (stream == NULL)
    {
        fprintf(stdout, "cannot open success log \"%s\"\n", success_file);
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(stream, "successfully executed\n");
        fclose(stream);
    }
    
    rate = (rate > 0) ? rate : 1;
    ppr_tb_log_total_result(rate, directory, exercise);
}


extern void ppr_tb_log_total_result(int rate, char* directory, char* result_file)
{
    char userid[SIZE];
    char* name;
    int name_length;

    FILE* stream;
    
    /* Pfad zum USER_PROPERTIES_FILE erstellen. Wichtig für den Aufruf aus 
     * ppr_tb_wait_and_exit bei einem Kill Signal.*/
    char user_file[255] = "";
    strcat(user_file, directory);
    strcat(user_file, USER_PROPERTIES_FILE);
    
    /*
     * Ermittle den Namen des Teilnehmers. Dieser steht in der ersten Zeile
     * der Datei "UserId.properties", nachem dem '=', bspw. 
     * TestBench.User.Name=Sample Submission
     */
    stream = fopen(user_file, "rb");
    if (stream == NULL)
    {
        fprintf(stderr, "cannot open user properties file \"%s\"\n", user_file);
        exit(EXIT_FAILURE);
    }
    
    fgets(userid, SIZE - 1, stream);
    name = strchr(userid, '=');
    name++;  /* Name beginnt hinter dem Gleichheitszeichen */
    name_length = strlen(name); /* Länge des Names */
    /* Zeilenumbruch entfernen */
    if (name[name_length - 1] == '\n') name[--name_length] = 0;
    /* Bei Linux sind es 2 Zeichen, also wird das 2.te auch entfernt */
	if (name[name_length - 1] == '\r') name[--name_length] = 0;

    fclose(stream);
    
    /*
     * Aktualisiere den Eintrag für den Teilnehmer in der Praktikums-
     * leistungendatei mit der Erfolgsquote.
     */     
     
    /* Datei zum Lesen und Ändern öffnen */
    stream = fopen(result_file, "a+");
    if (stream == NULL)
    {
        fprintf(stdout, "cannot open results \"%s\"\n", result_file);
        exit(EXIT_FAILURE);
    }

    fprintf(stream, CSV_FORMAT, name, rate);

    fclose(stream);
}

extern void ppr_tb_write_total_assert(int total_asserts) {
    
    int passed_asserts;
    int total_in_file;
    FILE* stream;
    
    errno = 0;

    stream = fopen(ASSERT_FILENAME, "r+");
    if(stream == NULL) 
    {
        if (errno == ENOENT)
        {
            stream = fopen(ASSERT_FILENAME, "w+");
            fprintf(stream, ASSERT_FORMAT, total_asserts, 0);
            rewind(stream);
        }
        if (stream == NULL) 
        {
            printf("cannot open assert log \" %s \"\n", ASSERT_FILENAME);
            exit(EXIT_FAILURE);
        }       
    } else {
    	fscanf(stream, ASSERT_FORMAT, &total_in_file, &passed_asserts);
    
        rewind(stream);
        fprintf(stream, ASSERT_FORMAT, total_asserts, passed_asserts);
    }

    fclose(stream);
}

