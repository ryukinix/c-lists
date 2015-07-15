#ifndef LIST_TYPE_H
#define LIST_TYPE_H

/* ===================================================================
 *
 *                 -*-  A resume of a dynamic list struct    -*-
 *
 * const char *subclass := "queue" || "stack" || "deque"
 *       node *elements := linked list
 *       id_state state := {0:empty, 1:available, 2:full}
 *             int size := the lenght of queue
 *
 * ====================================================================
 */


// for aux the enums
static const char *type_strings[] = { "integer", "character",  "real"};
static const char *state_strings[] = {"empty", "available", "full"};

typedef enum {
    empty,
    available,
    full
} id_state;


typedef struct _node {
    meta_data meta;
    struct _node *next;
    struct _node *back;
} node;

typedef struct {
    char subclass[10];
    node *elements;
    id_state state;
    int size;
} list;

#endif //LIST_TYPE_H
