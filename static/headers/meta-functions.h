#ifndef META_FUNCTIONS_H
#define META_FUNCTIONS_H

/* ==========================================================
 *
 *  -*- Some functions for manipulate meta-types  -*-
 *
 *===========================================================
 */

#define true 1
#define false 0

#include "meta-type.h"
#include <stdio.h>

void print_element(meta_data element) {
    identifier type = element.type;

    if (element.data.integer != -1) {
        if (type == integer)
            printf(" (%d) ", element.data.integer);
        else if (type == character)
            printf(" (%c) ", element.data.character);
        else if (type == real)
            printf(" (%.2f) ", element.data.real);
    } else {
        printf(" () ");
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

int union_comparision(something x, something y){
    if (x.integer == y.integer)
        return true;
    else if (x.character == y.character)
        return true;
    else if (x.real == y.real)
        return true;

    return false;
}

#endif // META_FUNCTIONS_H
