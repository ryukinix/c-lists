/*
 * =====================================================================================
 *
 *                      Copyright 2015 Manoel Vilela
 *
 *
 *       Filename:  dynamic-deque.c
 *
 *    Description:  A deque dynamic for any type.
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
#define LIST_TYPE "Deque"

// my headers
#include "headers/clear-pause.h"
#include "headers/meta-type.h"
#include "headers/list-type.h"
#include "headers/meta-functions.h"
#include "headers/list-functions.h"


/* ================================================
 *
 *  -*- Definition of all main deque functions  -*-
 *
 * ================================================
 */



// pop the deque (remove the head)
int pop(list *deque) {
    if (deque->state == empty) {
        return -1;
    } else {
        printf("[pop] Pop head: ");
        print_element(deque->elements->meta);
        printf("\n");
        free(deque->elements);
        deque->elements = deque->elements->next;
        deque->size -= 1;
    }
    return 0;
}


// insert a value in a tail of deque;
void insert(list *deque) {
    // create a node if deque->elements is nil
    if (deque->elements == NULL) {
        node *first;
        start_node(&first);
        deque->elements = first;
        deque->elements->back = NULL;
        deque->size = 1;
        return;
    }

    node *old_tail = walk_to_tail(deque->elements);
    node *new_tail;
    start_node(&new_tail);
    new_tail->back = old_tail;
    old_tail->next = new_tail;
    deque->size += 1;
}


void menu(list *deque) {
    int command, status;
    meta_data element;

    do {
        system(CLEAR);
        verify_state(deque);
        puts("Implementation of a dynamic deque as a subclass of the list type!\n\n");
        printf("[subclass]: %s\n", deque->subclass);
        printf("[size]: %d\n", deque->size);
        printf("[status]: %s\n\n", state_strings[deque->state]);
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
                insert(deque);
                break;
            case 2:
                printf("== Pop ==\n");
                status = pop(deque);
                if (status == -1) puts("Empty deque!");
                break;
            case 3:
                printf("== Print ==\n");
                print_list(deque);
                break;
            case 4:
                printf("== Search ==\n");
                new_meta(&element);
                search(deque, element.data);
                break;
            case 5:
                printf("== Edit ==\n");
                new_meta(&element);
                edit(deque, element.data);
                break;
            case 6:
                printf("== Erase ==\n");
                new_meta(&element);
                erase(deque, element.data);
                break;
            case 7:
                printf("== Random ==\n");
                random_values(deque);
                break;
            case 8:
                printf("== ClearList ==\n");
                clear_list(deque);
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
    list deque;
    strcpy(deque.subclass, LIST_TYPE);

    start(&deque);
    menu(&deque);

    return 0;
}

