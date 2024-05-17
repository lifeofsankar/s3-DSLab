//PROGRAM TO CONVERT A SPARSE MATRIX TO TUPLE FORM AND PRINT IT AND FIND ITS TRANPOSE. PRINT BOTH TUPLE AND ORIGINAL FORM OF TRANSPOSE

#include <stdio.h>
#define MAX_TERMS 100

struct Sparse_matrix
{
    int row;
    int col;
    int value;
};

// Arrays for the sparse matrix and its transpose, and their sizes
struct Sparse_matrix sparse1[MAX_TERMS];
struct Sparse_matrix transposeSparse[MAX_TERMS];
int SIZE;

// Dimensions of the input matrix
const int MATRIX_ROWS, MATRIX_COLS;

// Arrays for the input matrix and its transpose
int matrix[100][100];
int transpose[100][100];

// Function to print a matrix in standard 2D array format
void printMatrix(int printMatrix[100][100], int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%4d", printMatrix[i][j]);
        }
        printf("\n");
    }
}

// Function to print a sparse matrix in tuple format
void printSparseMatrix(struct Sparse_matrix sparse[100])
{
    int i;
    printf("\n");
    printf("ROW  COLUMN  VALUE");
    for (i = 0; i < SIZE; i++)
    {
        printf("\n");
        printf("%d\t%d\t%d", sparse[i].row, sparse[i].col, sparse[i].value);
    }
}

// Function to convert the input matrix to its sparse matrix (tuple) representation
void convertToSparseMatrix()
{
    // The first element is metadata: <number of rows, number of columns, number of non-zero entries>
    sparse1[0].row = MATRIX_ROWS;
    sparse1[0].col = MATRIX_COLS;
    int i, j, k = 1;
    for (i = 0; i < MATRIX_ROWS; i++)
    {
        for (j = 0; j < MATRIX_COLS; j++)
        {
            if (matrix[i][j])
            {
                sparse1[k].row = i + 1; // +1 because tuple indexing starts from 1
                sparse1[k].col = j + 1;
                sparse1[k].value = matrix[i][j];
                k++;
            }
        }
    }
    SIZE = k;
    sparse1[0].value = k - 1; // The value is the number of non-zero elements, which is k-1
}

// Function to find the transpose of the sparse matrix
void transposeSparseMatrix()
{
    // The first element is metadata: <number of rows, number of columns, number of non-zero entries>
    transposeSparse[0].row = MATRIX_COLS; // Swap rows and columns
    transposeSparse[0].col = MATRIX_ROWS;
    transposeSparse[0].value = sparse1[0].value; // The number of non-zero elements is the same
    int i, j, k = 1;
    for (i = 1; i <= MATRIX_COLS; i++)
    {
        for (j = 1; j <= SIZE; j++)
        {
            if (sparse1[j].col == i)
            {
                transposeSparse[k].row = sparse1[j].col;
                transposeSparse[k].col = sparse1[j].row;
                transposeSparse[k].value = sparse1[j].value;
                k++;
            }
        }
    }
}

// Function to convert a sparse matrix back to its normal 2D matrix form
void convertSparseToNormal()
{
    int i, j;
    // Initialize the transpose array with all elements set to 0
    for (i = 0; i < MATRIX_COLS; i++)
        for (j = 0; j < MATRIX_ROWS; j++)
            transpose[i][j] = 0;

    // Fill in the transpose array using the sparse matrix tuple values
    for (i = 1; i < SIZE; i++)
    {
        transpose[transposeSparse[i].row - 1][transposeSparse[i].col - 1] = transposeSparse[i].value;
    }
}

int main()
{
    int i, j;
    printf("\nEnter matrix dimensions: ");
    scanf("%d %d", &MATRIX_ROWS, &MATRIX_COLS);
    printf("\nEnter matrix: ");
    for (i = 0; i < MATRIX_ROWS; i++)
        for (j = 0; j < MATRIX_COLS; j++)
            scanf("%d", &matrix[i][j]);

    printf("\nINPUT MATRIX\n");
    printMatrix(matrix, MATRIX_ROWS, MATRIX_COLS);

    convertToSparseMatrix();

    printf("\n\nSPARSE MATRIX (TUPLE FORM)");
    printSparseMatrix(sparse1);

    printf("\n\nTRANSPOSE OF SPARSE MATRIX (TUPLE FORM)");
    transposeSparseMatrix();
    printSparseMatrix(transposeSparse);

    printf("\n\nTRANSPOSE OF INPUT MATRIX\n");
    convertSparseToNormal();
    printMatrix(transpose, MATRIX_COLS, MATRIX_ROWS);
    return 0;
}