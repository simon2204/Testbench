/**
 * @file Binärbaum
 *
 * Dieses Modul testet die Datenstrukturen und Funktionen des Binärbaums mit
 * der Struktur frequency 
 *
 * @author Ulrike Griefahn
 * @date 2019-09-09
 */
 

/* ===========================================================================
 * Header-Dateien einbinden
 * ======================================================================== */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "frequency.h"
#include "btree.h"


/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/**
 * Testet Funktionen der Module btree und btreenode mit Daten auf Basis des 
 * Moduls frequency. Die Testergebnisse werden auf dem Bildschirm ausgegeben.
 */
int main(void)
{
    /* Erzeuge die Frequency-Daten für die Knoten */
    struct FREQUENCY *frequency1    = frequency_create("1",    1);
    struct FREQUENCY *frequency10   = frequency_create("10",   2);
    struct FREQUENCY *frequency11   = frequency_create("11",   3);
    struct FREQUENCY *frequency100  = frequency_create("100",  4);
    struct FREQUENCY *frequency110  = frequency_create("110",  5);
    struct FREQUENCY *frequency111  = frequency_create("111",  6);
    struct FREQUENCY *frequency1100 = frequency_create("1100", 7);
    struct FREQUENCY *frequency1101 = frequency_create("1101", 8);
    struct FREQUENCY *frequency1110 = frequency_create("1110", 9);

    /* Erzeuge Knoten mit den Daten */
    BTREE_NODE *node100  = btreenode_new(frequency100);
    BTREE_NODE *node110  = btreenode_new(frequency110);
    BTREE_NODE *node111  = btreenode_new(frequency111);
    BTREE_NODE *node1100 = btreenode_new(frequency1100);
    BTREE_NODE *node1101 = btreenode_new(frequency1101);
    BTREE_NODE *node1110 = btreenode_new(frequency1110);

    BTREE *tree1;
    BTREE *tree2;
    BTREE *tree;
    BTREE *cloned_tree;
    BTREE_NODE *node;

    /* Erzeuge einen Baum mit den Knoten 10 und 100 */
    printf("Binaerbaum mit Knoten (10,2) und (100,4)\n\n");
    tree1 = btree_new(frequency10, 
                      (DESTROY_DATA_FCT) frequency_destroy,
                      (PRINT_DATA_FCT) frequency_print);
    node = btree_get_root(tree1);
    btreenode_set_left(node,  node100);
    btree_print(tree1);

    /* Erzeuge einen Baum mit den Knoten 11, 110, 111, 1100, 1101 und 1110 */
    printf("Binaerbaum mit Knoten (11:3), (110:5), (111:6), (1100:7), "
            "(1101:8) und (1110:9)\n\n");
    tree2 = btree_new(frequency11,
                      (DESTROY_DATA_FCT) frequency_destroy,
                      (PRINT_DATA_FCT) frequency_print);
    node = btree_get_root(tree2);
    btreenode_set_left(node, node110);
    btreenode_set_right(node, node111);
    btreenode_set_left(node110, node1100);
    btreenode_set_right(node110, node1101);
    btreenode_set_left(node111, node1110);
    btree_print(tree2);

    /* Füge die beiden Bäume zu einem zusammen mit neuer Wurzel 1 */
    printf("Zusammengefuegte Binaerbaeume mit neuer Wurzel (1:1)\n\n");
    tree = btree_merge(tree1, tree2, frequency1);
    tree1 = NULL;
    tree2 = NULL;
    btree_print(tree);

    /* Klonen des eben erzeugten Baums und Ausgabe. */
    printf("Kopie (deep clone) des resultierenden Binaerbaums\n\n");
    cloned_tree = btree_clone(tree);
    btree_print(cloned_tree);

    /* Ändere einen der Datensätze, der in beiden Bäumen vorhanden ist.*/
    printf("Aenderung der Daten des Knotens [110:5] in [test:42]\n\n");
    frequency_set_word(frequency110, "test");
    frequency_set_count(frequency110, 42);

    /* Prüfe, ob in beiden Bäumen jetzt 'test: 42' angezeigt wird. */
    printf("Ausgabe des Originalbaums und der Kopie\n\n");
    btree_print(tree);
    btree_print(cloned_tree);

    /* Speicher für beide Bäume wieder freigeben. */
    printf("Speicher des Originalsbaums und der Knoten freigeben, "
           "Daten nicht loeschen.\n\n");
    btree_destroy(&tree, false);

    /* Anzeige der nach dem Löschen des Originals noch vorhandenen Kopie. */
    printf("\nKopie anzeigen - ist noch vorhanden.\n");
    btree_print(cloned_tree);
    
    printf("\nSpeicher der Kopie, seiner Knoten und Daten freigeben.\n");
    btree_destroy(&cloned_tree, true);

    return 0;
}
