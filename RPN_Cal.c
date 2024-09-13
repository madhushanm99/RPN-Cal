#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

typedef struct
{
    double items[MAX_STACK_SIZE];
    int top;
} Stack;

void initStack(Stack *s)
{
    s->top = -1;
}

int isEmpty(Stack *s)
{
    return s->top == -1;
}

int isFull(Stack *s)
{
    return s->top == MAX_STACK_SIZE - 1;
}

void push(Stack *s, double value)
{
    if (isFull(s))
    {
        fprintf(stderr, "Stack is full\n");
        exit(EXIT_FAILURE);
    }
    s->items[++s->top] = value;
}

double pop(Stack *s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top--];
}

double peek(Stack *s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top];
}