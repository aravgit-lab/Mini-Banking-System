# Mini Banking System

A beginner-friendly, menu-driven banking application developed using C programming.

## Features

- Check account balance
- Deposit money
- Withdraw money
- View transaction history
- Store account balance permanently using file handling
- Save transaction records in a separate file
- Input validation and basic error handling

## Technologies Used

- C Programming
- File Handling (`fopen`, `fprintf`, `fscanf`, `fgets`, `fclose`)
- Functions and Pointers
- Loops, Conditional Statements and Switch Case
- GCC Compiler

## How to Run

1. Clone or download this repository.
2. Open the project folder in VS Code.
3. Open the terminal.
4. Compile the program:

   `gcc -mconsole main.c -o banking.exe`

5. Run the program:

   `.\banking.exe`

## Initial Balance

The application starts with an initial balance of Rs. 10,000 when no valid balance file exists.

## Project Files

- `main.c` – Main C source code.
- `balance.txt` – Stores the current account balance (created at runtime).
- `transactions.txt` – Stores transaction history (created at runtime).

## Note

This is an educational project developed to practise C programming concepts. It is a console-based simulation and is not intended for real financial transactions.

## Author

Developed as a beginner C programming project.