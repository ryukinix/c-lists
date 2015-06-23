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

// standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// my headers
#include "clear-pause.h" 
#include "meta-type.h"
#include "list-type.h"
#include "declarations.h"
#include "meta-functions.h"
#include "list-functions.h"

// my macros
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
 *  -*-       THE BIG MAIN CODE           -*-
 *
 * ==========================================
 */

int main(void) {
    list q;

    start(&q);
    menu(&q);

    return 0;
}


/* ==========================================
 *
 *  -*- Definition of all main queue functions  -*-
 *
 * ==========================================
 */



// iniciar q
void start(list *q) {
    // get the size of list
    int size = generate("Enter a size: ");
    q->size = size;

    // alloc memory
    q->elements = (meta_data *) malloc(sizeof(meta_data) * size);
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


// generate a int number with a message for stdout
int generate(const char *message) {
    int num;
    puts(message);
    scanf("%d", &num);
    printf("\n");
    clear_buffer();

    return num;
}


// step the queue (remove the head)
int step(list *q) {
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
int insert(list *q) {
    if (q->state == full)
        return -1;

    q->last_index++;
    insert_on(q, q->last_index);

    return 0;
}

int search(list *q, something thing) {
    int i;

    for (i = 0; i < q->size; i++)
        if (q->elements[i].data.real == thing.real)
            return i;
    return -1;
}

int erase(list *q, something thing) {
    int index = search(q, thing);

    if (index != -1)
        del(q, index);
    else
        return -1;

    return index;
}

int edit(list *q, int index) {
    // verify if index is not do the pesar of violate the lenght of vector
    if (!(index >= 0 && index <= q->size))
        return -1;

    insert_on(q, index);

    return 0;
}


void menu(list *q) {
    int command, status;
    something element;

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
        clear_buffer();

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
                element = new_thing(q->elements[0].type);
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
                element = new_thing(q->elements[0].type);
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
