#ifndef STACK_H_
#define STACK_H_

#define elem_f "%d"

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
    NO_PTR,
    NO_DATA,
    WRONG_SIZE,
    NEGATIVE_SIZE,
    NEGATIVE_CAPACITY,
};

ERRORS Stack_ctor(Stack* stk, int capacity);

ERRORS Stack_dtor(Stack* stk);

ERRORS Stack_realloc(Stack* stk, int new_capacity);

ERRORS Stack_set_poison(Stack* stk);

ERRORS Stack_push(Stack* stk, elem_t value);

ERRORS Stack_pop(Stack* stk, elem_t* value);

ERRORS Stack_dump(Stack* stk);

ERRORS Stack_OK(Stack* stk);

#endif