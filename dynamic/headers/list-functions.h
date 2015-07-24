#ifndef LIST_FUNCTIONS_H
#define LIST_FUNCTIONS_H

/* ================================================
 *
 *  -*- Definition of all basic functions list  -*-
 *
 * ================================================
 */


#include <time.h>


/* =============================================
 *
 *  -*-   Node control for linked list      -*-
 *
 * =============================================
 */

node* walk_forward(node *some_node) {
    some_node = some_node->next;
    return some_node;
}

node* walk_backwards(node *some_node) {
    some_node = some_node->back;
    return some_node;
}

node* walk_to_tail(node *some_node){
    while (some_node->next != NULL){
        some_node = walk_forward(some_node);
    }

    return some_node;
}

void insert_node(node *some_node){
    // type choose and input of data
    new_meta(&(some_node->meta));
}


void start_node(node **some_node){
    // allocation of memory
    *some_node = (node *) malloc(sizeof(node));
    insert_node(*some_node);
    (*some_node)->next = NULL;
}

void remove_node(node **some_node){
    // free pointer
    free(*some_node);

    // for 'back' element, jump the 'next' reference 
    if ((*some_node)->back != NULL)
        (*some_node)->back->next = (*some_node)->next;
    // for 'next' element, jump the 'back' reference
    if ((*some_node)->next != NULL)
        (*some_node)->next->back = (*some_node)->back;

    // pointer this node to next element
    *some_node = (*some_node)->next;
}



/* =============================================
 *
 *  -*-   List manipulation functions    -*-
 *
 * =============================================
 */

void print_list(list *l) {
    int i;
    node *some_node = l->elements;

    printf("%s: [ ", l->subclass);
    for (i = 0; some_node != NULL; i++){
        print_element(some_node->meta);
        some_node = walk_forward(some_node);
    }
    printf("]\n");
}

void free_list(list *l) {
    node *some_node = l->elements;
    while (some_node != NULL){
        free(some_node);
        some_node = walk_forward(some_node);
    }
}

void clear_list(list *l) {
    free_list(l);
    l->size = 0;
    l->elements = NULL;
    l->state = empty;
}

void verify_state(list *l) {
    if (l->size == 0)
        l->state = empty;
    else
        l->state = available;
}

void start(list *l) {
    // initial size;
    l->size = 0;

    // point to null
    l->elements = NULL;

    // start the initial values
    l->state = empty;
}

// insert random values all on the list
void random_values(list *l) {
    int i;
    time_t t;
    srand((unsigned) time(&t));

    node *some_node = l->elements;

    for (i = 0; i < l->size; i++) {
        identifier type = some_node->meta.type;
        if (type == integer)
            some_node->meta.data.integer = rand() % 100;
        else if (type == character)
            some_node->meta.data.character = 'a' + rand() % 26;
        else if (type == real)
            some_node->meta.data.real = (rand() % 100 / ( (rand () % 10) + 1));
        some_node = walk_forward(some_node);
    }
}

void search(list *l, something thing) {
    node *some_node = l->elements;
    int index = 0;
    while (some_node != NULL) {
        if (union_comparision(some_node->meta.data, thing)){
            printf("\n[search] On index %d was found: ", index);
            print_element(some_node->meta);
            printf("\n");
        }
        index++;
        some_node = walk_forward(some_node);
    }
}

void erase(list *l, something thing) {
    printf("A LOT OF BUGS!\n");
    // node **some_node = &(l->elements);
    // int index = 0;
    // while ((*some_node) != NULL) {
    //     if (union_comparision((*some_node)->meta.data, thing)){
    //         printf("\n[erase] On index %d was deleted: ", index);
    //         print_element((*some_node)->meta);
    //         printf("\n");
    //         remove_node(some_node);
    //         l->size -= 1;
    //         return; 
    //     }
    //     index++;
    //     some_node = &((*some_node)->next);
    // }
}

void edit(list *l, something thing) {
    node *some_node = l->elements;
    int index = 0;
    while (some_node != NULL) {
        if (union_comparision(some_node->meta.data, thing)) {
            printf("\n[edit] On index %d was editing: ", index);
            print_element(some_node->meta);
            printf("\n");
            insert_node(some_node);
        }
        index++;
        some_node = walk_forward(some_node);
    }
}



#endif //LIST_FUNCTIONS_H
