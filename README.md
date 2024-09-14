# Reverse Polish Notation (RPN) Calculator

## Introduction

The Reverse Polish Notation (RPN) Calculator is a command-line tool that allows you to evaluate mathematical expressions using RPN, where operators follow their operands. This method eliminates the need for parentheses, enabling quick and straightforward calculations. The calculator supports basic arithmetic operations: addition, subtraction, multiplication, and division.

## Features

- *Simple to Use*: Enter numbers and operators in RPN format, and the calculator processes the expression.
- *Stack-Based Operations*: Uses a stack data structure to handle operations efficiently.
- *Error Handling*: Provides informative error messages for invalid inputs, stack underflow/overflow, and division by zero.
- *User-Friendly Interface*: Continuously prompts for new calculations and displays results clearly.

## Getting Started

### Prerequisites

- C Compiler (e.g., gcc for Linux/Unix or MinGW for Windows)

### Installation

1. *Clone the Repository*:

    sh
    git clone https://github.com/your-username/rpn-calculator.git
    

2. *Navigate to the Project Directory*:

    sh
    cd rpn-calculator
    

3. *Compile the Source Code*:

    sh
    gcc -o rpn_calculator rpn_calculator.c
    

## Usage

1. *Run the Program*:

    sh
    ./rpn_calculator
    

2. *Enter Instructions*:

    - Use ? followed by a number to push an operand onto the stack.
    - Enter operators (+, -, *, /) to perform calculations.
    - Use = to display the result of the current stack top.

    *Example*:

    sh
    ? 5 ? 8 + ? 3 * =
    

    This will calculate (5 + 8) * 3 and display the result.

3. *Exit the Program*:

    - After displaying the result, the program will prompt if you want to perform another calculation.
    - Enter n to exit or y to continue with another calculation.

## Key Points

- *Stack Operations*: The calculator uses a stack to manage operands and results. Operands are pushed onto the stack, and operators pop the necessary operands, perform the operation, and push the result back onto the stack.
- *Error Handling*:
  - *Stack Overflow*: Ensures the stack doesn't exceed its maximum size.
  - *Stack Underflow*: Checks if there are enough operands for operations.
  - *Division by Zero*: Prevents division by zero with appropriate error messages.
  - *Invalid Instructions*: Catches invalid characters or incorrect syntax.
- *Looping Calculations*: Allows users to perform multiple calculations in a single session without restarting the program.

## Test Cases

### 1. Basic Operations

- *Input*: ? 5 ? 3 + =
- *Expected Output*: Result: 8.00

### 2. Complex Expression

- *Input*: ? 5 ? 8 + ? 3 ? 2 - * =
- *Expected Output*: Result: 39.00

### 3. Division by Zero

- *Input*: ? 10 ? 0 / =
- *Expected Output*: Error: Division by zero

### 4. Stack Underflow

- *Input*: ? 5 + =
- *Expected Output*: Error: Not enough operands for operation '+'

### 5. Invalid Operand

- *Input*: ? 5 ? a + =
- *Expected Output*: Error: Invalid operand

### 6. Nested Operations

- *Input*: ? 5 ? 1 + ? 2 * ? 4 / =
- *Expected Output*: Result: 3.00

### 7. Continue After Error

- *Scenario*: Enter an invalid expression to trigger an error, then perform a valid calculation.
  - *Invalid Input*: ? 5 + + =
  - *Expected Output*: Error: Invalid instruction '+'
  - *Follow-Up Input*: ? 7 ? 3 - =
  - *Expected Output*: Result: 4.00


## Acknowledgments

- Inspired by the simplicity and power of Reverse Polish Notation for mathematical computations.