#ifndef CLEAR_PAUSE_H
#define CLEAR_PAUSE_H

#define CLEAR "clear || cls"

// clear the stdin
void clear_buffer(void) {
    char c;
    while ((c = getchar() != '\n') && (c != EOF))
        continue;
}

// arg for a string: print and pause.
void pause(const char* msg) {
    printf("%s", msg);
    clear_buffer();
}

// message to exit
void get_out(){
    printf("There is no necessary memory available.\n");
    exit(EXIT_FAILURE);
}

#endif //CLEAR_PAUSE_H