#ifndef META_TYPE_H
#define META_TYPE_H
/**==========================================================
 *
 *  -*- All structures definition of meta type are below  -*-
 *  
 *    
 *      -> The meta_data structure is the more abstract
 *  piece on this code. It is can be used for be some 
 *  type between int, char and float.
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

#endif //META_TYPE_H