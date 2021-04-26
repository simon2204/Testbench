/* ===========================================================================
 * Header-Dateien einbinden
 * ======================================================================== */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "btreenode.h"
#include "btree_common.h"


/* ===========================================================================
 * Strukturen
 * ======================================================================== */

/**
 * Ein Knoten eines Binärbaumes enthält beliebige Daten sowie einen linken
 * und einen rechten Nachfolger. Beide Nachfolger können NULL sein, dann ist
 * der Knoten ein Blatt.
 */
struct _BTREE_NODE
{
    /**
     * Daten des Knotens
     */
    void *data;
    
    /** 
     * linker Teilbaum des Kotens
     */
    struct _BTREE_NODE *left;
    
    /** 
     * rechter Teilbaum des Kotens
     */
    struct _BTREE_NODE *right;
};


/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: btreenode_new
 * ------------------------------------------------------------------------ */
extern BTREE_NODE *btreenode_new(void *data)
{
    BTREE_NODE *node = (BTREE_NODE *) malloc(sizeof (BTREE_NODE));
    ENSURE_ENOUGH_MEMORY(node, "btreenode_new");

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/* ---------------------------------------------------------------------------
 * Funktion: btreenode_clone
 * ------------------------------------------------------------------------ */
extern BTREE_NODE *btreenode_clone(BTREE_NODE *node)
{
    BTREE_NODE *clone = NULL;

    if (node != NULL)
    {
        clone = btreenode_new(node->data);

        btreenode_set_left(clone, btreenode_clone(btreenode_get_left(node)));
        btreenode_set_right(clone, btreenode_clone(btreenode_get_right(node)));
    }

    return clone;
}

/* ---------------------------------------------------------------------------
 * Funktion: btreenode_equals
 * ------------------------------------------------------------------------ */
extern bool btreenode_equals(BTREE_NODE *node1, BTREE_NODE *node2)
{
    return (node1 == NULL && node2 == NULL)
            || ((btreenode_get_data(node1) == btreenode_get_data(node2))
            && btreenode_equals(btreenode_get_left(node1),
                                btreenode_get_left(node2))
            && btreenode_equals(btreenode_get_right(node1),
                                btreenode_get_right(node2)));

}

/* ---------------------------------------------------------------------------
 * Funktion: btreenode_destroy
 * ------------------------------------------------------------------------ */
extern void btreenode_destroy(BTREE_NODE **node, 
                              DESTROY_DATA_FCT destroy_data)
{
    if (*node != NULL)
    {
        /* Erst die beiden Teilbäume löschen und dann die Wurzel */
        BTREE_NODE *left_node = btreenode_get_left(*node);
        BTREE_NODE *right_node = btreenode_get_right(*node);
        
        btreenode_destroy(&left_node, destroy_data);
        btreenode_destroy(&right_node, destroy_data);

        /* Lösche die Daten des Knotens. */
        if (destroy_data != NULL)
        {
            void *data = (void *) btreenode_get_data(*node);            
            destroy_data(&data);
        }

        free(*node);
        *node = NULL;
#ifdef DEBUG
        printf("Knoten %p geloescht\n", node);
#endif 
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: btreenode_get_data
 * ------------------------------------------------------------------------ */
extern void *btreenode_get_data(BTREE_NODE *node)
{
    if (node != NULL)
    {
        return node->data;
    }

    return NULL;
}

/* ---------------------------------------------------------------------------
 * Funktion: btreenode_get_left
 * ------------------------------------------------------------------------ */
extern BTREE_NODE *btreenode_get_left(BTREE_NODE *node)
{
    if (node != NULL)
    {
        return node->left;
    }

    return NULL;
}

/* ---------------------------------------------------------------------------
 * Funktion: btreenode_get_right
 * ------------------------------------------------------------------------ */
extern BTREE_NODE *btreenode_get_right(BTREE_NODE *node)
{
    if (node != NULL)
    {
        return node->right;
    }

    return NULL;
}

/* ---------------------------------------------------------------------------
 * Funktion: btreenode_is_leaf
 * ------------------------------------------------------------------------ */
extern bool btreenode_is_leaf(BTREE_NODE *node)
{
    if (node != NULL)
    {
        return (node->left == NULL && node->right == NULL);
    }
    return false;
}

/* ---------------------------------------------------------------------------
 * Funktion: btreenode_set_left
 * ------------------------------------------------------------------------ */
extern bool btreenode_set_left(BTREE_NODE *parent_node, BTREE_NODE *node)
{
    if (parent_node == NULL || parent_node->left != NULL)
    {
        return false;

    }
    else
    {
        parent_node->left = node;
        return true;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: btreenode_set_right
 * ------------------------------------------------------------------------ */
extern bool btreenode_set_right(BTREE_NODE *parent_node, BTREE_NODE *node)
{
    if (parent_node == NULL || parent_node->right != NULL)
    {
        return false;

    }
    else
    {
        parent_node->right = node;
        return true;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: btreenode_print
 * ------------------------------------------------------------------------ */
extern void btreenode_print(BTREE_NODE *node, PRINT_DATA_FCT print_data)
{
    if (node != NULL)
    {
        printf("(%p", (void *) node);  

        if (print_data != NULL)
        {
            print_data(node->data);
        }
        else
        {
            printf("...");
        }
        printf(")");
    }
}

