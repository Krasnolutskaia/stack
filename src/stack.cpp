#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "stack.h"

const int DUMP_LEN = 3;

const int MIN_CAP = 4;

const elem_t POISON = 0xBADBABE;


ERRORS Stack_ctor(Stack* stk, int capacity)
{
    stk->data = (elem_t *) calloc(capacity, sizeof(elem_t));

    if (!stk->data)
    {
        printf("Stack_ctor(): no memory\n");
        free(stk->data);
        exit(EXIT_FAILURE);
    }

    stk->size = 0;
    stk->capacity = capacity;
    Stack_set_poison(stk);
    return OK;
}


ERRORS Stack_dtor(Stack* stk)
{
    free(stk->data);
    stk->data = NULL;
    stk->capacity = 0;
    stk->size = 0;
    printf("Stack dtor happened\n");
    return OK;
}


ERRORS Stack_realloc(Stack* stk, int new_capacity)
{
    stk->data = (elem_t *) realloc(stk->data, sizeof(elem_t) * new_capacity);
    if (!stk->data)
    {
        printf("Stack_realloc(): no memory\n");
        free(stk->data);
        exit(EXIT_FAILURE);
    } 
    memset(stk->data + stk->size - 1, '\0', stk->capacity - stk->size);
    stk->capacity = new_capacity;

    Stack_set_poison(stk);
    return OK;
}


ERRORS Stack_set_poison(Stack* stk)
{
    for (int i = stk->size - 1; i < stk->capacity; i++)
    {
        stk->data[i] = POISON;
    }
    return OK;
}


ERRORS Stack_push(Stack* stk, elem_t value)
{
    if (Stack_OK(stk) != OK)
    {
        Stack_dump(stk);
        return Stack_OK(stk);
    }

    if (stk->size == stk->capacity)
    {
        Stack_realloc(stk, stk->capacity * 2);
    }

    stk->data[stk->size++] = value;
    return OK;
}


ERRORS Stack_pop(Stack* stk, elem_t* value)
{
    if (Stack_OK(stk) != OK)
    {
        Stack_dump(stk);
        return Stack_OK(stk);
    }

    if ((stk->size - 1) * 2 <= stk->capacity && (stk->size - 1) >= MIN_CAP)
    {
        Stack_realloc(stk, stk->capacity / 2);
    }

    stk->size--;
    *value = stk->data[stk->size];
    stk->data[stk->size] = POISON;
    return OK;
}


ERRORS Stack_dump(Stack* stk)
{
    printf("Stack [0x%p]\n", &stk);
    printf("{\n");
    printf("\tsize = %d\n", stk->size);
    printf("\tcapacity = %d\n", stk->capacity);
    printf("\tdata [0x%p]\n", &stk->data);
    printf("\t{\n");

    for (int i = 0; i < stk->size + DUMP_LEN && i < stk->capacity; i++)
    {
        if (stk->data[i] != POISON)
        {
            printf("\t\t*[%d] = " elem_f "\n", i, stk->data[i]);
        }
        else
        {
            printf("\t\t [%d] = 0x%X (POISON)\n", i, stk->data[i]);
        }
    }

    printf("\t}\n");
    printf("}\n");
    return OK;
}


ERRORS Stack_OK(Stack* stk)
{
    if (!stk) return NO_PTR;
    if (!stk->data) return NO_DATA;
    if (stk->size > stk->capacity) return WRONG_SIZE;
    if (stk->size < 0) return NEGATIVE_SIZE;
    if (stk->capacity < 0) return NEGATIVE_CAPACITY;
    return OK;
}
