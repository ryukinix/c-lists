/*
 * =====================================================================================
 *
 *                      Copyright 2015 Manoel Vilela
 *
 *
 *       Filename:  static-queue.c
 *
 *    Description:  A queue whose you can choose the type and your size.
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
#define CLEAR "clear || cls"
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


// pop the queue (erase the head)
int pop(list *queue) {
    if (queue->state == empty) {
        return -1;
    } else {
        printf("Pop head: ");
        print_element(queue->elements[0]);
        puts("");
        del(queue, 0);
    }

    return 0;
}


// push a value in a tail of queue;
int push(list *queue) {
    if (queue->state == full)
        return -1;

    queue->last_index++;
    insert(queue, queue->last_index);

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
        printf("[head-type]: %s\n", type_strings[ (queue->elements[0].type) ]);
        printf("[status]: %s\n\n", state_strings[queue->state]);
        printf("\
                --> 0.Exit\n\n\
         ===[>Fundamental Methods<]===\n\n\
                1.Push\n\
                2.Pop\n\
                3.Print_list\n\
                4.Search\n\
                5.Edit\n\
                6.Erase\n\
                7.Rearrange\n\
                8.RandomValues\n\
                9.TypeChange\n\
                10.ClearList\n\n");
        printf("Type a command: ");
        scanf("%d", &command);
        clear_buffer();

        switch (command) {
            case 1:
                status = push(queue);
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
                element = new_thing(queue->elements[0].type);
                status = search(queue, element);
                
                // output
                if (status != -1)
                    printf("Found on index %d!\n", status);
                else
                    printf("Error 404: Not found!\n");
                break;

            case 5:
                element.integer = generate("Edit value in index: ");
                status = edit(queue, element.integer);
                
                if (status == -1)
                    printf("Index out of the range!\n");
                
                break;

            case 6:
                printf("== erase element ==\n");
                element = new_thing(queue->elements[0].type);
                status = erase(queue, element);
                
                // output
                if (status != -1)
                    printf("Found on index %d! Deleted!\n", status);
                else
                    printf("Error 404: Not found!\n");
                break;

            case 7:
                rearrange(queue);
                break;

            case 8:
                random_values(queue);
                break;
            case 9:
                type_choose(queue);
                break;
            case 10:
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

