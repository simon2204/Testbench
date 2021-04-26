/**
 * @file extern_prototypes.c (blatt09)
 *
 * @brief
 * Dieses Modul enthaelt die Prototypen der in den Modulen verwendeten 
 * externen Funktionen und wird bei der statischen Code-Pruefung mit 
 * Splint - insbesondere unter Verwendung des Flag "exportlocal" - 
 * verwendet. Ziel ist es, die vom Benutzer definierten Funktionen
 * aufzudecken, die weder mit dem extern- noch mit dem static-
 * Modifikator versehen wurden (sind also implizit "extern"), d.h. sie 
 * werden durch ensprechende Warnhinweise, die ins Auswertungsprotokoll
 * geschrieben werden, aufgezeigt, bspw. 
 * "Function exported but not used outside btree: btree_print_rek
 * A declaration is exported, but not used outside this module.
 * Declaration can use static qualifier."
 *        
 * Fuer externe Funktionen, die "scheinbar" nicht von aussen aufgerufen 
 * werden, werden die Warnmeldungen hingegegen unterdrueckt.
 *
 * @author  Ulrike Griefahn, Franz Bachmann
 * @date    2013-04-17
 */
 
 #include <stdbool.h>


/* ===========================================================================
 * Funktionsprototypen
 * ======================================================================== */
 
/* ---------------------------------------------------------------------------
 * btree
 * ------------------------------------------------------------------------ */
extern void *btree_new();
extern void *btree_clone();
extern void btree_destroy();
extern int btree_equals();
extern void *btree_get_root();
extern void *btree_merge();
extern void btree_print();

/* ---------------------------------------------------------------------------
 * btreenode
 * ------------------------------------------------------------------------ */
extern void *btreenode_new();
extern void *btreenode_clone();
extern int btreenode_equals();
extern void btreenode_destroy();
extern void *btreenode_get_data();
extern void *btreenode_get_left();
extern void *btreenode_get_right();
extern int btreenode_is_leaf();
extern int btreenode_set_left();
extern int btreenode_set_right();
extern void btreenode_print();

/* ---------------------------------------------------------------------------
 * frequency
 * ------------------------------------------------------------------------ */
extern struct FREQUENCY *create_frequency(const char *word, const int count);
extern void destroy_frequency(struct FREQUENCY **pp_frequency);
extern char *get_word_from_frequency(const struct FREQUENCY *p_frequency);
extern int get_count_from_frequency(const struct FREQUENCY *p_frequency);
extern void set_word_in_frequency(struct FREQUENCY *p_frequency, 
                                  const char *word);
extern void set_count_in_frequency(struct FREQUENCY *p_frequency, 
                                   const int count);
extern int compare_frequency(const struct FREQUENCY *p_frequency1, 
                             const struct FREQUENCY *p_frequency2);
extern char *get_frequency_as_string(const struct FREQUENCY *p_frequency);
extern void print_frequency(const struct FREQUENCY *p_frequency);

/* ---------------------------------------------------------------------------
 * data
 * ------------------------------------------------------------------------ */

extern struct Data *data_new();
extern void data_pretend_destroy(struct Data **pp_data);
extern void data_destroy(struct Data **pp_data);
extern bool data_get_destruction_requested(const struct Data *p_data);
extern void data_set_destruction_requested(struct Data *p_data, bool destruction_requested);
extern void data_print(const struct Data *p_data);