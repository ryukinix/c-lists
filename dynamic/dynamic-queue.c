/*
 * =====================================================================================
 *
 *                      Copyright 2015 Manoel Vilela
 *
 *
 *       Filename:  dynamic-queue.c
 *
 *    Description:  A queue dynamic for any type
 *
 *         Author:  Manoel Vilela
 *        Contact:  manoel_vilela@engineer.com
 *   Organization:  UFPA
 *
 * =====================================================================================
 */

// standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// my macros
#define LIST_TYPE "Queue"

// my headers
#include "headers/clear-pause.h" 
#include "headers/meta-type.h"
#include "headers/list-type.h"
#include "headers/meta-functions.h"
#include "headers/list-functions.h"


/* ================================================
 *
 *  -*- Definition of all main queue functions  -*-
 *
 * ================================================
 */



// pop the queue (remove the head)
int pop(list *queue) {
    if (queue->state == empty) {
        return -1;
    } else {
        printf("Pop head: ");
        print_element(queue->elements->meta);
        puts("");
        del(queue, 0);
    }

    return 0;
}


// insert a value in a tail of queue;
int insert(list *queue) {
    /*
        Reformulate that code

    */

    return 0;
}

int search(list *queue, something thing) {
    /*
        Reformulate that code

    */

    return -1;
}

int erase(list *queue, something thing) {    
    /*
        Reformulate that code

    */

    return index;
}

int edit(list *queue, int index) {
    /*
        Reformulate that code

    */

    return 0;
}


void menu(list *queue) {
    int command, status;
    something element;

    do {
        system(CLEAR);
        verify_state(queue);
        puts("Implementation of a static queue as a subclass of the list type!\n\n");
        printf("[subclass]: %s\n", queue->subclass);
        printf("[size]: %d\n", queue->size);
        printf("[head-type]: %s\n", type_strings[ (queue->elements->meta.type) ]);
        printf("[status]: %s\n\n", state_strings[queue->state]);
        printf("\
                --> 0.Exit\n\n\
         ===[>Fundamental Methods<]===\n\n\
                1.Insert\n\
                2.Pop\n\
                3.Print\n\
                4.Search\n\
                5.Edit\n\
                6.Erase\n\
                7.RandomValues\n\
                8.ClearList\n\n");
        printf("Type a command: ");
        scanf("%d", &command);
        clear_buffer();

        switch (command) {
            case 1:
                status = insert(queue);
                if (status == -1) puts("Full queue!");
                break;

            case 2:
                status = pop(queue);
                if (status == -1) puts("Empty queue!");
                break;

            case 3:
                print_list(queue);
                break;

            case 4:
                printf("== Search ==\n");
                /*
                    Reformulate that code

                */

            case 5:
                element.integer = generate("Edit value in index: ");
                /*
                    Reformulate that code

                */
                break;
            case 6:
                printf("== Erase element ==\n");
                /*
                    Reformulate that code

                */
                break;
            case 7:
                random_values(queue);
                break;
            case 8:
                clear_list(queue);
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


/* ==========================================
 *
 *  -*-       THE BIG MAIN CODE           -*-
 *
 * ==========================================
 */

int main(void) {
    list queue;
    strcpy(queue.subclass, LIST_TYPE);

    start(&queue);
    menu(&queue);

    return 0;
}

