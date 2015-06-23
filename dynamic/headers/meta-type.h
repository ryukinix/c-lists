/* ==========================================================
 *
 *  -*- All structures definition of meta type are below  -*-
 *
 *===========================================================
 */

typedef union {
    int integer;
    char character;
    float real;
} something;


typedef enum {
    integer,
    character,
    real,
} identifier;


typedef struct {
    something data;
    identifier type;
} meta_data;

