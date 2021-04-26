/**
 * @file
 * Dieses Modul enthaelt Testfaelle, mit denen die zu realisierenden Funktionen
 * zum Binaeren Heap getestet werden.
 *
 * @author  Ulrike Griefahn
 * @date    2016-12-01
 */


/* ============================================================================
 * Header-Dateien
 * ========================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef TESTBENCH
#include "ppr_tb_logging.h"
#endif


/* ===========================================================================
 * Prototypen der Aufgabenstellung
 * ======================================================================== */

extern void heap_init(int (*cmp)(void *, void *), void (*print)(void *));
extern void heap_destroy(void);
extern void heap_insert(void *element);
extern bool heap_extract_min(void **min_element);
extern void heap_print(void);


/* ============================================================================
 * Funktionsprototypen (Tests)
 * ========================================================================= */

/**
 * Wird aufgerufen, falls das erwartete mit dem gelieferten Ergebnis
 * uebereinstimmt.
 */
void ppr_tb_print_ok(void);

/**
 * Vergleicht die Elemente, die als String uebergeben werden, auf
 * Gleichheit. Falls sich die Elemente unterscheiden, erfolgt eine
 * entsprechende Ausgabe auf dem Bildschirm.
 *
 * @param result - IST-Zeichenkette
 * @param target - SOLL-Zeichenkette
 */
static void ppr_tb_assert_equal(char *expected, char *result);

/**
 * Gibt die uebergebene Zeichenkette auf dem Bildschirm aus.
 *
 * @param string - auszugebende Zeichenkette
 */
static void ppr_tb_print_letters(char string[]);


/* ============================================================================
 * Testbench - Funktionsdefinitionen (CUnit Test Suite)
 * ========================================================================= */

/* ----------------------------------------------------------------------------
 * Funktion: ppr_tb_print_ok
 * ------------------------------------------------------------------------- */
void ppr_tb_print_ok(void)
{   
    printf("[OK]\n\n");
    fflush(stdout);
              
#ifdef TESTBENCH
    ppr_tb_log_assert();
#endif
}

/* ----------------------------------------------------------------------------
 * Funktion: ppr_tb_assert_equal
 * ------------------------------------------------------------------------- */
static void ppr_tb_assert_equal(char *expected, char *result)
{
    if (strcmp(expected, result) == 0)
    {
        ppr_tb_print_ok();
    }
    else
    {
        printf("[ERROR]\n - Aufruf von heap_extract_min()\n");
        printf("\n");
        printf("    expected:<[\n");
        ppr_tb_print_letters(expected);
        printf("\n    ]> but was:<[\n");
        ppr_tb_print_letters(result);
        printf("\n    ]>\n\n");


        fflush(stdout);
    }
}

/* ----------------------------------------------------------------------------
 * Funktion: ppr_tb_print_letters
 * ------------------------------------------------------------------------- */
static void ppr_tb_print_letters(char *string)
{
    int index = 0;

    while (index < (int) strlen(string))
    {
        printf("%c ", string[index]);
        index += 1;
    }
    printf("\n");
    fflush(stdout);
}

/**
 * liefert das uebergebene Zeichen als String
 * @param c
 * @return 
 */
void tb_print_char(char *c) 
{
    printf("%c", *c);
}

/**
 * liefert das uebergebene Zeichen als String
 * @param c
 * @return 
 */
int tb_chrcmp(char *c1, char * c2) 
{
    return (*c1 == *c2) ? 0 : (*c1 > *c2) ? 1 : -1;
}

/* ---------------------------------------------------------------------------
 * Funktion: test_binary_heap_1
 * ------------------------------------------------------------------------- */
void ppr_tb_test_binary_heap_1()
{
    printf("========================================================"
           "\n1. Testfall: mit 5 Zeichen (\"abcde\"), print_heap und "
           "extract von 1 Zeichen \n");
    fflush(stdout);
    {
        int index;

        char *insert_elements = "abcde";
        char *target_elements = "a";
        char result_elements[100];

        char *letter; 

        /* Heap initialisieren */
        heap_init((int (*)(void *, void *)) tb_chrcmp, 
                  (void (*)(void *)) tb_print_char);

        /* Elemente einfügen */
        for (index = 0; index < (int) strlen(insert_elements); index++)
        {
            heap_insert(insert_elements + index);
        }

        /* Heap am Bildschirm ausgeben */
        heap_print();

        /* extract von 1 Zeichen ('a' wird extrahiert) */
        heap_extract_min((void **) &letter);

        /* Heap am Bildschirm ausgeben */
        heap_print();

        result_elements[0] = *letter;
        result_elements[1] = '\0';

        ppr_tb_assert_equal(result_elements, target_elements);        

        /* Heap freigeben */
        heap_destroy();
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: test_binary_heap_2 
 * ------------------------------------------------------------------------- */
void ppr_tb_test_binary_heap_2()
{
    printf("========================================================"
           "\n2. Testfall: mit 10 Zeichen (abcdgijnhp) und vollstaendigem Extrakt\n");
    fflush(stdout);
    {
        int index;
        char *letter = NULL;

        char *insert_elements = "abcdgijnhp";
        char *target_elements = "abcdghijnp";
        char result_elements[100];

        /* Heap initialisieren */
        heap_init((int (*)(void *, void *)) tb_chrcmp, 
                  (void (*)(void *)) tb_print_char);

        /* Elemente einfügen */
 
        for (index = 0; index < (int) strlen(insert_elements); index++)
        {
            heap_insert(&insert_elements[index]);
        }
        
        /* Elemente der Größe nach aus dem Heap extrahieren */
        index = 0;

        while (heap_extract_min((void **) &letter))
        {
            result_elements[index] = *letter;
            index += 1;
        }
        result_elements[index] = '\0';

        ppr_tb_assert_equal(result_elements, target_elements);

        /* Heap freigeben */
        heap_destroy();
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: test_binary_heap_3 
 * ------------------------------------------------------------------------- */
void ppr_tb_test_binary_heap_3()
{
    printf("========================================================"
           "\n3. Testfall: mit 10 Zeichen aus Testfall 1, jedoch in\n"
           "             umgekehrter Reihenfolge und vollstaendigem Extrakt\n");
    fflush(stdout);
    {
        int index;
        char *letter = NULL;

        char *insert_elements = "phnjigdcba";
        char *target_elements = "abcdghijnp";
        char result_elements[100];

        /* Heap initialisieren */
        heap_init((int (*)(void *, void *)) tb_chrcmp, 
                  (void (*)(void *)) tb_print_char);

        /* Elemente einfügen */
        for (index = 0; index < (int) strlen(insert_elements); index++)
        {
            heap_insert(&insert_elements[index]);
        }

        /* Elemente der Größe nach aus dem Heap extrahieren */
        index = 0;
        while (heap_extract_min((void **) &letter))
        {
            result_elements[index] = *letter;
            index += 1;
        }
        result_elements[index] = '\0';

        ppr_tb_assert_equal(result_elements, target_elements);

        /* Heap freigeben */
        heap_destroy();
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: test_binary_heap_4 
 * ------------------------------------------------------------------------- */
void ppr_tb_test_binary_heap_4()
{
    printf("========================================================"
           "\n4. Testfall: mit 43 Zeichen "
           "\"Donaudampfschifffahrtsgesellschaftskapitaen\"\n"
           "             und vollstaendigem Extrakt\n");
    fflush(stdout);
    {
        int index;
        char *letter = NULL;

        char *insert_elements = "Donaudampfschifffahrtsgesellschaftskapitaen";
        char *target_elements = "Daaaaaaccdeeefffffghhhiikllmnnopprssssstttu";
        char result_elements[100];

        /* Heap initialisieren */
        heap_init((int (*)(void *, void *)) tb_chrcmp, 
                  (void (*)(void *)) tb_print_char);

        /* Elemente einfügen */
        for (index = 0; index < (int) strlen(insert_elements); index++)
        {
            heap_insert(&insert_elements[index]);
        }

        /* Elemente der Größe nach aus dem Heap extrahieren */
        index = 0;
        while (heap_extract_min((void **) &letter))
        {
            result_elements[index] = *letter;
            index += 1;
        }
        result_elements[index] = '\0';

        ppr_tb_assert_equal(result_elements, target_elements);

        /* Heap freigeben */
        heap_destroy();
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: test_binary_heap_5 
 * ------------------------------------------------------------------------- */
void ppr_tb_test_binary_heap_5()
{
    printf("========================================================"
           "\n5. Testfall: mit 4 Ziffern als Zeichen \"2134\" und "
           "vollstaendigem Extrakt \n");
    fflush(stdout);
    {
        int index;
        char *letter = NULL;

        char *insert_elements = "2134";
        char *target_elements = "1234";
        char result[100];

        /* Heap initialisieren */
        heap_init((int (*)(void *, void *)) tb_chrcmp, 
                  (void (*)(void *)) tb_print_char);

        /* Elemente einfügen */
        for (index = 0; index < (int) strlen(insert_elements); index++)
        {
            heap_insert(&insert_elements[index]);
        }

        /* Elemente der Größe nach aus dem Heap extrahieren */
        index = 0;
        while (heap_extract_min((void **) &letter))
        {
            result[index] = *letter;
            index += 1;
        }
        result[index] = '\0';

        ppr_tb_assert_equal(result, target_elements);
        /* Heap freigeben */
        heap_destroy();
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: test_binary_heap_6 
 * ------------------------------------------------------------------------- */
void ppr_tb_test_binary_heap_6()
{
    printf("========================================================"
           "\n6. Testfall: mit 1 Zeichen (\"a\") und vollstaendigem Extrakt\n");
    fflush(stdout);
    {
        int index;
        char *letter = NULL;

        char *insert_elements = "a";
        char *target_elements = "a";
        char result_elements[100];

        /* Heap initialisieren */
        heap_init((int (*)(void *, void *)) tb_chrcmp, 
                  (void (*)(void *)) tb_print_char);

        /* Elemente einfügen */
        for (index = 0; index < (int) strlen(insert_elements); index++)
        {
            heap_insert(&insert_elements[index]);
        }

        /* Elemente der Größe nach aus dem Heap extrahieren */
        index = 0;
        while (heap_extract_min((void **) &letter))
        {
            result_elements[index] = *letter;
            index += 1;
        }
        result_elements[index] = '\0';

        ppr_tb_assert_equal(result_elements, target_elements);

        /* Heap freigeben */
        heap_destroy();
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: test_binary_heap_7 
 * ------------------------------------------------------------------------- */
void ppr_tb_test_binary_heap_7()
{
    printf("========================================================"
           "\n7. Testfall: erneutes Einfuegen nach vollstaendigem Extract\n"
           "             danach erneuter vollstaendiger Extract\n");
    fflush(stdout);
    {
        int index;
        char *letter = NULL;

        char *insert_elements = "fedcba";
        char *target_elements = "abcdef";
        char result_elements[100];

        /* Heap initialisieren */
        heap_init((int (*)(void *, void *)) tb_chrcmp, 
                  (void (*)(void *)) tb_print_char);

        /* Elemente einfügen */
        for (index = 0; index < (int) strlen(insert_elements); index++)
        {
            heap_insert(&insert_elements[index]);
        }

        /* alle Elemente aus dem Heap extrahieren */
        while (heap_extract_min((void **) &letter));

        /* Elemente ohne init erneut einfügen */
        for (index = 0; index < (int) strlen(insert_elements); index++)
        {
            heap_insert(&insert_elements[index]);
        }

        /* Elemente erneut der Größe nach aus dem Heap extrahieren */
        index = 0;
        while (heap_extract_min((void **) &letter))
        {
            result_elements[index] = *letter;
            index += 1;
        }
        result_elements[index] = '\0';

        ppr_tb_assert_equal(result_elements, target_elements);

        /* Heap freigeben */
        heap_destroy();
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: test_binary_heap_8 
 * ------------------------------------------------------------------------- */
void ppr_tb_test_binary_heap_8()
{
    printf("========================================================"
           "\n8. Testfall: Versuch ein Element aus leerem Heap zu extrahieren \n");
    fflush(stdout);
    {
        int index;
        char *letter = NULL;

        char *insert_elements = "";
        char *target_elements = "";
        char result_elements[100];

        /* Heap initialisieren */
        heap_init((int (*)(void *, void *)) tb_chrcmp, 
                  (void (*)(void *)) tb_print_char);

        /* Elemente einfügen */
        for (index = 0; index < (int) strlen(insert_elements); index++)
        {
            heap_insert(&insert_elements[index]);
        }

        /* Elemente der Größe nach aus dem Heap extrahieren */
        index = 0;
        while (heap_extract_min((void **) &letter))
        {
            result_elements[index] = *letter;
            index += 1;
        }
        result_elements[index] = '\0';

        ppr_tb_assert_equal(result_elements, target_elements);

        /* Heap freigeben */
        heap_destroy();
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: test_binary_heap 
 * ------------------------------------------------------------------------- */
void ppr_tb_test_binary_heap()
{
    ppr_tb_test_binary_heap_1();
    ppr_tb_test_binary_heap_2();
    ppr_tb_test_binary_heap_3();
    ppr_tb_test_binary_heap_4();
    ppr_tb_test_binary_heap_5();
    ppr_tb_test_binary_heap_6();
    ppr_tb_test_binary_heap_7();
    ppr_tb_test_binary_heap_8();
}


/* ----------------------------------------------------------------------------
 * Funktion: main
 * ------------------------------------------------------------------------- */
#ifndef TESTBENCH
int main(void)
{
    printf("%%SUITE_STARTING%% binary_heap_testsuite\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  test_binary_heap (binary_heap_testsuite)\n");
    ppr_tb_test_binary_heap();
    printf("%%TEST_FINISHED%% time=0 test_binary_heap (binary_heap_testsuite)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
#endif

#ifdef TESTBENCH
int main(int argc, char **argv)
{   
    ppr_tb_write_total_assert(8);
    ppr_tb_test_binary_heap();
    ppr_tb_write_summary("", argv[1]);
    
    return (EXIT_SUCCESS);
}
#endif
