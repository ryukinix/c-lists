/*
 * =====================================================================================
 *
 *                      Copyright 2015 Manoel Vilela
 *
 *
 *       Filename:  dynamic-stack.c
 *
 *    Description:  A stack dynamic for any type.
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
#define LIST_TYPE "Stack"

// my headers
#include "headers/clear-pause.h"
#include "headers/meta-type.h"
#include "headers/list-type.h"
#include "headers/meta-functions.h"
#include "headers/list-functions.h"


/* ================================================
 *
 *  -*- Definition of all main stack functions  -*-
 *
 * ================================================
 */


// pop the stack (remove the tail)
int pop(list *stack) {
    if (stack->state == empty)
        return -1;
    
    // printf("[pop] Pop tail: ");
    // print_element((*some_node)->meta);
    // printf("\n");

    printf("A lot of bugs!\n");
    /*===========================================================
     *
     *  -*-  rebuild this function: correct remove tails   -*-
     *
     *===========================================================
     */

    
    return 0;
}


// insert a value in a tail of stack;
void insert(list *stack) {
    // create a node if stack->elements is nil
    if (stack->elements == NULL) {
        node *first;
        start_node(&first);
        stack->elements = first;
        stack->elements->back = NULL;
        stack->size = 1;
        return;
    }

    node *new_tail;
    start_node(&new_tail);
    node *old_tail = walk_to_tail(stack->elements);
    new_tail->back = old_tail;
    old_tail->next = new_tail;
    stack->size += 1;
}


void menu(list *stack) {
    int command, status;
    meta_data element;

    do {
        system(CLEAR);
        verify_state(stack);
        puts("Implementation of a dynamic stack as a subclass of the list type!\n\n");
        printf("[subclass]: %s\n", stack->subclass);
        printf("[size]: %d\n", stack->size);
        printf("[status]: %s\n\n", state_strings[stack->state]);
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
                insert(stack);
                break;
            case 2:
                printf("== Pop ==\n");
                status = pop(stack);
                if (status == -1) puts("Empty stack!");
                break;
            case 3:
                printf("== Print ==\n");
                print_list(stack);
                break;
            case 4:
                printf("== Search ==\n");
                new_meta(&element);
                search(stack, element.data);
                break;
            case 5:
                printf("== Edit ==\n");
                new_meta(&element);
                edit(stack, element.data);
                break;
            case 6:
                printf("== Erase ==\n");
                new_meta(&element);
                erase(stack, element.data);
                break;
            case 7:
                printf("== Random ==\n");
                random_values(stack);
                break;
            case 8:
                printf("== ClearList ==\n");
                clear_list(stack);
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
    list stack;
    strcpy(stack.subclass, LIST_TYPE);

    start(&stack);
    menu(&stack);

    return 0;
}

