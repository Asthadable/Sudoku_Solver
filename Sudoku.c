#include <stdio.h>
int N=9;

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

// Function to check if a number can be placed in a given cell
int isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number exists in the current row or column
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return 0;
        }
    }

    // Check if the number exists in the current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return 0;
            }
        }
    }

    return 1;
}

// Function to solve the Sudoku using backtracking
int solveSudoku(int grid[N][N]) {
    int row, col;
    // Find an empty cell (with value 0)
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                // Try placing numbers 1 to 9 in the empty cell
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;
                        // Recursively solve for the next cell
                        if (solveSudoku(grid)) {
                            return 1;
                        }
                        // If the current placement doesn't lead to a solution, backtrack
                        grid[row][col] = 0;
                    }
                }
                // If no number can be placed, it means the puzzle is unsolvable
                return 0;
            }
        }
    }
    // If all cells are filled, the puzzle is solved
    return 1;
}

int main() {
    int grid[N][N];

    // Input the Sudoku grid, use 0 for empty cells
    printf("Enter the Sudoku grid (use 0 for empty cells):\n");
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            scanf("%d", &grid[row][col]);
        }
    }

    if (solveSudoku(grid)) {
        printf("Sudoku solved:\n");
        printGrid(grid);
    } else {
        printf("No solution exists for the given Sudoku.\n");
    }

    return 0;
}
