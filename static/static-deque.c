/*
 * =====================================================================================
 *
 *                      Copyright 2015 Manoel Vilela
 *
 *
 *       Filename:  static-deque.c
 *
 *    Description:  A deque whose you can choose the type and your size.
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
#define LIST_TYPE "Deque"
#define LEFT 0
#define RIGHT 1
#define LEFT_RIGHT \
"1.Left\n\
2.Right\n"


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


// pop the deque (erase the head)
int pop_left(list *deque) {
    if (deque->state == empty) 
        return -1;
    else {

        printf("Pop head: ");
        print_element(deque->elements[0]);
        puts("");
        del(deque, 0);
    }

    return 0;
}

int pop_right(list *deque) {
     if (deque->state == empty) 
        return -1;
    else {
        printf("Pop tail: ");
        print_element(deque->elements[deque->last_index]);
        puts("");
        del(deque, deque->last_index);
    }

    return 0;
}


int pop(list *deque){
    int command;
    puts("]=== Pop ===[");
    printf(LEFT_RIGHT);

    scanf("%d", &command);
    clear_buffer();

    if (command == 1) {
        return pop_left(deque);
    }
    else if (command == 2) {
        return pop_right(deque);
    }
    else {
        pop(deque);
    }

    //temporary solution?
    return EXIT_SUCCESS;
}

void transpose(list *deque, int blocks) {
    int before, after;

    meta_data *temp;

    temp = (meta_data *) malloc(sizeof(deque->elements));

    //start temp
    for (before = 0; before < deque->size; before++) {
        temp->data.integer = -1;
    }
    
    //transpose to the temp
    for (before = 0; before < deque->size ; before++ ) {
        after = before + blocks;
        if (after >= 0 && after < deque->size)
            temp[after] = deque->elements[before];
    } 

    //copy the temp -> deque.elements
    for (after = 0; after < before - 1; after++ ) {
        deque->elements[after] = temp[after];
    }

}


// insert a value in a tail of deque;
int insert_right(list *deque) {
    if (deque->state == full) {
        return -1;
    }

    deque->last_index++;
    insert_on(deque, deque->last_index);

    return 0;
}

int insert_left(list *deque) {
    if (deque->state == full) {
        return -1;
    }

    deque->last_index++;
    transpose(deque, 1);
    insert_on(deque, 0);

    return 0;
}


int insert(list *deque) {
    int command;
    puts("]=== Insert ===[");
    printf(LEFT_RIGHT);

    scanf("%d", &command);
    clear_buffer();

    if (command == 1) {
        return insert_left(deque);
    }
    else if (command == 2) {
        return insert_right(deque); 
    }
    else { 
        // this else is error prone.
        insert(deque);
    }

    // temporary solution?
    return EXIT_SUCCESS;
}


int search(list *deque, something thing) {
    int i;

    for (i = 0; i < deque->size; i++)
        if (union_comparision(deque->elements[i].data, thing))
            return i;
    return -1;
}

/* erase is already defined in stdio.h
 */
int erase(list *deque, something thing) {
    int index = search(deque, thing);

    if (index != -1) {
        del(deque, index);
    }
    else {
        return -1;
    }

    return index;
}

int edit(list *deque, int index) {
    // verify if the index given violates the lenght of the vector.
    if (!(index >= 0 && index <= deque->size))
        return -1;

    insert_on(deque, index);

    return 0;
}


void menu(list *deque) {
    int command, status;
    something element;

    do {
        system(CLEAR);
        verify_state(deque);
        puts("Implementation of a static deque as a subclass of the list type!\n\n");
        printf("[subclass]: %s\n", deque->subclass);
        printf("[size]: %d\n", deque->size);
        printf("[head-type]: %s\n", type_strings[ (deque->elements[0].type) ]);
        printf("[status]: %s\n\n", state_strings[deque->state]);
        printf("\
                --> 0.Exit\n\n\
         ===[>Fundamental Methods<]===\n\n\
                1.Insert\n\
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
                status = insert(deque);
                if (status == -1) puts("Full deque!");
                break;

            case 2:
                status = pop(deque);
                if (status == -1) puts("Empty deque!");
                break;

            case 3:
                print_list(deque);
                break;

            case 4:
                printf("== Search ==\n");
                element = new_thing(deque->elements[0].type);
                status = search(deque, element);
                
                // output
                if (status != -1)
                    printf("Found on index %d!\n", status);
                else
                    printf("Error 404: Not found!\n");
                break;

            case 5:
                element.integer = generate("Edit value in index: ");
                status = edit(deque, element.integer);
                
                if (status == -1)
                    printf("Index out of the range!\n");
                
                break;

            case 6:
                printf("== erase element ==\n");
                element = new_thing(deque->elements[0].type);
                status = erase(deque, element);
                
                // output
                if (status != -1)
                    printf("Found on index %d! Deleted!\n", status);
                else
                    printf("Error 404: Not found!\n");
                break;

            case 7:
                rearrange(deque);
                break;

            case 8:
                random_values(deque);
                break;
            case 9:
                type_choose(deque);
                break;
            case 10:
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
    } while (command != 0);
}

int main(void) {
    list deque;
    strcpy(deque.subclass, LIST_TYPE);

    start(&deque);
    menu(&deque);

    return 0;
}

