/** 
 * @file:   main.c
 * @author: UG
 *
 * Ruft die Funktionen des binären Heaps auf.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "binary_heap.h"

/**
 * Vergleicht die übergebenen Zeichen c1 und c2.
 * @param c1
 * @param c2
 * @return liefert 0, wenn beide Zeichen gleich sind; 1, wenn c1 größer ist 
 *         als c2; -1, wenn c1 kleiner ist als c2.
 */
static int chrcmp(char *c1, char * c2) 
{
    return (*c1 == *c2) 
            ? 0 
            : (*c1 > *c2) ? 1 : -1;
}

/**
 * Gibt das uebergebene Zeichen als String am Bildschirm aus
 * 
 * @param c
 */
static void print_char(char *c) 
{
    printf("%c", *c);
}

/**
 * Testet die Funktionen des binären Heaps
 * 
 * @return immer EXIT_SUCCESS
 */
int main(void)
{
    bool passed;
    int i;
    char *letter = NULL;

    char *elements = "phnjabcgdi";
    char *expected = "abcdghijnp";
    char result[100];

    /* Heap initialisieren */
    heap_init((HEAP_ELEM_COMP) chrcmp, (HEAP_ELEM_PRINT) print_char);

    /* Elemente in Heap einfügen */
    for (i = 0; i < (int) strlen(elements); i++)
    {
        heap_insert(&elements[i]);
    }
    
    /* Elemente der Größe nach aus dem Heap extrahieren */
    i = 0;
    while (heap_extract_min((void **) &letter))
    {
        result[i] = *letter;
        i++;
    }
    result[i] = '\0';

    /* Heap freigeben */
    heap_destroy();

    /* Ergebnis und erwartetes Ergebnis vergleichen */
    passed = strcmp(result, expected) == 0;
    printf("Test %s\n", (passed) ? "passed" : "failed");
    printf("%s\n", result);
    printf("%s\n", expected);
    
    return (EXIT_SUCCESS);
}
