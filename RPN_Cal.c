#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_SIZE 256

// Stack structure
typedef struct {
    double items[MAX_STACK_SIZE];
    int top;
} Stack;

// Initialize the stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check if the stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Check if the stack is full
int isFull(Stack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}

// Push a value onto the stack
int push(Stack *s, double value) {
    if (isFull(s)) {
        fprintf(stderr, "Error: Stack overflow\n");
        return 0;
    }
    s->items[++s->top] = value;
    return 1;
}

// Pop a value from the stack
double pop(Stack *s, int *success) {
    if (isEmpty(s)) {
        fprintf(stderr, "Error: Stack underflow\n");
        *success = 0;
        return 0;
    }
    *success = 1;
    return s->items[s->top--];
}

// Peek at the top value of the stack without popping it
double peek(Stack *s, int *success) {
    if (isEmpty(s)) {
        fprintf(stderr, "Error: Stack underflow\n");
        *success = 0;
        return 0;
    }
    *success = 1;
    return s->items[s->top];
}

// Perform arithmetic operations
int performOperation(Stack *s, char op) {
    double a, b, result;
    int success;

    b = pop(s, &success);  // Pop the second operand
    if (!success) return 0;

    a = pop(s, &success);  // Pop the first operand
    if (!success) return 0;

    switch (op) {
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
            if (b == 0) {
                fprintf(stderr, "Error: Division by zero\n");
                return 0;
            }
            result = a / b;
            break;
        default:
            fprintf(stderr, "Error: Unknown operator '%c'\n", op);
            return 0;
    }

    return push(s, result);  // Push the result back onto the stack
}

// Process each instruction
int processInstruction(Stack *s, const char *instruction) {
    char *endPtr;
    double value;
    int success;

    while (*instruction) {
        while (isspace(*instruction)) {
            ++instruction;  // Skip whitespace
        }

        if (*instruction == '\0') {
            break;  // End of string
        }

        if (*instruction == '?') {  // Operand input
            ++instruction;
            value = strtod(instruction, &endPtr);
            if (instruction == endPtr) {
                fprintf(stderr, "Error: Invalid operand\n");
                return 0;
            }
            if (!push(s, value)) return 0;  // Push failed (stack overflow)
            instruction = endPtr;  // Move to the next part of the instruction
        } else if (strchr("+-*/", *instruction)) {  // Operators
            if (!performOperation(s, *instruction)) return 0;
            ++instruction;
        } else if (*instruction == '=') {  // Print result
            double result = peek(s, &success);
            if (!success) return 0;  // Error in peeking the stack
            printf("\nResult: %.2f\n", result);
            ++instruction;
        } else {
            fprintf(stderr, "Error: Invalid instruction '%c'\n", *instruction);
            return 0;
        }
    }
    return 1;  // Indicate success
}

int main() {
    Stack s;
    char instruction[MAX_INPUT_SIZE];
    char continueCalculation;

    printf("Welcome to the Reverse Polish Notation (RPN) Calculator!\n");

    do {
        initStack(&s);  // Initialize stack for a new calculation

        printf("\nEnter RPN instructions (use ? before numbers, and end with '=' to display result):\n");

        if (fgets(instruction, sizeof(instruction), stdin) == NULL) {
            fprintf(stderr, "Error: Unable to read input\n");
            continue;  // Ask for a new input
        }

        if (!processInstruction(&s, instruction)) {
            printf("\nAn error occurred during calculation.\n");
        }

        // Ask the user if they want to perform another calculation
        printf("\nDo you want to perform another calculation? (y/n): ");
        scanf(" %c", &continueCalculation);

        // Clear input buffer to avoid unintended input issues
        while (getchar() != '\n');

    } while (tolower(continueCalculation) == 'y');

    printf("Thank you for using the RPN Calculator. Goodbye!\n");

    return 0;
}
