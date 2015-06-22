/*
 * =====================================================================================
 *
 *                      Copyright 2015 Manoel Vilela
 *
 *
 *       Filename:  half-dynamic-queue.c
 *
 *    Description:  A queue whose you can choose the type
 *
 *         Author:  Manoel Vilela
 *        Contact:  manoel_vilela@engineer.com
 *   Organization:  UFPA
 *
 * =====================================================================================
**/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CLEAR "clear || cls"


/* =============================================
 *
 *             -*- Meta comment -*-
 *
 * Foi convencionado que o indice de início é -1,
 * Assim como também o espaço vazio.
 * 
 * ============================================
 */

/* ================================================
 *
 *  -*- All structures definition are below  -*-
 *
 *=================================================
 */

typedef union {
    int integer;
    char character;
    float real;
} metathing;


typedef enum {
    integer,
    character,
    real,
} identifier;


typedef struct {
    metathing data;
    identifier type;
} metadata;


typedef enum {
    empty,
    available,
    full
} id_state;


typedef struct {
    metadata *elements;
    id_state state;
    int last_index;
    int size;
} queue;

// for aux the enums
static const char *type_strings[] = { "integer", "character",  "real"};
static const char *state_strings[] = {"empty", "available", "full"};



/* ===================================================================
 *
 *    -*-  A resume of queue struct    -*-
 *  
 *     char *type := the type of the user choose
 * int last_index := index of vector whose is used to control i/o
 *      int state := {0:empty, 1:available, 2:full}
 *       int size := the lenght of queue
 *
 * ====================================================================
 */




/* ==========================================
 *
 *  -*- Declarations of all functions  -*-
 *
 * ==========================================
 */


// methods of list
int step(queue *q);
int insert(queue *q);
int search(queue *q, metathing thing);
int erase(queue *q, metathing thing);
int edit(queue *q, int index);

// aux-functions
void type_choose(queue *q);
void start(queue *q);
void random_values(queue *q);
void rearrange(queue *q);
void del(queue *q, int index);
void verify_state(queue *q);

// in-out and terminal functions
int  generate(const char *message);
metathing new_thing(queue *q);
void insert_on(queue *q, int index);
void print_element(metadata element);
void print_list(queue *q);
void menu(queue *q);
void clear(void);
void pause(const char* msg);


/* ==========================================
 *
 *  -*-       THE BIG MAIN CODE           -*-
 *
 * ==========================================
 */

int main(void) {
    queue q;

    start(&q);
    menu(&q);

    return 0;
}


/* ==========================================
 *
 *  -*- Definition of all functions  -*-
 *
 * ==========================================
 */


void type_choose(queue *q) {
    int command, i;
    puts("Choose a type for the list");
    printf("1.Int\n2.Char\n3.Float\n\n");
    printf("Enter a command: ");
    scanf("%d", &command);
    clear();

    for (i= 0; i < q->size; i++) {
        //that verification it will usefull on the type change
        if (q->elements[i].data.integer == -1){
            if (command == 1)
               q->elements[i].type = integer;
            else if (command == 2)
               q->elements[i].type = character;
            else if (command == 3)
               q->elements[i].type = real;
            else        
               type_choose(q);
        }
    }
}

// iniciar q
void start(queue *q) {
    // get the size of list
    int size = generate("Enter a size: ");
    q->size = size;

    // alloc memory
    q->elements = (metadata *) malloc(sizeof(metadata) * size);
    if (q->elements == NULL) {
        puts("Error with alloc memory! Try again with other size.");
        start(q);
    }

    // start the initial values
    q->last_index = -1;
    q->state = empty;

    int i;
    for (i = 0; i < q->size; i++) {
        q->elements[i].data.integer = -1;
    }

    //Ask the type to receive
    type_choose(q);
}

void random_values(queue *q) {
    int i;
    time_t t;
    srand((unsigned) time(&t));

    for (i = 0; i < q->size; i++) {
        identifier type = q->elements[i].type;
        if (type == integer)
            q->elements[i].data.integer = rand() % 100;
        else if (type == character)
            q->elements[i].data.character = 'a' + rand() % 26;
        else if (type == real)
            q->elements[i].data.real = (rand() % 100) / (rand () % 100);
    }
    
    q->last_index = i + 1;
}

void rearrange(queue *q) {
    // ignoring empty blocks and rearrange the vector
    int i, j;
    for (i = 0, j = 0; i < q->size; i++) {
        if (q->elements[i].data.integer != -1) {
            q->elements[j] = q->elements[i];
            j++;
        }
    }

    // assigning the garbage in right of vector as empty
    for (i = j; i < q->size; i++) {
        q->elements[i].data.integer = -1;
    }

    q->last_index = j - 1;
}

// delete some element
void del(queue *q, int index) {
    q->elements[index].data.integer = -1;
    rearrange(q);
}


// generate a int number with a message for stdout
int generate(const char *message) {
    int num;
    puts(message);
    scanf("%d", &num);
    printf("\n");
    clear();

    return num;
}


metathing new_thing(queue *q){
    printf("Insert a thing: ");
    identifier type = q->elements[0].type;
    metathing the_thing;

    if (type == integer)
        scanf("%d", &the_thing.integer);
    else if (type == character)
        scanf("%c", &the_thing.character);
    else if (type == real)
        scanf("%f", &the_thing.real);

    clear();

    return the_thing;
}



void insert_on(queue *q, int index) {
    metathing the_thing = new_thing(q);

    q->elements[index].data = the_thing;
}

void verify_state(queue *q) {
    if (q->last_index == -1)
        q->state = empty;
    else if (q->last_index >= q->size - 1)
        q->state = full;
    else
        q->state = available;
}


// step the queue (remove the head)
int step(queue *q) {
    if (q->state == empty) {
        return -1;
    } else {
        printf("Pop head: ");
        print_element(q->elements[0]);
        del(q, 0);
    }

    return 0;
}


// insert a value in a tail of queue;
int insert(queue *q) {
    if (q->state == full)
        return -1;

    q->last_index++;
    insert_on(q, q->last_index);

    return 0;
}

int search(queue *q, metathing thing) {
    int i;

    for (i = 0; i < q->size; i++)
        if (q->elements[i].data.real == thing.real)
            return i;
    return -1;
}

int erase(queue *q, metathing thing) {
    int index = search(q, thing);

    if (index != -1)
        del(q, index);
    else
        return -1;

    return index;
}

int edit(queue *q, int index) {
    // verify if index is not do the pesar of violate the lenght of vector
    if (!(index >= 0 && index <= q->size))
        return -1;

    insert_on(q, index);

    return 0;
}

void print_element(metadata element) {
    identifier type = element.type;

    if (element.data.integer != -1) {
        if (type == integer)
            printf(" (%d) ", element.data.integer);
        else if (type == character)
            printf(" (%c) ", element.data.character);
        else if (type == real)
            printf(" (%.2f) ", element.data.real);
    } else {
        printf(" () ");
    }
}


void print_list(queue *q) {
    int i;
    identifier type = q->elements[0].type;

    printf("Queue: [ ");
    for (i = 0; i < q->size; i++)
        print_element(q->elements[i]);
    printf("]\n");
}

// clear the stdin
void clear(void) {
    char c;
    while (c = getchar() != '\n' && c != EOF )
        continue;
}

// arg for a string: print and pause.
void pause(const char* msg) {
    printf("%s", msg);
    clear();
}

void menu(queue *q) {
    int command, status;
    metathing element;

    do {
        system(CLEAR);
        verify_state(q);
        puts("Implementation of type queue in the class list!\n\n");
        printf("[size]: %d\n", q->size);
        printf("[type]: %s\n", type_strings[ (q->elements[0].type) ]);
        printf("[status]: %s\n\n", state_strings[q->state]);
        printf("\
                0.Exit\n\n\
                Fundamental Methods:\n\
                1.Insert\n\
                2.Step\n\
                3.Print_list\n\
                4.Search\n\
                5.Edit\n\
                6.Erase\n\
                7.Rearrange\n\
                8.RandomValues\n\
                9.TypeChange\n\n");
        printf("Type a command: ");
        scanf("%d", &command);
        clear();

        switch (command) {
            case 1:
                status = insert(q);
                if (status == -1) puts("Full queue!");
                break;

            case 2:
                status = step(q);
                if (status == -1) puts("Empty queue!");
                break;

            case 3:
                print_list(q);
                break;

            case 4:
                printf("== Search ==\n");
                element = new_thing(q);
                status = search(q, element);
                
                // output
                if (status != -1)
                    printf("Found on index %d!\n", status);
                else
                    printf("Error 404: Not found!\n");
                break;

            case 5:
                element.integer = generate("Edit value in index: ");
                status = edit(q, element.integer);
                
                if (status == -1)
                    printf("Index out of the range!\n");
                
                break;

            case 6:
                printf("== Erase element ==\n");
                element = new_thing(q);
                status = erase(q, element);
                
                // output
                if (status != -1)
                    printf("Found on index %d! Deleted!\n", status);
                else
                    printf("Error 404: Not found!\n");
                break;

            case 7:
                rearrange(q);
                break;

            case 8:
                random_values(q);
                break;
            case 9:
                type_choose(q);
                break;

            case 0:
                printf("Leaving the universe...\n");
                break;

            default:
                printf("Command invalid, try again.!\n");
                break;
        }

        pause("Press enter to continue...");
    }while(command != 0);
}
