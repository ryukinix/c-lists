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

// walk to a next node
node* walk_foward(node *n){
    n = n->next;
    return n;
}

// don't you mean walk backwards?
node* walk_backwards(node *n){
    n = n->back;
    return n;
}

void start_node(node *n){
    // allocation of memory 
    n = (node *) malloc(sizeof(node));
    
    // type choose and input of data
    type_choose(&(n->meta));
    n->meta.data = new_thing(n->meta.type);

    n->next = NULL;
}

// walk until the n node of the linked list
node* walk_until(node *head, int index){
    int i;
    node *n = head;
    for (i = 0; i < index && n != NULL; i++)
        n = walk_foward(n);
    return n;
}

node* walk_to_tail(node *head){
    node *n = head;

    int i;
    for (i = 0; n != NULL; i++)
        n = walk_foward(n);
    return n;
}

void remove_node(node **some_node){
    free(some_node);
    // maybe here's the error.
    some_node = (*some_node)->next;
}

// END

// print the list
void print_list(list *l) {
    int i;
    node *n = l->elements;

    printf("%s: [ ", l->subclass);
    for (i = 0; l->elements != NULL; i++){
        print_element(n->meta);
        n = walk_foward(n);
    }
    printf("]\n");
}

// clear the list
void clear_list(list *l){
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
        n = walk_foward(n);
    }
}

