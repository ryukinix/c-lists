/* =============================================
 *
 *  -*- Definition of all basic functions list  -*-
 *
 * =============================================
 */

#include <time.h>

//print the list
void print_list(list *l) {
    int i;
    identifier type = l->elements[0].type;

    printf("%s: [ ", l->subclass);
    for (i = 0; i < l->size; i++)
        print_element(l->elements[i]);
    printf("]\n");
}


//insert on index
void insert_on(list *l, int index) {
    something the_thing = new_thing(l->elements[0].type);
    l->elements[index].data = the_thing;
}


// rearrange the list
void rearrange(list *l) {
    // ignoring empty blocks and rearrange the vector
    int i, j;
    for (i = 0, j = 0; i < l->size; i++) {
        if (l->elements[i].data.integer != -1) {
            l->elements[j] = l->elements[i];
            j++;
        }
    }

    // assigning the garbage in right of vector as empty
    for (i = j; i < l->size; i++) {
        l->elements[i].data.integer = -1;
    }

    l->last_index = j - 1;
}


// delete some element
void del(list *l, int index) {
    l->elements[index].data.integer = -1;
    rearrange(l);
}

//clear the list
void clear_list(list *l){
    int index;
    for(index = 0; index < l->size; index++)
        l->elements[index].data.integer = -1;
    rearrange(l);
}

//verify the state of list
void verify_state(list *l) {
    if (l->last_index == -1)
        l->state = empty;
    else if (l->last_index >= l->size - 1)
        l->state = full;
    else
        l->state = available;
}

//choose the type of the list
void type_choose(list *l) {
    int command, i;
    puts("Choose a type for the list");
    printf("1.Int\n2.Char\n3.Float\n\n");
    printf("Enter a command: ");
    scanf("%d", &command);
    clear_buffer();

    for (i= 0; i < l->size; i++) {
        //that verification it will usefull on the type change
        if (l->elements[i].data.integer == -1){
            if (command == 1)
               l->elements[i].type = integer;
            else if (command == 2)
               l->elements[i].type = character;
            else if (command == 3)
               l->elements[i].type = real;
            else        
               type_choose(l);
        }
    }
}


/* ===============================================
 *
 *             -*- Meta comment -*-
 *
 * Was adopted that the begin index to control is -1,
 * Like this as the empty value too.
 * 
 * ===============================================
 */


void start(list *l) {
    // get the size of list
    int size = generate("Enter a size: ");
    l->size = size;

    // alloc memory
    l->elements = (meta_data *) malloc(sizeof(meta_data) * size);
    if (l->elements == NULL) {
        puts("Error with alloc memory! Try again with other size.");
        start(l);
    }

    // start the initial values
    l->last_index = -1;
    l->state = empty;

    int i;
    for (i = 0; i < l->size; i++) {
        l->elements[i].data.integer = -1;
    }

    //Ask the type to receive
    type_choose(l);
}


//insert random values all on the list
void random_values(list *l) {
    int i;
    time_t t;
    srand((unsigned) time(&t));

    for (i = 0; i < l->size; i++) {
        identifier type = l->elements[i].type;
        if (type == integer)
            l->elements[i].data.integer = rand() % 100;
        else if (type == character)
            l->elements[i].data.character = 'a' + rand() % 26;
        else if (type == real)
            l->elements[i].data.real = (rand() % 100 / ( (rand () % 10) + 1));
    }
    
    l->last_index = i - 1;
}

