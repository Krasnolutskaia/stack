#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "stack.h"


int main()
{
    Stack stk = {};
    Stack_ctor(&stk, 4);
    Stack_push(&stk, 10);
    Stack_dump(&stk);
    Stack_push(&stk, 18);
    Stack_dump(&stk);
    Stack_push(&stk, 5);
    Stack_dump(&stk);
    Stack_push(&stk, 15);
    Stack_dump(&stk);
    Stack_push(&stk, 100);
    Stack_dump(&stk);

    elem_t x = 0;
    Stack_pop(&stk, &x);
    Stack_dump(&stk);
    printf(elem_f "\n", x);
    Stack_pop(&stk, &x);
    printf(elem_f "\n", x);
    Stack_dump(&stk);
    Stack_dtor(&stk);
    return 0;
}
