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

node* walk_forward(node *n){
    n = n->next;
    return n;
}

node* walk_backwards(node *n){
    n = n->back;
    return n;
}

void insert_node(node *n){
    // type choose and input of data
    new_meta(&(n->meta));
}


void start_node(node **n){
    // allocation of memory
    *n = (node *) malloc(sizeof(node));
    insert_node(*n);
    (*n)->next = NULL;
}

void remove_node(node **some_node){
    printf("self: %p\n", *some_node);
    printf("next: %p\n", (*some_node)->next);
    printf("back: %p\n", (*some_node)->back);

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


// walk until the n node of the linked list
node* walk_until(node *head, int index){
    int i;
    node *n = head;
    for (i = 0; i < index && n != NULL; i++)
        n = walk_forward(n);
    return n;
}

node* walk_to_tail(node *head){
    node* n = head;

    while (n->next != NULL) {
        n = walk_forward(n);
    }

    return n;
}

/* =============================================
 *
 *  -*-   List manipulation functions    -*-
 *
 * =============================================
 */

// print the list
void print_list(list *l) {
    int i;
    node *n = l->elements;

    printf("%s: [ ", l->subclass);
    for (i = 0; n != NULL; i++){
        print_element(n->meta);
        n = walk_forward(n);
    }
    printf("]\n");
}

void free_list(list *l){
    node *n = l->elements;
    while (n != NULL){
        free(n);
        n = walk_forward(n);
    }
}


// clear the list
void clear_list(list *l){
    free_list(l);
    l->size = 0;
    l->elements = NULL;
    l->state = empty;
}

// verify the state of list
void verify_state(list *l) {
    if (l->size == 0)
        l->state = empty;
    else
        l->state = available;
}

// start the list
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

    node *n = l->elements;

    for (i = 0; i < l->size; i++) {
        identifier type = n->meta.type;
        if (type == integer)
            n->meta.data.integer = rand() % 100;
        else if (type == character)
            n->meta.data.character = 'a' + rand() % 26;
        else if (type == real)
            n->meta.data.real = (rand() % 100 / ( (rand () % 10) + 1));
        n = walk_forward(n);
    }
}

void search(list *l, something thing) {
    node *n = l->elements;
    int index = 0;
    while (n != NULL) {
        if (union_comparision(n->meta.data, thing)){
            printf("\n[search] On index %d was found: ", index);
            print_element(n->meta);
            printf("\n");
        }
        index++;
        n = walk_forward(n);
    }
}

void erase(list *l, something thing) {
    node *n = l->elements;
    int index = 0;
    while (n != NULL) {
        if (union_comparision(n->meta.data, thing)){
            printf("\n[erase] On index %d was deleted: ", index);
            print_element(n->meta);
            printf("\n");
            remove_node(&n);
            l->size -= 1;
        }
        index++;
        n = walk_forward(n);
    }
}

void edit(list *l, something thing) {
    node *n = l->elements;
    int index = 0;
    while (n != NULL) {
        if (union_comparision(n->meta.data, thing)) {
            printf("\n[edit] On index %d was editing: ", index);
            print_element(n->meta);
            printf("\n");
            insert_node(n);
        }
        index++;
        n = walk_forward(n);
    }
}



#endif //LIST_FUNCTIONS_H
