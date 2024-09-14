#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_SIZE 256

// Stack structure
typedef struct
{
    double items[MAX_STACK_SIZE];
    int top;
} Stack;

// Initialize the stack
void initStack(Stack *s)
{
    s->top = -1;
}

// Check if the stack is empty
int isEmpty(Stack *s)
{
    return s->top == -1;
}
// Check if the stack is full
int isFull(Stack *s)
{
    return s->top == MAX_STACK_SIZE - 1;
}

// Push a value onto the stack
void push(Stack *s, double value)
{
    if (isFull(s))
    {
        fprintf(stderr, "Error: Stack overflow(Full)\n");
        exit(EXIT_FAILURE);
    }
    s->items[++s->top] = value;
}

// Pop a value from the stack
double pop(Stack *s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "Error: Stack underflow(Empty)\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top--];
}

// Peek at the top value of the stack without popping it
double peek(Stack *s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "Error: Stack underflow(Empty)\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top];
}

// Perform arithmetic operations
void performOperation(Stack *s, char op)
{
    double a, b, result;

    if (isEmpty(s))
    {
        fprintf(stderr, "Error: Not enough operands for operation '%c'\n", op);
        exit(EXIT_FAILURE);
    }

    b = pop(s); // Pop the second operand

    if (isEmpty(s))
    {
        fprintf(stderr, "Error: Not enough operands for operation '%c'\n", op);
        exit(EXIT_FAILURE);
    }

    a = pop(s); // Pop the first operand

    switch (op)
    {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        if (b == 0)
        {
            fprintf(stderr, "Error: Division by zero\n");
            exit(EXIT_FAILURE);
        }
        result = a / b;
        break;
    default:
        fprintf(stderr, "Error: Unknown operator '%c'\n", op);
        exit(EXIT_FAILURE);
    }

    push(s, result); // Push the result back onto the stack
}

// Process each instruction
void processInstruction(Stack *s, const char *instruction)
{
    char *endPtr;
    double value;

    while (*instruction)
    {
        while (isspace(*instruction))
        {
            ++instruction; // Skip whitespace
        }

        if (*instruction == '\0')
        {
            break; // End of string
        }

        if (*instruction == '?') // Operand input
        {
            ++instruction;
            value = strtod(instruction, &endPtr);
            if (instruction == endPtr)
            {
                fprintf(stderr, "Error: Invalid operand\n");
                exit(EXIT_FAILURE);
            }
            push(s, value);
            instruction = endPtr; // Move to the next part of the instruction
        }
        else if (strchr("+-*/", *instruction)) // Operators
        {
            performOperation(s, *instruction);
            ++instruction;
        }
        else if (*instruction == '=') // Print result
        {
            printf("Result: %.2f\n", peek(s));
            ++instruction;
        }
        else
        {
            fprintf(stderr, "Error: Invalid instruction '%c'\n", *instruction);
            exit(EXIT_FAILURE);
        }
    }
}

int main()
{
    Stack s;
    char instruction[MAX_INPUT_SIZE];
    char continueCalculation;

    printf("Welcome to the Reverse Polish Notation (RPN) Calculator!\n");


    do {
        initStack(&s);  // Initialize stack for a new calculation

        printf("\nEnter RPN instructions (use ? before numbers, and end with '=' to display result):\n");

        if (fgets(instruction, sizeof(instruction), stdin) == NULL) {
            fprintf(stderr, "Error: Unable to read input\n");
            exit(EXIT_FAILURE);
        }

        processInstruction(&s, instruction);

        // Ask the user if they want to perform another calculation
        printf("\nDo you want to perform another calculation? (y/n): ");
        scanf(" %c", &continueCalculation);

        // Clear input buffer to avoid unintended input issues
        while (getchar() != '\n');

    } while (tolower(continueCalculation) == 'y');

    printf("Thank you for using the RPN Calculator. Goodbye!\n");

    return 0;
}