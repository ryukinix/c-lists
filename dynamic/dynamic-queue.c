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



// pop the queue (remove the head)
int pop(list *queue) {
    if (queue->state == empty) {
        return -1;
    } else {
        printf("Pop head: ");
        print_element(queue->elements->meta);
        printf("\n");
        free(queue->elements);
        queue->elements = queue->elements->next;
        queue->size -= 1;
    }
    return 0;
}


// insert a value in a tail of queue;
void insert(list *queue) {
    node *old_tail = walk_to_tail(queue->elements);
    node *new_tail = old_tail->next;
    start_node(new_tail);
    new_tail->back = old_tail;
    queue->size += 1;
}

void search(list *queue, something thing) {
    node *n = queue->elements;
    int index = 0;
    while (n != NULL) {
        if (union_comparision(n->meta.data, thing)){
            printf("On index %d was found: ", index);
            print_element(n->meta);
            printf("\n");
        }
        index++;
        n = walk_forward(n);
    }
}

void erase(list *queue, something thing) {    
    node *n = queue->elements;
    int index = 0;
    while (n != NULL) {
        if (union_comparision(n->meta.data, thing)){
            printf("On index %d was deleted: ", index);
            print_element(n->meta);
            printf("\n");
            remove_node(&n);
            queue->size -= 1;
        }
        index++;
        n = walk_forward(n);
    }
}

void edit(list *queue, int index) {
    node *n = queue->elements;

    n = walk_until(n, index);
    insert_node(n);

}


void menu(list *queue) {
    int command, status;

    do {
        system(CLEAR);
        verify_state(queue);
        puts("Implementation of a static queue as a subclass of the list type!\n\n");
        printf("[subclass]: %s\n", queue->subclass);
        printf("[size]: %d\n", queue->size);
        //printf("[head-type]: %s\n", type_strings[ (queue->elements->meta.type) ]);
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
                printf("== Insert ==\n");
                insert(queue);
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
                /*
                    Reformulate that code

                */

            case 5:
                printf("== Edit ==\n");
                /*
                    Reformulate that code

                */
                break;
            case 6:
                printf("== Erase ==\n");
                /*
                    Reformulate this code

                */
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

