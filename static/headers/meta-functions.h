/* ==========================================================
 *
 *  -*- Some functions for manipulate meta-types  -*-
 *
 *===========================================================
 */

#include <stdbool.h>

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

int meta_comparision(meta_data x, meta_data y){
    if (x.data.integer == y.data.integer)
        return true;
    else if (x.data.character == y.data.character)
        return true;
    else if (x.data.real == y.data.real)
        return true;

    return false;
}

/* // conflicts with the definition in list-type
void type_choose(meta_data *element){
    int command;  
    
    puts("Insert the type that you wish attribute!");
    puts("1.Int\n2.Char\n3.Real\n");

    printf("Put a command: ");
    scanf("%d", &command);
    clear_buffer();

    switch(command){
        case 1:
            element->type = integer;
            break;
        case 2:
            element->type = character;
            break;
        case 3:
            element->type = real;
            break;
        default:
            puts("Invalid option! Try again!");
            type_choose(element);
            break;       
    }  
}
*/