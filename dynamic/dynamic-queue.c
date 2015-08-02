/*
 * =====================================================================================
 *
 *                      Copyright 2015 Manoel Vilela
 *
 *
 *       Filename:  dynamic-queue.c
 *
 *    Description:  A queue dynamic for any type.
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


int pop(list *queue){
    node **some_node = &(queue->elements);
    if (queue->state == empty) 
        return -1;
    else {
        pop_left(some_node);
        queue->size -= 1;
    }

    return 0;
}

void push(list *queue, meta_data element){
    queue->elements = push_right(queue->elements, element);
    queue->size += 1;
}

void menu(list *queue) {
    int command, status;
    meta_data element;

    do {
        system(CLEAR);
        verify_state(queue);
        puts("Implementation of a dynamic queue as a subclass of the list type!\n\n");
        printf("[subclass]: %s\n", queue->subclass);
        printf("[size]: %d\n", queue->size);
        printf("[status]: %s\n\n", state_strings[queue->state]);
        printf("\
                --> 0.Exit\n\n\
         ===[>Fundamental Methods<]===\n\n\
                1.Push\n\
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
                printf("== push ==\n");
                new_meta(&element);
                push(queue, element);
                break;
            case 2:
                printf("== Pop ==\n");
                status = pop(queue);
                if (status == -1) puts("Empty queue!");
                break;
            case 3:
                printf("== Print ==\n");
                print_list(queue);
                break;
            case 4:
                printf("== Search ==\n");
                new_meta(&element);
                search(queue, element.data);
                break;
            case 5:
                printf("== Edit ==\n");
                new_meta(&element);
                edit(queue, element.data);
                break;
            case 6:
                printf("== Erase ==\n");
                new_meta(&element);
                erase(queue, element.data);
                break;
            case 7:
                printf("== Random ==\n");
                random_values(queue);
                break;
            case 8:
                printf("== ClearList ==\n");
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

