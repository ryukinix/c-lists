/* ================================================
 *
 *  -*- All structures definition are below  -*-
 *
 *=================================================
 */


// for aux the enums
static const char *type_strings[] = { "integer", "character",  "real"};
static const char *state_strings[] = {"empty", "available", "full"};

typedef enum {
    empty,
    available,
    full
} id_state;


typedef struct {
    meta_data element;
    node *next;
} node;

typedef struct {
    char subclass[10];
    node *elements;
    id_state state;
    int last_index;
    int size;
} list;


/* ===================================================================
 *
 *                 -*-  A resume of a list struct    -*-
 * const char *subclass := "queue" || "stack" || "deque"
 *  meta_data *elements := {something data, identifier type}
 *       id_state state := {0:empty, 1:available, 2:full}
 *      int first_index := index of vector whose is used to control i/o
 *       int last_index := index of vector whose is used to control i/o
 *             int size := the lenght of queue
 *            int state := {0:empty, 1:available, 2:full}
 *
 * ====================================================================
 */

