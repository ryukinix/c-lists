/* ==========================================================
 *
 *  -*- Some functions for manipulate meta-types  -*-
 *
 *===========================================================
 */

#include <stdbool.h>

void print_element(meta_data meta) {
    identifier type = meta.type;

    if (meta.data.integer != -1) {
        if (type == integer)
            printf(" (%d) ", meta.data.integer);
        else if (type == character)
            printf(" (%c) ", meta.data.character);
        else if (type == real)
            printf(" (%.2f) ", meta.data.real);
    } else {
        printf(" () ");
    }
}


void type_choose(meta_data *meta){
    int command;  
    
    puts("Insert the type that you wish attribute!");
    puts("1.Int\n2.Char\n3.Real\n");

    printf("Put a command: ");
    scanf("%d", &command);
    clear_buffer();

    switch(command){
        case 1:
            meta->type = integer;
            break;
        case 2:
            meta->type = character;
            break;
        case 3:
            meta->type = real;
            break;
        default:
            puts("Invalid option! Try again!");
            type_choose(meta);
            break;       
    }  
}

something new_thing(identifier type){
    printf("Insert a thing: ");
    something the_thing;

    if (type == integer)
        scanf("%d", &the_thing.integer);
    else if (type == character)
        scanf("%c", &the_thing.character);
    else if (type == real)
        scanf("%f", &the_thing.real);

    clear_buffer();

    return the_thing;
}

void new_meta(meta_data *meta){
    type_choose(meta);
    meta->data = new_thing(meta->type);
}

int union_comparision(something x, something y){
    if (x.integer == y.integer)
        return true;
    else if (x.character == y.character)
        return true;
    else if (x.real == y.real)
        return true;

    return false;
}

