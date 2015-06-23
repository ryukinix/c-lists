/* ================================================
 *
 *  -*- All structures definition are below  -*-
 *
 *=================================================
 */

typedef enum {
    empty,
    available,
    full
} id_state;


typedef struct {
    meta_data *elements;
    id_state state;
    char subclass[10];
    int first_index;
    int last_index;
    int size;
} list;

// for aux the enums
static const char *type_strings[] = { "integer", "character",  "real"};
static const char *state_strings[] = {"empty", "available", "full"};

