/* =============================================
 *
 *  -*- Definition of all basic functions list  -*-
 *
 * =============================================
 */



//print the list
void print_list(list *q) {
    int i;
    identifier type = q->elements[0].type;

    printf("%s: [ ", q->subclass);
    for (i = 0; i < q->size; i++)
        print_element(q->elements[i]);
    printf("]\n");
}


//insert on index
void insert_on(list *q, int index) {
    something the_thing = new_thing(q->elements[0].type);
    q->elements[index].data = the_thing;
}


// delete some element
void del(list *q, int index) {
    q->elements[index].data.integer = -1;
    rearrange(q);
}

// rearrange the list
void rearrange(list *q) {
    // ignoring empty blocks and rearrange the vector
    int i, j;
    for (i = 0, j = 0; i < q->size; i++) {
        if (q->elements[i].data.integer != -1) {
            q->elements[j] = q->elements[i];
            j++;
        }
    }

    // assigning the garbage in right of vector as empty
    for (i = j; i < q->size; i++) {
        q->elements[i].data.integer = -1;
    }

    q->last_index = j - 1;
}


//verify the state of list
void verify_state(list *q) {
    if (q->last_index == -1)
        q->state = empty;
    else if (q->last_index >= q->size - 1)
        q->state = full;
    else
        q->state = available;
}

//choose the type of the list
void type_choose(list *q) {
    int command, i;
    puts("Choose a type for the list");
    printf("1.Int\n2.Char\n3.Float\n\n");
    printf("Enter a command: ");
    scanf("%d", &command);
    clear_buffer();

    for (i= 0; i < q->size; i++) {
        //that verification it will usefull on the type change
        if (q->elements[i].data.integer == -1){
            if (command == 1)
               q->elements[i].type = integer;
            else if (command == 2)
               q->elements[i].type = character;
            else if (command == 3)
               q->elements[i].type = real;
            else        
               type_choose(q);
        }
    }
}

//insert random values all on the list
void random_values(list *q) {
    int i;
    time_t t;
    srand((unsigned) time(&t));

    for (i = 0; i < q->size; i++) {
        identifier type = q->elements[i].type;
        if (type == integer)
            q->elements[i].data.integer = rand() % 100;
        else if (type == character)
            q->elements[i].data.character = 'a' + rand() % 26;
        else if (type == real)
            q->elements[i].data.real = (rand() % 100) / (rand () % 100);
    }
    
    q->last_index = i + 1;
}

