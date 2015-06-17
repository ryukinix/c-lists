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
}metadata;


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
int search(queue *q, int num);
int erase(queue *q, int num);
int edit(queue *q, int index);

// aux-functions
int  alloc_type(queue *q, int size);
void start(queue *q);
void random_values(queue *q);
void rearrange(queue *q);
void del(queue *q, int index);
void verify_state(queue *q);

// in-out and terminal functions
int  generate(const char *message);
void new_element(queue *q, int index);
void print_element(queue *q, int i);
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


int alloc_type(queue *q, int size) {
    int command;
    puts("Choose a type for the list");
    printf("1.Int\n2.Char\n3.Float\n\n");
    printf("Enter a command: ");
    scanf("%d", &command);
    clear();

    q->elements = (metadata *) malloc(sizeof(metadata) * size);

    if (q->elements == NULL)
        return -1;

    for (int i = 0; i < size; i++) {
       if (command = 1)
	       q->elements[i].type = integer;
       else if (command == 2)
           q->elements[i].type = character;
       else if (command = 3)
           q->elements[i].type = real;
       else        
           alloc_type(q, size);
    }

    return 0;
}

// iniciar q
void start(queue *q) {
    // get the size of list
    int size = generate("Enter a size: ");
    q->size = size;

    // alloc and ask the type
    if (alloc_type(q, size) == -1) {
        puts("Error with alloc memory! Try again with other size.");
        start(q);
    }

    // start the initial values
    q->last_index = -1;
    q->state = empty;

    for (int i = 0; i < q->size; i++) {
        q->elements[i].data.integer = -1;
    }
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

void new_element(queue *q, int index) {
    printf("Insert a value: ");
    identifier type = q->elements[index].type;

    if (type == integer)
        scanf("%d", &q->elements[index].data.integer);
    else if (type == character)
        scanf("%c", &q->elements[index].data.character);
    else if (type == real)
        scanf("%f", &q->elements[index].data.real);

    clear();
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
        print_element(q, 0);
        del(q, 0);
    }

    return 0;
}


// insert a value in a tail of queue;
int insert(queue *q) {
    if (q->state == full)
        return -1;

    q->last_index++;
    new_element(q, q->last_index);

    return 0;
}

int search(queue *q, int num) {
    int i;

    for (i = 0; i < q->size; i++)
        if (q->elements[i].data.integer == num)
            return i;
    return -1;
}

int erase(queue *q, int num) {
    int index = search(q, num);

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

    new_element(q, index);

    return 0;
}

void print_element(queue *q, int i) {
    identifier type = q->elements[i].type;

    if (q->elements[i].data.integer != -1) {
        if (type == integer)
            printf(" (%d) ", q->elements[i].data.integer);
        else if (type == character)
            printf(" (%c) ", q->elements[i].data.character);
        else if (type == real)
            printf(" (%.2f) ", q->elements[i].data.real);
    } else {
        printf(" () ");
    }
}


void print_list(queue *q) {
    int i;
    identifier type = q->elements[0].type;

    printf("Queue: [ ");
    for (i = 0; i < q->size; i++)
        print_element(q, i);
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
    int command, status, num_key;

    do {
        system(CLEAR);
        verify_state(q);
        puts("Implementation of type queue in the class list!\n\n");
        printf("[type]: %s\n", type_strings[ (q->elements[0].type) ]);
        printf("[status]: %s\n\n", state_strings[q->state]);
        printf("\
                0.Exit\n\
                1.Insert\n\
                2.Step\n\
                3.Print_list\n\
                4.Search\n\
                5.Edit\n\
                6.Erase\n\
                7.Rearrange\n\
                8.RandomValues\n\n");
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
                num_key = new_element("Search for: ");
                status = search(q, num_key);
                if (status != -1)
                    printf("Found %d on %d index\n", num_key, status);
                else
                    printf("Error 404: Not found!\n");
                break;

            case 5:
                num_key = generate("Edit value in index: ");
                status = edit(q, num_key);
                if (status == -1)
                    printf("Index out of the range!\n");
                break;

            case 6:
                num_key = generate("Erase element: ");
                status = erase(q, num_key);
                if (status != -1)
                    printf("Deleted %d on %d\n index", num_key, status);
                else
                    printf("Error 404: Not found!\n");
                break;

            case 7:
                rearrange(q);
                break;

            case 8:
                random_values(q);
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
