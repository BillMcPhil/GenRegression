#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to generate a random matrix
void generateMatrix(int rows, int cols, double matrix[rows][cols])
{
    // Double for loop to generate a 2D matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // Generates a random float between 1 and 10 and then multiplies it by -1 raised to either 0 or 1,
            // to give a random float between -10 and 10 inclusive.
            matrix[i][j] = ((double)rand() / (double)(RAND_MAX / 10)) * (pow(-1, rand() % 2));
        }
    }
}

// Function to print a matrix
void printMatrix(int rows, int cols, double matrix[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // The negative symbol gives an extra character, so this just evens out the spacing
            if (matrix[i][j] >= 0)
            {
                printf(" %f ", matrix[i][j]);
            }

            else
            {
                printf("%f ", matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Function to add two matrices
void addMatrices(int rowsA, int colsA, double matrixA[rowsA][colsA], int rowsB, int colsB, double matrixB[rowsB][colsB], double matrixC[rowsA][colsA])
{
    // Makes sure the matrices are of equal size
    if (rowsA != rowsB || colsA != colsB)
    {
        printf("Incompatible matrix sizes.\n");
    }

    else
    {
        // Just loop through the matrix and add each value together
        for (int i = 0; i < rowsA; ++i)
        {
            for (int j = 0; j < colsA; ++j)
            {
                matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
            }
        }
    }
}

// Function to subtract matrices
void subtractMatrices(int rowsA, int colsA, double matrixA[rowsA][colsA], int rowsB, int colsB, double matrixB[rowsB][colsB], double matrixC[rowsA][colsA])
{
    // Ensure matrices are of the same dimensions
    if (rowsA != rowsB || colsA != colsB)
    {
        printf("Incompatible matrix sizes.\n");
    }

    else
    {
        // Simply loop through each matrix and subtract their corresponding values
        for (int i = 0; i < rowsA; ++i)
        {
            for (int j = 0; j < colsA; ++j)
            {
                matrixC[i][j] = matrixA[i][j] - matrixB[i][j];
            }
        }
    }
}

// Function to multiply matrices
void multiplyMatrices(int rowsA, int colsA, double matrixA[rowsA][colsA], int rowsB, int colsB, double matrixB[rowsB][colsB], double matrixC[rowsA][colsB])
{
    // Make sure matrix sizes are compatible
    if (colsA != rowsB)
    {
        printf("Incompatible matrix sizes.\n");
    }

    else
    {
        // Loop through the rows of A and columns of B
        for (int i = 0; i < rowsA; ++i)
        {
            for (int j = 0; j < colsB; ++j)
            {
                // Multiply every entry in the row of A with the entry in the row of B
                // and add them all together. Then add the result to the final matrix.
                double entry = 0;
                for (int k = 0; k < colsA; ++k)
                {
                    entry += matrixA[i][k] * matrixB[k][j];
                }
                matrixC[i][j] = entry;
            }
        }
    }
}

// Function to solve a system of linear equations
void solveLinearSystem(int rowsA, int colsA, double matrixA[rowsA][colsA], int rowsB, int colsB, double matrixB[rowsB][colsB], double matrixC[rowsB][colsB])
{
    // Make sure the matrices are of the correct size
    if (rowsA == colsA && rowsA == rowsB && colsB == 1)
    {
        // Loop through each row of A
        for (int i = 0; i < rowsA; ++i)
        {
            // Make sure each pivot is valid
            if (matrixA[i][i] == 0)
            {
                printf("Divide by 0 error: No Solution.");
                break;
            }

            // Divide each entry in the row by the pivot value
            // Including the corresponding value in the B matrix
            float dividingFactor = matrixA[i][i];
            matrixB[i][0] /= dividingFactor;
            for (int j = 0; j < colsA; ++j)
            {
                matrixA[i][j] /= dividingFactor;
            }

            // Loop through each row and perform the necessary row operations
            for (int j = 0; j < rowsA; ++j)
            {
                // Skip over the row we are currently on
                if (j == i)
                {
                    continue;
                }

                // The subtraction factor is simply the matrix entry directly above or below the pivot
                float subtractingFactor = matrixA[j][i];

                // Multiply the i-th row by the subtractingFactor and then subtract each row.
                for (int k = 0; k < colsA; ++k)
                {
                    matrixA[j][k] -= matrixA[i][k] * subtractingFactor;
                }
                matrixB[j][0] -= matrixB[i][0] * subtractingFactor;
            }
        }

        // The matrix is now solved, so we transfer the B matrix values over to the solution matrix.
        for (int i = 0; i < rowsB; ++i)
        {
            matrixC[i][0] = matrixB[i][0];
        }
    }

    else
    {
        printf("Invalid matrices. Must be a square matrix and a vector.\n");
    }
}

// Given a matrix X and a vector y do a least squares regression on A and y by solving the linear system (A^T)(A)b = (A^T)y
void leastSquares(int rows, int columns, double A[rows][columns], double b[columns][1], double y[rows][1])
{
    // Make the transpose matrix
    double transpose[columns][rows];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            transpose[j][i] = A[i][j];
        }
    }

    double ATA[columns][columns];
    double ATY[columns][1];

    // Do matrix multiplication necessary to set up linear system
    multiplyMatrices(columns, rows, transpose, rows, columns, A, ATA);
    multiplyMatrices(columns, rows, transpose, rows, 1, y, ATY);

    // Solve the linear system
    solveLinearSystem(columns, columns, ATA, columns, 1, ATY, b);
}