#ifndef STACK_H_
#define STACK_H_


typedef int elem_t;

struct Stack 
{
    elem_t * data;
    int size;
    int capacity;
};

enum ERRORS 
{
    OK,
    NO_MEMORY,
};

ERRORS Stack_ctor(Stack* stk);

ERRORS Stack_dtor(Stack* stk);

ERRORS Stack_realloc(Stack* stk, int new_capacity);

ERRORS Stack_push(Stack* stk, elem_t value);

ERRORS Stack_pop(Stack* stk, elem_t* value);

ERRORS Stack_dump(Stack* stk);

#endif