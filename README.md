# Matrix Operations in C++

This project implements a system for performing advanced matrix operations in C++. It includes support for common matrix operations such as transposition, inversion, scalar multiplication, matrix multiplication, and more. The project also supports parsing matrix expressions for complex calculations.

## Features

- Matrix Transposition: Easily transpose a matrix with the `^T` operator.
- Matrix Inversion: Calculate the inverse of a square matrix with the `^-1` operator.
- Matrix Multiplication: Perform matrix-to-matrix and scalar-to-matrix multiplication.
- Expression Parsing: Parse complex mathematical expressions involving matrices, scalars, and operations.
- Error Handling: Includes exception handling for invalid operations or input.

## Example Expression

The following example demonstrates a supported matrix operation expression:

```text
[1 2; 3 4]^3 * (4 * [1 2 3; 4 5 6] + [7 8; 9 1; 2 4]^T) - [1 3; 7 2]^-1 * [7 8 1; 1 2 3] * I3
