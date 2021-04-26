/**
 * @file
 * Dieses Modul enthaelt Testfaelle, mit denen die zu realisierenden Funktionen
 * zum Binaerbaum getestet werden.
 *
 * @author  Ulrike Griefahn
 * @date    2014-02-03
 */

/* ============================================================================
 * Header-Dateien
 * ========================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "data.h"

#ifdef TESTBENCH
#include "ppr_tb_logging.h"
#endif


/* ============================================================================
 * Vorgaben der Aufgabenstellung
 * ========================================================================= */

typedef void (*BTREENODE_PRINT_DATA)(void *);
typedef void (*BTREENODE_DESTROY_DATA)(void **);

typedef struct _BTREE_NODE BTREE_NODE;
typedef struct _BTREE BTREE;

extern BTREE *btree_new(void *data,
                        BTREENODE_DESTROY_DATA destroy_data, 
                        BTREENODE_PRINT_DATA print_data);
extern BTREE *btree_clone(BTREE *tree);
extern void btree_destroy(BTREE **tree, bool destroy_data);
extern bool btree_equals(BTREE *tree1, BTREE *tree2);
extern BTREE_NODE *btree_get_root(BTREE *tree);
extern BTREE *btree_merge(BTREE *left, BTREE *right, void *data);
extern void btree_print(BTREE *tree);

extern BTREE_NODE *btreenode_new(void *data);
extern BTREE_NODE *btreenode_clone(BTREE_NODE *node);
extern bool btreenode_equals(BTREE_NODE *node1, BTREE_NODE *node2);
extern void btreenode_destroy(BTREE_NODE **node, 
                              BTREENODE_DESTROY_DATA destroy_data);
extern void *btreenode_get_data(BTREE_NODE *node);
extern BTREE_NODE *btreenode_get_left(BTREE_NODE *node);
extern BTREE_NODE *btreenode_get_right(BTREE_NODE *node);
extern bool btreenode_is_leaf(BTREE_NODE *node);
extern bool btreenode_set_left(BTREE_NODE *parent_node, BTREE_NODE *node);
extern bool btreenode_set_right(BTREE_NODE *parent_node, BTREE_NODE *node);
extern void btreenode_print(BTREE_NODE *node, BTREENODE_PRINT_DATA print_data);


extern struct FREQUENCY *frequency_create(const char *word, const int count);
extern void frequency_destroy(struct FREQUENCY **pp_frequency);
extern char *frequency_get_word(const struct FREQUENCY *p_frequency);
extern int frequency_get_count(const struct FREQUENCY *p_frequency);
extern void frequency_set_word(struct FREQUENCY *p_frequency, 
                               const char *word);
extern void frequency_set_count(struct FREQUENCY *p_frequency, 
                                const int count);
extern int frequency_compare(const struct FREQUENCY *p_frequency1, 
                             const struct FREQUENCY *p_frequency2);
extern char *frequency_get_string(const struct FREQUENCY *p_frequency);
extern void frequency_print(const struct FREQUENCY *p_frequency);


/* ============================================================================
 * Funktionsprototypen (Tests)
 * ========================================================================= */

void ppr_ppr_tb_print_ok(void);
void ppr_tb_test_btree();


/* ============================================================================
 * Funktionsdefinitionen
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

/* ---------------------------------------------------------------------------
 * Funktion: ppr_tb_test_binaerbaum 
 * ------------------------------------------------------------------------- */
void ppr_tb_test_btree()
{
    /* Erzeuge die Frequency-Daten fuer die Knoten */
    struct FREQUENCY *frequency0001 = frequency_create("1", 1);
    struct FREQUENCY *frequency0010 = frequency_create("10", 2);
    struct FREQUENCY *frequency0011 = frequency_create("11", 3);
    struct FREQUENCY *frequency0100 = frequency_create("100", 4);
    struct FREQUENCY *frequency0110 = frequency_create("110", 5);
    struct FREQUENCY *frequency0111 = frequency_create("111", 6);
    struct FREQUENCY *frequency1100 = frequency_create("1100", 7);
    struct FREQUENCY *frequency1101 = frequency_create("1101", 8);
    struct FREQUENCY *frequency1110 = frequency_create("1110", 9);
    
    /* Erzeuge Knoten mit den Daten */
    BTREE_NODE *node0100 = btreenode_new(frequency0100);
    BTREE_NODE *node0110 = btreenode_new(frequency0110);
    BTREE_NODE *node0111 = btreenode_new(frequency0111);
    BTREE_NODE *node1100 = btreenode_new(frequency1100);
    BTREE_NODE *node1101 = btreenode_new(frequency1101);
    BTREE_NODE *node1110 = btreenode_new(frequency1110);
    
    BTREE *tree1;
    BTREE *tree2;
    BTREE *tree;
    BTREE *cloned_tree;

    BTREE_NODE *root;
    
    {
        printf("-----------------------------------------------------------\n"
               "1. Testfall : Erzeuge Knoten [\"100\": 4]\n");
        if (node0100 != NULL
                && btreenode_get_data(node0100) == frequency0100
                && btreenode_get_left(node0100) == NULL
                && btreenode_get_right(node0100) == NULL)
        {
            ppr_tb_print_ok();
        }
        else
        {
            printf("\n[ERROR]\n"
                   "   Erzeugung eines neuen Knotens mit Daten vom Typ frequency\n"
                   "   expected:<[\n"
                   "    data: %p ", (void *)frequency0100);
            frequency_print(frequency0100); 
            printf(", left: 0, right: 0\n"
                   "   ]> but was:<[\n"
                   "    data: %p ",
                   btreenode_get_data(node0100));
            frequency_print(btreenode_get_data(node0100));
            printf(", left: %jx, right: %jx\n"
                   "   ]>\n\n",
                   (uintmax_t)btreenode_get_left(node0100),
                   (uintmax_t)btreenode_get_right(node0100));
        }
    }

    {
        /* Erzeuge einen Baum mit den Knoten 10 und 100 */
        printf("-----------------------------------------------------------\n"
               "2. Testfall : Zwei Binaerbaume aufbauen\n");
        
        printf("   Binaerbaum mit Wurzel (10,2) und linkem Teilbaum (100,4)\n");
        tree1 = btree_new(frequency0010,
                          (BTREENODE_DESTROY_DATA) frequency_destroy,
                          (BTREENODE_PRINT_DATA) frequency_print);
        root = btree_get_root(tree1);
        btreenode_set_left(root, node0100);

        /* Erzeuge einen Baum mit den Knoten 11, 110, 111, 1100, 1101 und 1110 */
        printf("   Binaerbaum mit Knoten (11:3),(110:5),(111:6),(1100:7),"
               "(1101:8) und (1110:9)\n");
        tree2 = btree_new(frequency0011,
                          (BTREENODE_DESTROY_DATA) frequency_destroy,
                          (BTREENODE_PRINT_DATA) frequency_print);
        root = btree_get_root(tree2);
        btreenode_set_left(root, node0110);
        btreenode_set_right(root, node0111);
        btreenode_set_left(node0110, node1100);
        btreenode_set_right(node0110, node1101);
        btreenode_set_left(node0111, node1110);
        
        if (btreenode_get_data(btree_get_root(tree1)) == frequency0010
            && btreenode_get_left(btree_get_root(tree1)) == node0100
            && btreenode_get_data(btree_get_root(tree2)) == frequency0011
            && btreenode_get_left(btree_get_root(tree2)) == node0110
            && btreenode_get_right(btree_get_root(tree2)) == node0111
            && btreenode_get_left(btreenode_get_left(btree_get_root(tree2))) == node1100
            && btreenode_get_right(btreenode_get_left(btree_get_root(tree2))) == node1101
            && btreenode_get_left(btreenode_get_right(btree_get_root(tree2))) == node1110)
        {
            ppr_tb_print_ok();
        }
        else
        {
            printf("\n[ERROR]\n"
                   "Fehler beim Zusammenbauen der Baeume\n\n");
            btree_print(tree1);
            btree_print(tree2);
            fflush(stdout);
        }
    }
    
    {
        /* Fuege die beiden Baeume zu einem zusammen mit neuer Wurzel 1 */
        printf("-----------------------------------------------------------\n"
               "3. Testfall : Zusammengefuegte Binaerbaeume mit neuer Wurzel (1:1)\n");
        tree = btree_merge(tree1, tree2, frequency0001);
        tree1 = NULL;
        tree2 = NULL;
        
        if (btreenode_get_data(btree_get_root(tree)) == frequency0001
            && btreenode_get_data(btreenode_get_left(btree_get_root(tree))) == frequency0010
            && btreenode_get_left(btreenode_get_left(btree_get_root(tree))) == node0100
            && btreenode_get_data(btreenode_get_right(btree_get_root(tree))) == frequency0011
            && btreenode_get_left(btreenode_get_right(btree_get_root(tree))) == node0110
            && btreenode_get_right(btreenode_get_right(btree_get_root(tree))) == node0111
            && btreenode_get_left(btreenode_get_left(btreenode_get_right(btree_get_root(tree)))) == node1100
            && btreenode_get_right(btreenode_get_left(btreenode_get_right(btree_get_root(tree)))) == node1101
            && btreenode_get_left(btreenode_get_right(btreenode_get_right(btree_get_root(tree)))) == node1110)
        {
            ppr_tb_print_ok();
        }
        else
        {
            printf("\n[ERROR]\n"
                   "Fehler beim Zusammenbauen der Baeume\n\n");
            btree_print(tree);
            fflush(stdout);
        }
    }
    
    {
        /* Klonen des eben erzeugten Baums und Ausgabe. */
        printf("-----------------------------------------------------------\n"
               "4. Testfall : Kopie (deep clone) des resultierenden Binaerbaums\n\n");
        cloned_tree = btree_clone(tree);

        /* Vergleiche die beiden Binaerbaeume: Sie muessen gleich sein */
        if (btree_equals(tree, cloned_tree) == true)
        {
            printf("Die beiden Baeume %jx und %jx sind gleich.\n",
                   (uintmax_t)tree, (uintmax_t)cloned_tree);
            ppr_tb_print_ok();
        }
        else
        {
            printf("\n[ERROR]\n"
                   "Die beiden Baeume %jx und %jx sind ungleich.\n\n",
                   (uintmax_t)tree, (uintmax_t)cloned_tree);
            btree_print(cloned_tree);
            fflush(stdout);
        }
    }

    {
        /* Aendere ein enthaltenes Element, das in beiden Baeumen vorhanden ist.*/
        printf("-----------------------------------------------------------\n"
        "5. Testfall : Aenderung der Daten des Knotens (110:5) in (test:42)\n\n");
        frequency_set_word(frequency0110, "test");
        frequency_set_count(frequency0110, 42);

        /* Vergleiche die beiden Binaerbaeume: Sie muessen weiterhin gleich sein */
        if (btree_equals(tree, cloned_tree) == true)
        {
            printf("Die beiden Baeume %jx und %jx sind weiterhin gleich.\n",
                   (uintmax_t)tree, (uintmax_t)cloned_tree);
            ppr_tb_print_ok();
        }
        else
        {
            printf("\n[ERROR]\n"
                   "Die beiden Baeume %jx und %jx sind jetzt ungleich.\n\n",
                   (uintmax_t)tree, (uintmax_t)cloned_tree);
            fflush(stdout);

            printf("Ausgabe des Originalbaums und der Kopie\n\n");
            btree_print(tree);
            btree_print(cloned_tree);
        }
    }
    
    {   
        printf("-----------------------------------------------------------\n"
        "6. Testfall : Speicher des Originalbaums und der Knoten freigeben, "
               "Daten nicht loeschen.\n\n");
        
        /* Speicher fuer beide Baeume wieder freigeben. */
        btree_destroy(&tree, false);
        if (tree == NULL && frequency0001 != NULL && frequency_get_word(frequency0001) != NULL)
        {
            printf("Der Originalbaum wurde zerstoert. Die Daten existieren noch.\n");
            ppr_tb_print_ok();            
        }
        else
        {
            if (tree != NULL)
            {
                printf("\n[ERROR]\n"
                       "Der Originalbaum existiert weiterhin.\n\n");
                fflush(stdout);
            }
            
            if (frequency0001 == NULL || frequency_get_word(frequency0001) == NULL)
            {
                printf("\n[ERROR]\n"
                       "Die Daten des Originalbaums wurden gelöscht.\n\n");
                fflush(stdout);
            }
            /* Anzeige der nach dem Loeschen des Originals noch vorhandenen Kopie. */
            btree_print(cloned_tree);
        }
    }
    
    {
        struct Data *data;
        struct Data *data2;
        printf("-----------------------------------------------------------\n"
               "7. Testfall : Loesche Baum - Enthaltene Daten der Knoten werden nicht geloescht\n");
        /* Kopiere die Daten um spaeter im Fehlerfall die erwarteten Daten anzuzeigen */
        data = data_new();
        data2 = data_new();
        data_set_destruction_requested(data2, false);
        
        tree1 = btree_new(data,
                          (BTREENODE_DESTROY_DATA) data_pretend_destroy,
                          (BTREENODE_PRINT_DATA) data_print);
        btree_destroy(&tree1, false);
        if (data != NULL && data_get_destruction_requested(data)
                                  == data_get_destruction_requested(data2))
        {
            ppr_tb_print_ok();
        }
        else
        {
            printf("\n[ERROR]\n"
                   "   Loeschen eines Baumes ohne Loeschen der Daten\n"
                   "   expected:<[\n"
                   "    data: ");
            data_print(data2); 
            printf("\n"
                   "   ]> but was:<[\n"
                   "    data: ");
            data_print(data);
            printf("\n   ]>\n\n");
        }
        if (data != NULL)
        {
            data_destroy(&data);
        }
        if (data2 != NULL)
        {
            data_destroy(&data2);
        }
    }
    
    {
        struct Data *data;
        struct Data *data2;
        printf("-----------------------------------------------------------\n"
               "8. Testfall : Loesche Baum - Enthaltene Daten der Knoten werden geloescht\n");
        /* Kopiere die Daten um spaeter im Fehlerfrei die erwarteten Daten anzuzeigen */
        data = data_new();
        data2 = data_new();
        data_set_destruction_requested(data2, true);
        
        tree1 = btree_new(data,
                          (BTREENODE_DESTROY_DATA) data_pretend_destroy,
                          (BTREENODE_PRINT_DATA) data_print);
        btree_destroy(&tree1, true);
        if (data != NULL && data_get_destruction_requested(data)
                                  == data_get_destruction_requested(data2))
        {
            ppr_tb_print_ok();
        }
        else
        {
            printf("\n[ERROR]\n"
                   "   Loeschen eines Baumes mit Loeschen der Daten\n"
                   "   expected:<[\n"
                   "    data: ");
            data_print(data2); 
            printf("\n"
                   "   ]> but was:<[\n"
                   "    data: ");
            data_print(data);
            printf("\n   ]>\n\n");
        }
        if (data != NULL)
        {
            data_destroy(&data);
        }
        if (data2 != NULL)
        {
            data_destroy(&data2);
        }
    }
    
    {
        BTREE_NODE *node1;
        BTREE_NODE *node2;
        struct Data *data1;
        struct Data *data2;
        struct Data *data3;
        struct Data *data_expected;
        printf("-----------------------------------------------------------\n"
               "9. Testfall : Loesche verschachtelten Baum - Enthaltene Daten der Knoten werden geloescht\n");
        /* Kopiere die Daten um spaeter im Fehlerfrei die erwarteten Daten anzuzeigen */
        data1 = data_new();
        data2 = data_new();
        data3 = data_new();
        data_expected = data_new();
        data_set_destruction_requested(data_expected, true);
        
        tree = btree_new(data1,
                          (BTREENODE_DESTROY_DATA) data_pretend_destroy,
                          (BTREENODE_PRINT_DATA) data_print);
        root = btree_get_root(tree);
        node1 = btreenode_new(data2);
        node2 = btreenode_new(data3);
        btreenode_set_right(root, node1);
        btreenode_set_left(node1, node2);
        
        btree_destroy(&tree, true);
        
        if (data1 != NULL && data2 != NULL
            && data3 != NULL
            && data_get_destruction_requested(data_expected)
               == data_get_destruction_requested(data1)
            && data_get_destruction_requested(data_expected)
               == data_get_destruction_requested(data2)
            && data_get_destruction_requested(data_expected)
               == data_get_destruction_requested(data3))
        {
            ppr_tb_print_ok();
        }
        else
        {
            if (data1 == NULL || data_expected == NULL
                || data_get_destruction_requested(data_expected)
                   != data_get_destruction_requested(data1))
            {
                printf("\n[ERROR]\n"
                       "   Loeschen eines Baumes mit Loeschen der Daten im Wurzelknoten\n"
                       "   expected:<[\n"
                       "    data: ");
                data_print(data_expected); 
                printf("\n"
                       "   ]> but was:<[\n"
                       "    data: ");
                data_print(data1);
                printf("\n   ]>\n\n");
            }
        
            if (data2 == NULL || data_expected == NULL
                || data_get_destruction_requested(data_expected)
                   != data_get_destruction_requested(data2))
            {
                printf("\n[ERROR]\n"
                       "   Loeschen eines Baumes mit Loeschen der Daten im rechten Sohn\n"
                       "   expected:<[\n"
                       "    data: ");
                data_print(data_expected); 
                printf("\n"
                       "   ]> but was:<[\n"
                       "    data: ");
                data_print(data2);
                printf("\n   ]>\n\n");
            }
        
            if (data3 == NULL || data_expected == NULL
                || data_get_destruction_requested(data_expected)
                   != data_get_destruction_requested(data3))
            {
                printf("\n[ERROR]\n"
                       "   Loeschen eines Baumes mit Loeschen der Daten im linken Sohn\n"
                       "   expected:<[\n"
                       "    data: ");
                data_print(data_expected); 
                printf("\n"
                       "   ]> but was:<[\n"
                       "    data: ");
                data_print(data3);
                printf("\n   ]>\n\n");
            }
        }
        
        if (data1 != NULL)
        {
            data_destroy(&data1);
        }
        if (data2 != NULL)
        {
            data_destroy(&data2);
        }
        if (data3 != NULL)
        {
            data_destroy(&data3);
        }
        if (data_expected != NULL)
        {
            data_destroy(&data_expected);
        }
    }
    
    {
        BTREE_NODE *node1;
        BTREE_NODE *node2;
        struct Data *data;
        printf("-----------------------------------------------------------\n"
               "10. Testfall : Ueberpruefe btreenode_is_leaf\n");
        
        data = data_new();
        
        tree = btree_new(data,
                          (BTREENODE_DESTROY_DATA) data_pretend_destroy,
                          (BTREENODE_PRINT_DATA) data_print);
        root = btree_get_root(tree);
        node1 = btreenode_new(data);
        node2 = btreenode_new(data);
        btreenode_set_right(root, node1);
        btreenode_set_left(node1, node2);
        
        if (root != NULL && node1 != NULL && node2 != NULL
            && btreenode_is_leaf(root) == false
            && btreenode_is_leaf(node1) == false
            && btreenode_is_leaf(node2) == true)
        {
            ppr_tb_print_ok();
        }
        else
        {
          
            if (root == NULL || btreenode_is_leaf(root) != false)
            {
                printf("\n[ERROR]\n"
                       "   Ueberpruefung des Wurzelknotens auf Blatt\n"
                       "   expected:<[\n");
                printf("false");
                printf("\n"
                       "   ]> but was:<[\n");
                if (btreenode_is_leaf(root) == false)
                {
                    printf("false");
                }
                else
                {
                        printf("true (value: %d)", btreenode_is_leaf(root));
                }
                printf("\n   ]>\n\n");
            }
        
            if (node1 == NULL || btreenode_is_leaf(node1) != false)
            {
                printf("\n[ERROR]\n"
                       "   Ueberpruefung des Unterknotens erste Ebene auf Blatt\n"
                       "   expected:<[\n");
                printf("false");
                printf("\n"
                       "   ]> but was:<[\n");
                if (btreenode_is_leaf(node1) == false)
                {
                    printf("false");
                }
                else
                {
                    printf("true (value: %d)", btreenode_is_leaf(node1));
                }
                printf("\n   ]>\n\n");
            }
        
            if (node2 == NULL || btreenode_is_leaf(node2) != true)
            {
                printf("\n[ERROR]\n"
                       "   Ueberpruefung des Unterknotens auf zweiter Ebene auf Blatt\n"
                       "   expected:<[\n");
                printf("true (value: 1)");
                printf("\n"
                       "   ]> but was:<[\n");
                if (btreenode_is_leaf(node2) == false)
                {
                    printf("false");
                }
                else
                {
                    printf("true (value: %d)", btreenode_is_leaf(node2));
                }
                printf("\n   ]>\n\n");
            }
        }
        
        btree_destroy(&tree, true);
        
        if (data != NULL)
        {
            data_destroy(&data);
        }
    }
}

/* ----------------------------------------------------------------------------
 * Funktion: main
 * ------------------------------------------------------------------------- */
#ifndef TESTBENCH
int main(void)
{
printf("%%SUITE_STARTING%% btree_testsuite\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  test_btree (btree_testsuite)\n");
    ppr_tb_test_btree();
    printf("%%TEST_FINISHED%% time=0 test_btree (btree_testsuite)\n");
    
    printf("%%SUITE_FINISHED%% time=0\n");
    
    return (EXIT_SUCCESS);
}
#endif

#ifdef TESTBENCH
int main(int argc, char **argv)
{   
    ppr_tb_write_total_assert(10);

    ppr_tb_test_btree();
    
    ppr_tb_write_summary("", argv[1]);
    
    return (EXIT_SUCCESS);
}
#endif
