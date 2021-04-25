/* ============================================================================
 * Includes
 * ========================================================================= */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "btree.h"
#include "binary_heap.h"

#include "huffman_common.h"
#include "io.h"
#include "frequency.h"
#include "huffman.h"

#include "limits.h"


/* ===========================================================================
 * Makros
 * ======================================================================== */

/** 
 * Anzahl der möglichen Zeichen, welche in einer Datei vorkommen können. 
 */
#define MAX_CHARACTERS 256

/**
 * Die Länge der Huffman-Codes wird auf maximal 50 festgelegt
 * ToDo: Die Begrenzung auf eine bestimmte Länge aufheben 
 */
#define CODE_LENGTH 50


/* ===========================================================================
 * Funktionsprototypen
 * ======================================================================== */

/**
 * Komprimiert die Zeichen eines Eingabestroms mit den in der Code-Tabelle 
 * übergebebenen Codes und schreibt die Kompromierung bitweise in die 
 * Ausgabedatei.
 * 
 * @param code_table    Code-Tabelle, die für alle Zeichen des Eingabestroms 
 *                      einen Code für die Komprimierung enthält.
 */
static void compress_characters(char code_table[][CODE_LENGTH]);

/**
 * Dekomprimiert die Bits des Eingabestroms anhand des übergebebenen 
 * Huffman-Baums und schreibt die dekomprimierten Zeichen in den Ausgabestrom.
 * 
 * @param hufftree      Huffman-Baum für die Dekomprimierung
 * @param used_bits     Anzahl der benutzten Bits im letzten Byte
 */
static void decompress_characters(BTREE *hufftree, unsigned int used_bits);

/**
 * Vergleicht 2 Binärbäume miteinander. Dazu werden die Häufigkeiten der in 
 * der Wurzel enthaltenen CharFrequencys verglichen.
 * 
 * @param tree1 Der erste der zu vergleichenden Bäume.
 * @param tree2 Der zweite der zu vergleichenden Bäume.
 * @return      Die Funktion gibt true zurück, wenn die Häufigkeit im ersten
 *              Baum kleiner der im zweiten Baum ist, und false sonst.
 */
static int compare_trees(BTREE *tree1, BTREE *tree2);

/**
 * Zählt die Anzahl der Zeichen, die Anzahl der unterschiedlichen Zeichen und 
 * die Häufigkeiten der einzelnen Zeichen in einer Datei.
 * 
 * @param source_filename       Name der Datei, in der die Häufigkeiten
 *                              gezählt werden sollen.
 * @param frequencys            Array, in das die Häufigkeiten der Zeichen
 *                              geschrieben werden sollen.
 * @param all_characters        Anzahl aller Zeichen
 * @param different_characters  Anzahl unterschiedlicher Zeichen
 */
static void count_frequencys(char *source_filename,
                             unsigned int frequencys[],
                             unsigned int *all_characters,
                             unsigned int *different_characters);

/**
 * Erzeugt einen Huffman-Baum aus den Häufigkeiten von Zeichen.
 * 
 * @param frequencys    Ein Array mit den Häufigkeiten von Zeichen in
 *                      der zu komprimierenden Datei.
 * @return              Ein Pointer auf den erzeugten Huffman-Baum. Der Aufrufer
 *                      dieser Funktion muss sich selbst darum kümmern, dass der
 *                      Speicher für die BTree-Struktur wieder freigegeben wird.
 */
static BTREE *build_hufftree(unsigned int frequencys[]);

/**
 * Erzeugt aus einem Huffman-Baum eine Code-Tabelle, welche die 
 * Kodierungs-Vorschrift für die Komprimierung einer Datei darstellt.
 * 
 * @param hufftree      Huffman-Baum, aus dem die Code-Tabelle erzeugt
 *                      werden soll
 * @param code_table    Das 2-dimensionale Array, in welches die Codes 
 *                      (Strings) geschrieben werden.
 */
static void build_code_table(BTREE *hufftree, char code_table[][CODE_LENGTH]);

/**
 * Rekursive Erzeugung eines Code anhand des Pfads von einem Knoten im 
 * Huffman-Baum bis zu einem Blatt. Der Code wird um "0" verlängert, wenn der 
 * Pfad über den linken Teilbaum geht und mit "1" sonst. Bei Erreichen eines 
 * Blatts wird der Code in die Code-Tabelle eingetragen.
 * 
 * @param huffnode      Ein Knoten des Huffman-Baums, von dem ausgehend
 *                      der Code verlängert werden soll.
 * @param current_code  Der bislang erzeugte Code.
 * @param code_table    Die Tabelle mit den Binär-Codes für die
 *                      Komprimierung.
 */
static void build_code_table_rek(BTREE_NODE *huffnode, 
                                 char *current_code,
                                 char code_table[][CODE_LENGTH]);

/**
 * Schreibt die Informationen, welche zur Dekomprimierung benötigt werden, 
 * in die Ausgabedatei, die zuvor mit open_outfile geöffnet worden sein muss.
 * 
 * @param all_characters        Anzahl aller Zeichern der Eingabedatei
 * @param different_characters  Anzahl verschiedener Zeichen der Eingabedatei
 * @param frequencys            Ein Array mit den Häufigkeiten von Zeichen in
 *                              der zu komprimierenden Datei.
 */
static void write_fileheader(unsigned int all_characters,
                             unsigned int different_characters,
                             unsigned int frequencys[]);

/**
 * Liest die Informationen, welche zur Dekomprimierung benötigt werden, aus 
 * einer Datei. Die bitaccess-Struktur muss bereits initialisiert sein und
 * auf den Anfang einer geöffneten Datei zeigen.
 * 
 * @param frequencys    Ein Array mit den Häufigkeiten von Zeichen in
 *                      der zu komprimierenden Datei.
 * @param used_bits     Beschreibt, wie viele Bits im letzten Byte der
 *                      Datei noch mit gültigen Informationen gefüllt sind
 */
static void read_fileheader(unsigned int frequencys[],
                            unsigned int *used_bits);


/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: huffman_compress
 * ------------------------------------------------------------------------ */
extern void compress(char *in_filename, char *out_filename)
{
    /* Häufigkeiten der Zeichen in der Eingabedatei. */
    unsigned int frequencys[MAX_CHARACTERS];
    /* Huffman-Baum */
    BTREE *hufftree;
    /* Tabelle mit Huffman-Binärcodes zum Kodieren der Zeichen */
    char code_table[MAX_CHARACTERS][CODE_LENGTH];
    /* Größe der Eingabedatei */
    unsigned int all_characters = 0;
    /* Anzahl der unterschiedlichen Zeichen in der Eingabedatei */
    unsigned int different_characters = 0;

    count_frequencys(in_filename, frequencys, &all_characters, &different_characters);

    hufftree = build_hufftree(frequencys);

    build_code_table(hufftree, code_table);

    /* Freigeben des Baum und der enthaltenen Daten. */
    btree_destroy(&hufftree, true);

    /* Zieldatei zum bitweisen Schreiben öffnen */
    open_infile(in_filename);
    open_outfile(out_filename);

    write_fileheader(all_characters, different_characters, frequencys);
    compress_characters(code_table);

    /* Schließen der Quell- und Zieldatei */
    close_infile();
    close_outfile();
}

/* ---------------------------------------------------------------------------
 * Funktion: compress_characters
 * ------------------------------------------------------------------------ */
static void compress_characters(char code_table[][CODE_LENGTH])
{
    /* aktuell gelesenes Zeichen */
    unsigned char next_character;
    /* Zahldarstellung des aktuell gelesenen Zeichens */
    unsigned int int_code;

    unsigned short used_bits = 0;

    /* Laufvariable */
    unsigned int i;

    SPRINT("Schreibe Binaerdaten...\n");

    /* Schreibe die kodierten Daten in die Datei. */
    while (has_next_char())
    {
        next_character = (unsigned char) read_char();

        /* Schreibe den Code des gelesenen Zeichens in die Datei. */
        int_code = (unsigned int) next_character;
        for (i = 0; i < ((unsigned int) strlen(code_table[int_code])); i++)
        {
            write_bit((unsigned int) code_table[int_code][i] - '0');
            used_bits = (used_bits + 1) % 8;
        }
    }

    /* Letztes Byte mit 0-Bits auffüllen */
    /* wird von io.h übernommen
    while (used_bits < 8)
    {
        write_bit(0);
        used_bits++;
    }
     */
}

/* ---------------------------------------------------------------------------
 * Funktion: huffman_decompress
 * ------------------------------------------------------------------------ */
extern void decompress(char *in_filename, char *out_filename)
{
    /* Benutzte Bits im letzten Byte der Datei. */
    unsigned int all_characters = 0;
    /* Tabelle mit Häufigkeiten der vorhandenen Zeichen. */
    unsigned int frequencys[MAX_CHARACTERS];
    /* Der Huffman-Baum zum Entschlüsseln der Daten. */
    BTREE *hufftree;

    /* Quelldatei zum bitweisen Zugriff öffnen */
    open_infile(in_filename);

    read_fileheader(frequencys, &all_characters);

    hufftree = build_hufftree(frequencys);

    open_outfile(out_filename);
    decompress_characters(hufftree, all_characters);

    /* Freigeben des Baum und der enthaltenen Daten. */
    btree_destroy(&hufftree, true);

    close_infile();
    close_outfile();
}

/* ---------------------------------------------------------------------------
 * Funktion: decompress_characters
 * ------------------------------------------------------------------------ */
static void decompress_characters(BTREE *hufftree, unsigned int all_characters)
{
    /* Die Eingabe wird bitweise gelesen. Für jedes Bit wird im Huffmanbaum
     * von der Wurzel bis zu einem Blatt gewandert, bei einem 0-Bit jeweils in
     * den linken, bei einem 1-Bit jeweils in den rechten Teilbaum.
     * Das Zeichen des Blattes wird dann in die Ausgabedatei geschrieben.
     * Danach wird wieder bei der Wurzel begonnen. */

    /* aktueller Knoten während des Durchlaufs durch den Huffmannbaum. */
    BTREE_NODE *current_node;
    /* Daten des aktuellen Knotens */
    FREQUENCY *cf;
    /* aktuell gelesenes Bit. */
    BIT current_bit = 0;

#ifdef DEBUG

    printf("Dekomprimiere Binaerdaten...\n");
#endif

    current_node = btree_get_root(hufftree);

    /* Bitweises Lesen, solange in der Eingabe noch ein Byte oder im letzten
     * Byte noch belegte Bits vorhanden sind */

    while (all_characters > 0)
    {
        current_bit = read_bit();

        /* Die Daten des aktuellen Knotens im Binärbaum. */
        cf = (FREQUENCY *) btreenode_get_data(current_node);

        if (frequency_get_letter(cf) != NO_LETTER)
        {
            /* Das entschlüsselte Zeichen in die Datei schreiben */
            unsigned char character = (unsigned int) frequency_get_letter(cf);
            write_char((unsigned char) character);
            all_characters--;

            /* zurückkehren zur Wurzel im Baum */
            current_node = btree_get_root(hufftree);
        }

        current_node = (current_bit == 0)
                ? btreenode_get_left(current_node)
                : btreenode_get_right(current_node);
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: compare_trees
 * ------------------------------------------------------------------------ */
static int compare_trees(BTREE *tree1, BTREE *tree2)
{
    FREQUENCY *cf1 =
            (FREQUENCY *) btreenode_get_data(btree_get_root(tree1));

    FREQUENCY *cf2 =
            (FREQUENCY *) btreenode_get_data(btree_get_root(tree2));

    return (frequency_get_count(cf1) < frequency_get_count(cf2))
            ? -1
            : 1;
}

/* ---------------------------------------------------------------------------
 * Funktion: count_frequencys
 * ------------------------------------------------------------------------ */
static void count_frequencys(char *source_filename,
                             unsigned int frequencys[],
                             unsigned int *all_characters,
                             unsigned int *different_characters)
{
    /* das aktuell gelesene Zeichen. */
    unsigned char next_character;

    /* Anzahl der Zeichen in der Datei */
    (*all_characters) = 0;

    open_infile(source_filename);

    /* alle Felder in frequencys mit 0 initialisieren */
    memset(frequencys, 0, MAX_CHARACTERS * sizeof (unsigned int));

    /* Lese zeichenweise und zähle die Häufigkeiten der einzelnen Zeichen. */
    while (has_next_char())
    {
        if ((*all_characters) == UINT_MAX)
        {
            printf("Fehler: Die Datei ist zu gross zum komprimieren.\n");
            system("PAUSE");
            exit(EXIT_SUCCESS);
        }

        next_character = (unsigned char) read_char();
        frequencys[next_character]++;

        (*all_characters)++;
        if (frequencys[next_character] == 1)
        {
            (*different_characters)++;
        }
    }

    close_infile();
}

/* ---------------------------------------------------------------------------
 * Funktion: build_hufftree
 * ------------------------------------------------------------------------ */
static BTREE *build_hufftree(unsigned int frequencys[])
{
    /* Zahldarstellung des aktuellen Zeichens */
    unsigned int int_code;
    /* aktuelles Zeichen */
    unsigned char character;
    /* Daten für die Knoten des Huffman-Baums */
    FREQUENCY *new_cf;
    FREQUENCY *cf1;
    FREQUENCY *cf2;
    /* Binärbäume */
    BTREE *new_tree;
    BTREE *tree1 = NULL;
    BTREE *tree2 = NULL;
    /* Huffman-Baum */
    BTREE *hufftree = NULL;

    heap_init((HEAP_ELEM_COMP) compare_trees, (HEAP_ELEM_PRINT) btree_print);

    /* Füge alle Häufigkeiten jeweils als Wurzel eines Binärbaumes in den
     * Heap ein */
    for (int_code = 0; int_code < MAX_CHARACTERS; int_code++)
    {
        if (frequencys[int_code] > 0)
        {
            character = (unsigned char) int_code;
            new_cf = frequency_create(character, (int) frequencys[int_code]);
            new_tree = btree_new(new_cf,
                                 (DESTROY_DATA_FCT) frequency_destroy,
                                 (PRINT_DATA_FCT) frequency_print);
            heap_insert(new_tree);
        }
    }

    if (heap_get_size() == 0)
    {
        /* Heap ist leer, erzeuge leeren Baum */
        hufftree = btree_new(NULL,
                             (DESTROY_DATA_FCT) frequency_destroy,
                             (PRINT_DATA_FCT) frequency_print);
    }
    else
    {
        /* Aufbauen des Huffman-Baumes mit Hilfe des Heaps. */
        while (heap_get_size() > 1)
        {
            /* Extrahiere die beiden Binärbäume mit der kleinsten Häufigkeit */
            heap_extract_min((void **) &tree1);
            heap_extract_min((void **) &tree2);

            /* Erzeuge die neue Wurzel mit der Summe der Häufigkeiten der beiden
             * gefundenen Bäume */
            cf1 = (FREQUENCY *) btreenode_get_data(btree_get_root(tree1));
            cf2 = (FREQUENCY *) btreenode_get_data(btree_get_root(tree2));
            new_cf = frequency_create(NO_LETTER,
                                      frequency_get_count(cf1)
                                        + frequency_get_count(cf2));

            /* Verbinde die 2 alten Bäume und füge sie mit der neuen Wurzel 
             * wieder in den Heap ein. */
            new_tree = btree_merge(tree1, tree2, new_cf);
            heap_insert(new_tree);
#ifdef DEBUG
            btree_print(new_tree);
#endif
        }

        /* Der letzte im Heap verbleibene Baum ist nun der Huffman-Baum. */
        heap_extract_min((void **) &hufftree);

        /* Hat der Huffman-Baum nur einen Knoten: noch eine Wurzel einfügen */
        if (btreenode_is_leaf(btree_get_root(hufftree)) == true)
        {
            BTREE_NODE *root = btree_get_root(hufftree);
            FREQUENCY *cf1 = btreenode_get_data(root);
            FREQUENCY *cf2 = frequency_create(NO_LETTER,
                                              frequency_get_count(cf1));
            hufftree = btree_new(cf2,
                                 (DESTROY_DATA_FCT) frequency_destroy,
                                 (PRINT_DATA_FCT) frequency_print);
            btreenode_set_left(btree_get_root(hufftree), root);
        }
#ifdef DEBUG
        btree_print(hufftree);
#endif
    }
    heap_destroy();
    return hufftree;
}

/* ---------------------------------------------------------------------------
 * Funktion: build_code_table
 * ------------------------------------------------------------------------ */
static void build_code_table(BTREE *hufftree,
                             char code_table[][CODE_LENGTH])
{
    int i;

    /* Initialisiere alle Elemente der Code-Tabelle mit einem Leerstring. */
    for (i = 0; i < MAX_CHARACTERS; i++)
    {
        code_table[i][0] = '\0';
    }

    build_code_table_rek(btree_get_root(hufftree), "", code_table);

#ifdef DEBUG
    printf("Code-Tabelle:\n");
    {
        int code;
        for (code = 0; code < MAX_CHARACTERS; code++)
        {
            if (code_table[code][0] != '\0')
            {
                printf("Code fuer %d: %s\n", code, code_table[code]);
            }
        }
    }
#endif
}

/* ---------------------------------------------------------------------------
 * Funktion: build_code_table_rek
 * ------------------------------------------------------------------------ */
static void build_code_table_rek(BTREE_NODE *huffnode,
                                 char *current_code,
                                 char code_table[][CODE_LENGTH])
{
    /* Linker oder rechter Kindknoten des aktuellen Knotens */
    BTREE_NODE *child_node;
    /* Codes für Verlängerung im linken und rechten Teilbaum */
    char left_code[CODE_LENGTH];
    char right_code[CODE_LENGTH];

    FREQUENCY *cf = (FREQUENCY*) btreenode_get_data(huffnode);
    if (frequency_get_letter(cf) != NO_LETTER)
    {
        /* Ein Zeichen wurde gefunden. Der Code muss nun zugeordnet werden. */
        int code = frequency_get_letter(cf);
        strcpy(code_table[code], current_code);
    }

    /* Falls vorhanden, Code für das linke Kind verlängern */
    child_node = btreenode_get_left(huffnode);
    if (child_node != NULL)
    {
        /* Anhängen des linken Bits (0) an den Code */
        strcpy(left_code, current_code);
        strcat(left_code, "0");
        build_code_table_rek(child_node, left_code, code_table);
    }

    /* Falls vorhanden, Code für das rechte Kind verlängern */
    child_node = btreenode_get_right(huffnode);
    if (child_node != NULL)
    {
        /* Anhängen des linken Bits (0) an den Code */
        strcpy(right_code, current_code);
        strcat(right_code, "1");
        build_code_table_rek(child_node, right_code, code_table);
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: write_fileheader
 * ------------------------------------------------------------------------ */
static void write_fileheader(unsigned int all_characters,
                             unsigned int different_characters,
                             unsigned int frequencys[])
{
    int i;

#ifdef DEBUG
    printf("Schreibe Header...\n");
    printf("- Anzahl kodierter Zeichen : %d\n", different_characters);
    printf("- Anzahl aller Zeichern    : %u\n", all_characters);
#endif

    /* Schreibe Anzahl Zeichen und Anzahl unterschiedlicher Zeichen 
     * in der Eingabedatei */
    write_int((unsigned int) all_characters);
    write_int((unsigned int) different_characters);

    /* Schreibe Zeichen und Häufigkeit */
    for (i = 0; i < MAX_CHARACTERS; i++)
    {
        if (frequencys[i] != 0)
        {
            write_char((unsigned char) i);
            write_int((unsigned int) frequencys[i]);
        }
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: read_fileheader
 * ------------------------------------------------------------------------ */
static void read_fileheader(unsigned int frequencys[],
                            unsigned int *all_characters)
{
    /* Anzahl der kodierten Zeichen */
    unsigned int different_characters = 0;
    /* Das aktuell gelesene Zeichen. */
    unsigned char current_character = 0;
    /* Die Häufigkeit des aktuell gelesenen Zeichens */
    unsigned int current_frequency = 0;

    /* Laufvariable. */
    unsigned int i;

    /* Lese Anzahl kodierter Zeichen lesen */
    *all_characters = (unsigned int) read_int();
    different_characters = (unsigned int) read_int();

    /* Initialisiere die Häufigkeiten-Tabelle mit 0 */
    memset(frequencys, 0, MAX_CHARACTERS * sizeof (unsigned int));

    /* Setze für jedes Zeichen die eingelesene Häufigkeit */
    for (i = 0; i < different_characters; i++)
    {
        current_character = (unsigned char) read_char();
        current_frequency = (unsigned int) read_int();

        frequencys[current_character] = current_frequency;
    }
#ifdef DEBUG
    printf("Header der komprimierten Datei:\n");
    printf("- Anzahl kodierter Zeichen : %d\n", different_characters);
    printf("- Anzahl aller Zeichen     : %u\n", *all_characters);
    printf("- Haeufigkeiten der Zeichen: \n");
    {
        int code;
        for (code = 0; code < MAX_CHARACTERS; code++)
        {
            if (frequencys[code] != 0)
            {
                printf("  - '%d' : %d\n", code, frequencys[code]);
            }
        }
    }
#endif
}