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
void pop_right(node **some_node) {
    node **tail = tail_pointer(some_node);
    printf("[pop] Pop tail: ");
    print_element((*tail)->meta);
    printf("\n");
    *tail = remove_node(*tail);
}

int pop(list *stack){
    if (stack->size == empty)
        return -1;
    pop_right(&(stack->elements));
    stack->size -= 1;
    return 0;
}


// insert a new node after the tail
node* insert_right(node *some_node, meta_data element) {
    //if some_node not points to nil, try insert in next node recursively
    if (some_node != NULL) {
        node *new_node = insert_right(some_node->next, element);
        new_node->back = some_node; 
        some_node->next = new_node;
    }
    //if some_node points to nil, alloc, attribue and points next to nil
    else {
        start_node(&some_node);
        some_node->meta = element;
    }
    //return the some_node (should be a new 'node' or no)
    return some_node;
}

void insert(list *queue, meta_data element){
    queue->elements = insert_right(queue->elements, element);
    queue->size += 1;
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
                new_meta(&element);
                insert(stack, element);
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

