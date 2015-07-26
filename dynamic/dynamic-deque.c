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

// (remove the head)
void pop_left(node **head) {
    printf("[pop] Pop head: ");
    print_element((*head)->meta);
    printf("\n");
    *head = remove_node(*head);
}
// (remove the tail)
void pop_right(node **some_node) {
    node **tail = tail_pointer(some_node);
    printf("[pop] Pop tail: ");
    print_element((*tail)->meta);
    printf("\n");
    *tail = remove_node(*tail);
}

// pop the deque (remove left or right)
int pop(list *deque) {
    if (deque->state == empty) 
        return -1;
    
    int orientation;
    puts("Choose the orientation of pop!");
    printf("0. Left\n1. Right\n");
    printf("Put a command: ");
    scanf("%d", &orientation);
    clear_buffer();

    if (orientation)
        pop_right(&(deque->elements));
    else
        pop_left(&(deque->elements));
    
    return 0;
}


// insert a value before the head (i think this function dont't work)
node* insert_left(node *head, meta_data element) {
    //start a new node
    node *new_head;
    start_node(&new_head);
    
    //attribute the element in node
    new_head->meta = element;
    new_head->next = head;

    //attribute the back-pointer of the head new_head
    //new_head -> head -> end_of_list (...)
    if (head != NULL)
        head->back = new_head;

    //return the new_head
    return new_head;
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



// insert a value in a tail of deque;
void insert(list *deque) {
    int orientation;
    puts("Choose the orientation of insertion!");
    printf("0. Left\n1. Right\n");
    printf("Put a command: ");
    scanf("%d", &orientation);
    clear_buffer();

    meta_data data;
    new_meta(&data);

    
    if (orientation)
        deque->elements = insert_right(deque->elements, data);
    else
        deque->elements = insert_left(deque->elements, data);

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
    } while(command != 0);
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

