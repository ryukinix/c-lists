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
    return some_node->next;
}

node* walk_backwards(node *some_node) {
    return some_node->back;
}

node* walk_to_tail(node *some_node) {
    while (some_node->next != NULL)
        some_node = walk_forward(some_node);

    return some_node;
}

node** tail_pointer(node **some_node) {
    if ((*some_node)->next == NULL)
        return some_node;
    else
        return tail_pointer(&((*some_node)->next));
}

void insert_node(node *some_node) {
    new_meta(&(some_node->meta));
}

void start_node(node **some_node) {
    // allocation of memory
    *some_node = (node *) malloc(sizeof(node));
    (*some_node)->next = NULL;
    (*some_node)->back = NULL;    
}

node* remove_node(node *some_node) {
    // free pointer
    free(some_node);

    // for 'back' element, jump the 'next' reference 
    if (some_node->back != NULL)
        some_node->back->next = some_node->next;
    // for 'next' element, jump the 'back' reference
    if (some_node->next != NULL)
        some_node->next->back = some_node->back;

    // pointer this node to next element
    some_node = some_node->next;

    return some_node;
}

/* =============================================
 *
 *  -*-   List manipulation functions    -*-
 *
 * =============================================
 */

void debug_pointers(node **some_node) {
    printf("self := %p", (*some_node));
    printf("next := %p", (*some_node)->next);
    printf("back := %p", (*some_node)->back);
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

void erase_search(node **some_node, something thing, int *size, int index){
    if ((*some_node) == NULL) {
        return ;
    }

    else if (union_comparision((*some_node)->meta.data, thing)) {
        printf("\n[erase] On index %d was deleted: ", index);
        print_element((*some_node)->meta);
        printf("\n");
        *some_node = remove_node(*some_node);
        *size -= 1;
    }

    else {
        erase_search(&((*some_node)->next), thing, size, index + 1);
    }
}


void erase(list *l, something thing) {
    node **head = &(l->elements);
    int *size = &(l->size);
    int index = 0;

    erase_search(head, thing, size, index);
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
