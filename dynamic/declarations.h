/* ==========================================
 *
 *  -*- Declarations of all functions  -*-
 *
 * ==========================================
 */


// methods of list
int step(list *q);
int insert(list *q);
int search(list *q, something thing);
int erase(list *q, something thing);
int edit(list *q, int index);

// aux-functions
void type_choose(list *q);
void start(list *q);
void random_values(list *q);
void rearrange(list *q);
void del(list *q, int index);
void verify_state(list *q);

// in-out and terminal functions
int  generate(const char *message);
something new_thing(identifier type);
void insert_on(list *q, int index);
void print_element(meta_data element);
void print_list(list *q);
void menu(list *q);
void clear_buffer(void);
void pause(const char* msg);
