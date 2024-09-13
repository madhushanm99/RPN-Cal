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

int main()
{
    Stack s;
    initStack(&s);

    push(&s, 10.0);
    push(&s, 20.0);
    push(&s, 30.0);

    printf("Top of stack: %.2f\n", peek(&s));

    printf("Popped value: %.2f\n", pop(&s));
    printf("Popped value: %.2f\n", pop(&s));

    if (isEmpty(&s))
    {
        printf("Stack is empty\n");
    }
    else
    {
        printf("Stack is not empty\n");
    }

    printf("Popped value: %.2f\n", pop(&s));

    if (isEmpty(&s))
    {
        printf("Stack is empty\n");
    }
    else
    {
        printf("Stack is not empty\n");
    }

    return 0;

}