/* ===========================================================================
 * Header-Dateien 
 * ======================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "binary_heap.h"


/* ===========================================================================
 * Makro-Definitionen
 * ======================================================================== */

/**
 * Anzahl an Elementen, für die bei einer Speicherallokation neuer 
 * Speicherplatz reserviert bzw. freigegeben wird. 
 */
#define ALLOC_STEP 5

/**
 * Berechnet die Position des Elternknotens zu einem Kindknoten 
 */
#define PARENT_POSITION(POSITION) (((POSITION) - 1) / 2)

/**
 * Berechnet die Position des linken Kindknotens zu einem Elternknoten 
 */
#define LEFT_CHILD_POSITION(POSITION) (((POSITION) * 2) + 1)

/**
 * Berechnet die Position des rechten Kindknotens zu einem Elternknoten 
 */
#define RIGHT_CHILD_POSITION(POSITION) (((POSITION) * 2) + 2)

/**
 * Makro zur Pr�fung, ob die Speicherallokation erfolgreich war 
 */
#define ENSURE_ENOUGH_MEMORY(VAR, FUNCTION) \
{if (VAR == NULL) { printf(FUNCTION ": not enough memory\n"); \
                    exit(EXIT_FAILURE); }}


/* ===========================================================================
 * Globale Variablen
 * ======================================================================== */

/**
 * Größe des für den Heap allokierten Speichers. Der Speicher wird immer in
 * der durch #ALLOC_STEP vorgegebene Schrittweite erhöht 
 */
static int heap_memory_size = 0;

/**
 * Größe des Heaps, d.h. die Anzahl der aktuelle enthaltenen Elemente 
 */
static int heap_size = 0;

/**
 * Die Heap-Elemente werden in einem dynamischen Array verwaltet. 
 */
static void **heap_array;

/** Vergleichsfunktion, mit denen die Heap-Elemente verglichen werden */
static HEAP_ELEM_COMP heap_compare_data;

/** Funktion für die textuelle Ausgabe der Heap-Elemente */
static HEAP_ELEM_PRINT heap_print_data;


/* ===========================================================================
 * Funktionsprototypen
 * ======================================================================== */

/**
 * Stellt sicher, dass im Heap noch gen�gend Platz für ein weiteres Element 
 * ist. Ist der Heap voll, wird in der Schrittweite #ALLOC_STEP weiterer 
 * Speicherplatz allokiert.
 *
 * Ändert die globalen Variablen: heap_array, heap_memory_size. 
 * Programmabbruch, wenn kein Speicher allokiert werden kann.
 */
static void heap_ensure_enlarge(void);

/**
 * Stellt sicher, dass für den Heap nicht zu viel Platz allokiert ist. Ist im 
 * Heap noch Platz für ALLOC_STEP weitere Elemente, wird der Speicher in der 
 * Schrittweite ALLOC_STEP freigegeben.
 * 
 * �ndert die globalen Variablen: heap_array, heap_memory_size
 * Programmabbruch, wenn kein Speicher allokiert werden kann.
 */
static void heap_ensure_reduce(void);

/**
 * Vertauscht zwei Elemente des Heaps
 * 
 * Es wird davon ausgegangen, dass position1 und position2 gültige Positionen 
 * im Heap sind.
 * 
 * @param position1 - Position des ersten Elements
 * @param position2 - Position des zweiten Elements
 */
static void swap(int position1, int position2);

/**
 * Stellt nach dem Einfügen eines neuen Elements ans Ende des Heaps die 
 * Heap-Eigenschaft wieder her. Das Element an position wird solange auf dem 
 * Pfad zur Wurzel mit seinen Vaterknoten getauscht, bis ein Vaterknoten kleiner
 * ist als das eingefügte Element.
 * 
 * Es wird davon ausgegangen, dass position eine gültige Position im Heap ist.
 * 
 * @param position Position des eingefügten Elements
 */
static void heapify_up(int position);

/**
 * Stellt die Heap-Eigenschaft nach Extrahieren eines Elements wieder her. Das
 * Element an position wird mit dem kleineren der beiden Kindknoten solange 
 * getauscht, bis beide Kindknoten kleiner sind als das Element.
 *
 * Es wird davon ausgegangen, dass position eine gültige Position im Heap ist.
 *
 * @param position - Position im Heap, ab der die Heap-Eigenschaft wieder
 *              hergestellt werden soll. 
 */
static void heapify_down(int position);

/**
 * Gibt das Heap-Element an der Position position am Bildschirm aus. Die 
 * Ausgabe wird um indent Leerzeichen eingerückt. 
 * 
 * @param position Position im Heap, aber der ausgegeben werden soll
 * @param indent   Anzahl der Leerzeichen, die die Ausgabe eingerückt
 *                 werden soll.
 */
static void heap_print_rek(int position, int indent);


/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: heap_init
 * ------------------------------------------------------------------------ */
extern void heap_init(HEAP_ELEM_COMP compare_fct, HEAP_ELEM_PRINT print_fct)
{
    /* ggf. existierenden Heap l�schen */
    if (heap_array != NULL)
    {
        heap_destroy();
    }
    
    /* Speicher wird immer in der Schrittweite ALLOC_STEP angefordert, damit
     * nicht für jedes einzelne Element Speicher angefordert werden muss */

    heap_array = (void **) malloc(ALLOC_STEP * sizeof (void *));
    ENSURE_ENOUGH_MEMORY(heap_array, "heap_init");

    heap_memory_size = ALLOC_STEP;
    heap_size = 0;
    heap_compare_data = compare_fct;  
    heap_print_data = print_fct;    
}

/* ---------------------------------------------------------------------------
 * Funktion: heap_destroy
 * ------------------------------------------------------------------------ */
extern void heap_destroy(void)
{
    free(heap_array);
    heap_array = NULL;

    heap_memory_size = 0;
    heap_size = 0;
}


/* ---------------------------------------------------------------------------
 * Funktion: heap_get_size
 * ------------------------------------------------------------------------ */
extern int heap_get_size(void)
{
    return heap_size;
}

/* ---------------------------------------------------------------------------
 * Funktion: heap_ensure_enlarge
 * ------------------------------------------------------------------------ */
static void heap_ensure_enlarge(void)
{
    if (heap_size == heap_memory_size)
    {
        /* Heap voll -> weiteren Speicher reservieren */
        heap_array = (void **) realloc(
                heap_array, (heap_memory_size + ALLOC_STEP) * sizeof (void *));
        ENSURE_ENOUGH_MEMORY(heap_array, "heap_ensure_enlarge");

        heap_memory_size += ALLOC_STEP;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: heap_ensure_reduce
 * ------------------------------------------------------------------------ */
static void heap_ensure_reduce(void)
{
    if (heap_size < heap_memory_size - ALLOC_STEP)
    {
        /* Heap zu groß -> Speicher freigeben */
        heap_array = (void **) realloc(
                heap_array, (heap_memory_size - ALLOC_STEP) * sizeof (void *));
        ENSURE_ENOUGH_MEMORY(heap_array, "heap_ensure_reduce");

        heap_memory_size -= ALLOC_STEP;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: swap
 * ------------------------------------------------------------------------ */
static void swap(int position1, int position2)
{
    void *temp;

    temp = heap_array[position1];
    heap_array[position1] = heap_array[position2];
    heap_array[position2] = temp;
}

/* ---------------------------------------------------------------------------
 * Funktion: heapify_up
 * ------------------------------------------------------------------------ */
static void heapify_up(int position)
{
    int parent_pos;
    
    while (position > 0)
    {
        parent_pos = PARENT_POSITION(position);
        if (heap_compare_data(heap_array[position], 
                              heap_array[parent_pos]) == -1)
        {
            swap(position, parent_pos);
        }
        position = parent_pos;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: heapify_down
 * ------------------------------------------------------------------------ */
static void heapify_down(int parent_pos)
{
    /* Positionen der Kindknoten des Knotens an parent_pos */
    int left_child_pos = LEFT_CHILD_POSITION(parent_pos);
    int right_child_pos = RIGHT_CHILD_POSITION(parent_pos);

    /* Suche unter den Kindknoten und dem Elternknoten den mit dem
     * kleinsten Wert. */
    int min_pos = parent_pos;
    
    if ((left_child_pos < heap_size)
        && (heap_compare_data(heap_array[left_child_pos], 
                              heap_array[parent_pos]) == -1))
    {
        min_pos = left_child_pos;
    }
    if ((right_child_pos < heap_size)
        && (heap_compare_data(heap_array[right_child_pos], 
                              heap_array[min_pos]) == -1))
    {
        min_pos = right_child_pos;
    }

    /* Ist einer der Kindknoten der Knoten mit dem keinsten Wert, wird dieser
     * mit dem Elternknoten getauscht und die Heap-Eigenschaft im Baum ab
     * dem Kindknoten wieder hergestellt. */
    if (min_pos != parent_pos)
    {
        swap(parent_pos, min_pos);
        heapify_down(min_pos);
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: heap_insert
 * ------------------------------------------------------------------------ */
extern void heap_insert(void *element)
{
    /* Sicherstellen, dass genügend Speicherplatz vorhanden ist */
    heap_ensure_enlarge();

    /* Neues Element hinten anfügen */
    heap_array[heap_size] = element;
    heap_size += 1;

    /* Heap-Eigenschaft ab dem letzten Element wieder herstellen */
    heapify_up(heap_size - 1);
}

/* ---------------------------------------------------------------------------
 * Funktion: heap_extract_min
 * ------------------------------------------------------------------------ */
extern bool heap_extract_min(void **min_element)
{
    if (heap_size == 0)
    {
        return false;
    }
     
    /* Das erste Element des Heap ist immer das kleinste */
    *min_element = heap_array[0];

    /* Element aus dem Heap löschen */
    heap_array[0] = heap_array[heap_size - 1];
    heap_size -= 1;

    /* Heap-Eigenschaft ab der Wurzel wieder herstellen */
    heapify_down(0);

    /* ggf. Speicher freigeben */
    heap_ensure_reduce();

    return true;
}

/* ---------------------------------------------------------------------------
 * Funktion: heap_print
 * ------------------------------------------------------------------------ */
extern void heap_print(void)
{
    printf("Heap: (%d Elemente)\n", heap_size);
    if (heap_size > 0)
    {
        heap_print_rek(0, 0);
        printf("\n");
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: heap_print_rek
 * ------------------------------------------------------------------------ */
static void heap_print_rek(int position, int indent)
{
    int i;
    for (i = 0; i < indent; i++)
    {
        printf("    ");
    }

    printf("|-- ");
    heap_print_data(heap_array[position]);
    printf("\n");
    
    if (LEFT_CHILD_POSITION(position) < heap_size)
    {
        heap_print_rek(LEFT_CHILD_POSITION(position), indent + 1);
    }
    if (RIGHT_CHILD_POSITION(position) < heap_size)
    {
        heap_print_rek(RIGHT_CHILD_POSITION(position), indent + 1);
    }
}
