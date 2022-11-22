

#ifndef STACKTYPE_H
#define STACKTYPE_H

#include <stdlib.h>

#ifndef STACKELEMENT
#define STACKELEMENT int
#endif
typedef struct Stack_type{
    int top;
    int total;
    STACKELEMENT * data;
}StackType;

/**
 * @brief Create a stack object
 * 
 * @param n stack size
 * @return StackType* 
 */
StackType * create_stack(int n);

/**
 * @brief Check stack is empty
 * 
 * @param s stack
 * @return int stack size 
 */
int stack_is_empty(StackType * s);

/**
 * @brief Check stack is full
 * 
 * @param s stack
 * @return int stack size
 */
int stack_is_full(StackType * s);

/**
 * @brief Check top of the stack
 * 
 * @param s stack
 * @return STACKELEMENT 
 */
STACKELEMENT stack_peek(StackType * s);

/**
 * @brief add value to stack
 * 
 * @param s stack
 * @param node insert value
 * @return int insert state if insert is falled it return 0
 */
int stack_push(StackType * s,STACKELEMENT node);

/**
 * @brief pop value from stack
 * 
 * @param s stack
 * @param returnValue poped value
 * @return int pop state if pop is falled it return 0
 */
int stack_pop(StackType * s,STACKELEMENT * returnValue);
#endif


#ifdef STACKTYPE_IMPLEMENTATION

StackType * create_stack(int n){
    StackType * result = (StackType *)malloc(sizeof(StackType));
    result->data = (STACKELEMENT *)malloc(sizeof(STACKELEMENT) * n);
    result->top = -1;
    result->total = n;
    return result;
}

void destroy_stack(StackType * s){
    free(s->data);
    free(s);
}

int stack_is_empty(StackType * s){
    return s->top == -1;
}

int stack_is_full(StackType * s){
    return s->top == s->total;
}

int stack_push(StackType * s,STACKELEMENT node){
    if(stack_is_full(s)) return 0;
    s->data[++s->top] = node;
    return 1;
}

STACKELEMENT stack_peek(StackType * s){
    return s->data[s->top];
}

int stack_pop(StackType * s,STACKELEMENT * returnValue){
    if(stack_is_empty(s)) return 0;
    *returnValue = s->data[s->top--];
    return 1;
}

#endif