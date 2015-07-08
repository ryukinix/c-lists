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
    n = n->next
    return n;
}
node* walk_foward(node *n){
    n = n->back
    return n;
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
    int i;
    node *n = head;
    for (i = 0; i < index && n != NULL; i++)
        n = walk_foward(n);
    return n;
}

// print the list
void print_list(list *l) {
    int i;
    identifier type = l->elements.type;
    node *n = l->elements;

    printf("%s: [ ", l->subclass);
    for (i = 0; l->elements != NULL; i++){
        print_element(n->meta);
        n = walk_foward(n);
    }
    printf("]\n");
}


// insert on index
void insert_on(list *l, int index) {
    something the_thing = new_thing(l->elements->type);
    walk_until(l, index);
    l->elements.n.data = the_thing;
}


// delete some element
void del(list *l, int index){
    walk_until(l, index);
    free(l->elements);
}

// clear the list
void clear_list(list *l){
    l->size = 0;
    l->elements = NULL;
    l->id_state = empty;
}

// verify the state of list
void verify_state(list *l) {
    if (size == 0)
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
        identifier type = l->elements.meta.type;
        if (type == integer)
            n->meta.data.integer = rand() % 100;
        else if (type == character)
            n->meta.data.character = 'a' + rand() % 26;
        else if (type == real)
            n->data.real = (rand() % 100 / ( (rand () % 10) + 1));
        n = walk_foward(n);
    }
}

