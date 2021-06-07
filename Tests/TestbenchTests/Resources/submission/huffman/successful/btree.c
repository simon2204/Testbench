/* ===========================================================================
 * Header-Dateien einbinden  
 * ======================================================================== */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "btree.h"
#include "btreenode.h"
#include "btree_common.h"


/* ===========================================================================
 * Strukturen
 * ======================================================================== */

/**
 * Struktur f¸r die Informationen eines Bin‰rbaums. Besteht aus der Wurzel und
 * einer Funktion, mit der die Daten der Knoten am Bildschirm ausgegeben werden
 * kˆnnen. */
struct _BTREE
{
    /**
     * Wurzelknoten des Bin‰rbaums
     */
    BTREE_NODE *root;
    
    /**
     * Funktion zum Lˆschen der Daten
     */
    DESTROY_DATA_FCT destroy_data;
    
    /**
     * Funktion zum Anzeigen der Daten auf dem Bildschirm
     */
    PRINT_DATA_FCT print_data;
};

/* ===========================================================================
 * Funktionsprototypen
 * ======================================================================== */

/**
 * rekursive Hilfsfunktion f¸r btree_print. Gibt den Bin‰rbaum in
 * Preorder-Reihenfolge auf dem Bildschirm aus.
 *
 * @param tree      auszugebender Bin‰rbaum
 * @param node      aktuell auszugebender Knoten
 * @param indent    Einr¸ckungstiefe f¸r die Ausgabe des aktuellen Knotens
 */
static void btree_print_rek(BTREE *tree, BTREE_NODE *node, int indent);


/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: btree_new
 * ------------------------------------------------------------------------ */
extern BTREE *btree_new(void *data,
                        DESTROY_DATA_FCT destroy_data, 
                        PRINT_DATA_FCT print_data)
{
    BTREE *btree;
    BTREE_NODE *bnode;

    btree = (BTREE *) malloc(sizeof (BTREE));
    ENSURE_ENOUGH_MEMORY(btree, "btree_new");

    bnode = btreenode_new(data);

    btree->root = bnode;
    btree->destroy_data = destroy_data;
    btree->print_data = print_data;

    return btree;
}

/* ---------------------------------------------------------------------------
 * Funktion: btree_clone
 * ------------------------------------------------------------------------ */
extern BTREE *btree_clone(BTREE *tree)
{
    BTREE *clone = NULL;
    
    if (tree != NULL)
    {
        clone = (BTREE *) malloc(sizeof (BTREE));
        ENSURE_ENOUGH_MEMORY(clone, "btree_new");

        clone->root = btreenode_clone(btree_get_root(tree));
        clone->destroy_data = tree->destroy_data;
        clone->print_data = tree->print_data;
    }
    
    return clone;
}

/* ---------------------------------------------------------------------------
 * Funktion: btree_destroy
 * ------------------------------------------------------------------------ */
extern void btree_destroy(BTREE **tree, bool destroy_data)
{
    BTREE_NODE *root = btree_get_root(*tree);

#ifdef DEBUG
    printf("Loesche Binaerbaum %p\n", tree);
#endif 

    if (destroy_data == true)
    {
        btreenode_destroy(&root, (*tree)->destroy_data);
    }
    else
    {
        btreenode_destroy(&root, NULL);
    }
    free(*tree);
    *tree = NULL;
}


/* ---------------------------------------------------------------------------
 * Funktion: btree_equals
 * ------------------------------------------------------------------------ */
extern bool btree_equals(BTREE *tree1, BTREE *tree2)
{

#ifdef DEBUG
    printf("Vergleiche Binaerbaeume %p und %p\n", tree1, tree2);
#endif

    return (tree1 != NULL && tree2 != NULL)
            && btreenode_equals(tree1->root, tree2->root);
}


/* ---------------------------------------------------------------------------
 * Funktion: btree_get_root
 * ------------------------------------------------------------------------ */
extern BTREE_NODE *btree_get_root(BTREE *btree)
{

    if (btree != NULL)
    {
        return btree->root;
    }

    return NULL;
}

/* ---------------------------------------------------------------------------
 * Funktion: btree_merge
 * ------------------------------------------------------------------------ */
extern BTREE *btree_merge(BTREE *left, BTREE *right, void *data)
{

    BTREE *merge = NULL;
    BTREE_NODE *root;
    
    if (left != NULL && right != NULL)
    {
        merge = btree_new(data, left->destroy_data, left->print_data);

        root = btree_get_root(merge);
        btreenode_set_left(root, left->root);
        btreenode_set_right(root, right->root);

        /* Speicher der alten B‰ume freigeben. */
        free(left);
        free(right);
    }

    return merge;
}

/* ---------------------------------------------------------------------------
 * Funktion: btree_print
 * ------------------------------------------------------------------------ */
extern void btree_print(BTREE *tree)
{
    BTREE_NODE *root = btree_get_root(tree);
    if (root != NULL)
    {
        btree_print_rek(tree, root, 0);
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: btree_print_rek
 * ------------------------------------------------------------------------ */
static void btree_print_rek(BTREE *tree, BTREE_NODE *node, int indent)
{
    int i;

    /* Nur weiterarbeiten, wenn ein Knoten uebergeben wurde */
    if (node != NULL)
    {

        /* Zeile f√ºr den aktuellen Knoten */
        for (i = 0; i < indent; i++)
        {
            printf("    ");
        }
        printf("|-- ");

        btreenode_print(node, tree->print_data);

        printf("\n");

        /* linker Teilbaum */
        btree_print_rek(tree, btreenode_get_left(node), indent + 1);

        /* rechter Teilbaum */
        btree_print_rek(tree, btreenode_get_right(node), indent + 1);
    }
}





