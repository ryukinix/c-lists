#include <stdio.h>

// clear the stdin
void clear_buffer(void) {
    char c;
    while (c = getchar() != '\n' && c != EOF )
        continue;
}

// arg for a string: print and pause.
void pause(const char* msg) {
    printf("%s", msg);
    clear_buffer();
}