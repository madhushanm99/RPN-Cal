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

void performOperation(Stack *s, char op)
{
    double a, b, result;

    switch (op)
    {
    case '+':
        b = pop(s);
        a = pop(s);
        result = a + b;
        push(s, result);
        break;
    case '-':
        b = pop(s);
        a = pop(s);
        result = a - b;
        push(s, result);
        break;
    case '*':
        b = pop(s);
        a = pop(s);
        result = a * b;
        push(s, result);
        break;
    case '/':
        b = pop(s);
        a = pop(s);
        if (b == 0)
        {
            fprintf(stderr, "Division by zero\n");
            exit(EXIT_FAILURE);
        }
        result = a / b;
        push(s, result);
        break;
    default:
        fprintf(stderr, "Unknown operator %c\n", op);
        exit(EXIT_FAILURE);
    }
}

void processInstruction(Stack *s, const char *instruction)
{
    while (*instruction)
    {
        if (isspace(*instruction))
        {
            ++instruction;
            continue;
        }

        if (*instruction == '?')
        {
            ++instruction;
            while (isspace(*instruction))
                ++instruction;
            double value = atof(instruction);
            push(s, value);
            while (isdigit(*instruction) || *instruction == '.' || *instruction == '-')
                ++instruction;
        }
        else if (*instruction == '+')
        {
            performOperation(s, '+');
            ++instruction;
        }
        else if (*instruction == '-')
        {
            performOperation(s, '-');
            ++instruction;
        }
        else if (*instruction == '*')
        {
            performOperation(s, '*');
            ++instruction;
        }
        else if (*instruction == '/')
        {
            performOperation(s, '/');
            ++instruction;
        }
        else if (*instruction == '=')
        {
            printf("Result: %.2f\n", peek(s));
            ++instruction;
        }
        else
        {
            fprintf(stderr, "Unknown instruction %c\n", *instruction);
            exit(EXIT_FAILURE);
        }
    }
}

int main()
{
    Stack s;
    initStack(&s);

    char instruction[256];

    printf("Enter RPN instructions:\n");
    while (fgets(instruction, sizeof(instruction), stdin))
    {
        processInstruction(&s, instruction);
    }

    return 0;
}