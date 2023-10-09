#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "stack.h"

const int DEFAULT_CAP = 8;


ERRORS Stack_ctor(Stack* stk)
{
    stk->data = (elem_t *) calloc(DEFAULT_CAP, sizeof(elem_t));

    if (stk->data == NULL)
    {
        printf("no memory\n");
        free(stk->data);
        exit(EXIT_FAILURE);
    }

    stk->size = 0;
    stk->capacity = DEFAULT_CAP;
    return OK;
}


ERRORS Stack_dtor(Stack* stk)
{
    free(stk->data);
    stk->capacity = 0;
    stk->size = 0;
    return OK;
}


ERRORS Stack_realloc(Stack* stk, int new_capacity)
{
    stk->data = (elem_t *) realloc(stk->data, sizeof(elem_t) * new_capacity);
    if (stk->data == NULL)
    {
        printf("no memory\n");
        free(stk->data);
        exit(EXIT_FAILURE);
    } 
    memset(stk->data + stk->size - 1, '\0', stk->capacity - stk->size);
    stk->capacity = new_capacity;
    return OK;
}


ERRORS Stack_push(Stack* stk, elem_t value)
{
    if (stk->size == stk->capacity)
    {
        Stack_realloc(stk, stk->capacity * 2);
    }

    stk->data[stk->size++] = value;
    return OK;
}


ERRORS Stack_pop(Stack* stk, elem_t* value)
{
    if ((stk->size - 1) * 2 <= stk->capacity && (stk->size - 1) >= DEFAULT_CAP)
    {
        Stack_realloc(stk, stk->capacity / 2);
    }

    stk->size--;
    *value = stk->data[stk->size];
    stk->data[stk->size] = 0;
    return OK;
}


ERRORS Stack_dump(Stack* stk)
{
    printf("Stack [%p]\n", &stk);
    printf("{\n");
    printf("\tsize = %d\n", stk->size);
    printf("\tcapacity = %d\n", stk->capacity);
    printf("\tdata [%p]\n", &stk->data);
    printf("\t{\n");

    for (int i = 0; i < stk->size + 5 && i < stk->capacity; i++)
    {
        printf("\t\t[%d] = %d\n", i, stk->data[i]);
    }

    printf("\t}\n");
    printf("}\n");
    return OK;
}
