/*
 * =====================================================================================
 *
 *                      Copyright 2015 Manoel Vilela
 *
 *
 *       Filename:  static-stack.c
 *
 *    Description:  A stack whose you can choose the type and your size
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


// generate a int number with a message for stdout
int generate(const char *message) {
    int num;
    puts(message);
    scanf("%d", &num);
    printf("\n");
    clear_buffer();

    return num;
}


// pop the stack (remove the head)
int pop(list *stack) {
    if (stack->state == empty) {
        return -1;
    } else {
        printf("Pop tail: ");
        print_element(stack->elements[stack->last_index]);
        puts("");
        del(stack, stack->last_index);
    }

    return 0;
}


// insert a value in a tail of stack;
int insert(list *stack) {
    if (stack->state == full)
        return -1;

    stack->last_index++;
    insert_on(stack, stack->last_index);

    return 0;
}

int search(list *stack, something thing) {
    int i;

    for (i = 0; i < stack->size; i++)
        if (union_comparision(stack->elements[i].data, thing))
            return i;
    return -1;
}

int erase(list *stack, something thing) {
    int index = search(stack, thing);

    if (index != -1)
        del(stack, index);
    else
        return -1;

    return index;
}

int edit(list *stack, int index) {
    // verify if index is not do the pesar of violate the lenght of vector
    if (!(index >= 0 && index <= stack->size))
        return -1;

    insert_on(stack, index);

    return 0;
}


void menu(list *stack) {
    int command, status;
    something element;

    do {
        system(CLEAR);
        verify_state(stack);
        puts("Implementation of type stack in the class list!\n\n");
        printf("[subclass]: %s\n", stack->subclass);
        printf("[size]: %d\n", stack->size);
        printf("[head-type]: %s\n", type_strings[ (stack->elements[0].type) ]);
        printf("[status]: %s\n\n", state_strings[stack->state]);
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
                status = insert(stack);
                if (status == -1) puts("Full stack!");
                break;

            case 2:
                status = pop(stack);
                if (status == -1) puts("Empty stack!");
                break;

            case 3:
                print_list(stack);
                break;

            case 4:
                printf("== Search ==\n");
                element = new_thing(stack->elements[0].type);
                status = search(stack, element);
                
                // output
                if (status != -1)
                    printf("Found on index %d!\n", status);
                else
                    printf("Error 404: Not found!\n");
                break;

            case 5:
                element.integer = generate("Edit value in index: ");
                status = edit(stack, element.integer);
                
                if (status == -1)
                    printf("Index out of the range!\n");
                
                break;

            case 6:
                printf("== Erase element ==\n");
                element = new_thing(stack->elements[0].type);
                status = erase(stack, element);
                
                // output
                if (status != -1)
                    printf("Found on index %d! Deleted!\n", status);
                else
                    printf("Error 404: Not found!\n");
                break;

            case 7:
                rearrange(stack);
                break;

            case 8:
                random_values(stack);
                break;
            case 9:
                type_choose(stack);
                break;
            case 10:
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

