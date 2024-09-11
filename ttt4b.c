/* Homework 4 Problem 2 “ttt4b.c” 
 * Pranavi Khanna, ECS 36A
 * This program is a tic-tac-toe game so 2 people can play.
 * June 11th 2024
 * original program written
 */
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes */
void printXSection(int i);
void printOSection(int i);
void printEmptySection(void);
void printRowSeparator(void);
void printBoard(char board[3][3]);
int checkWin(char board[3][3], char player);
int checkTie(char board[3][3]);

int main(void) {
    char board[3][3] = { { ' ', ' ', ' ' }, { ' ', ' ', ' ' }, { ' ', ' ', ' ' } };
    int x, y;
    char input[100];
    char currentPlayer = 'X'; /* X goes first */
    int moveCount = 0;

    while (moveCount < 9) {
        int validMove = 0;

        /* Prompt for the current player's turn */
        printf("%c's turn > ", currentPlayer);

        while (!validMove) {
            if (!fgets(input, sizeof(input), stdin)) {
                printf("\n");
                exit(0); /* End-of-file or read error, exit with status 0 */
            }

            /* Check if input is just a newline (empty input) */
            if (input[0] == '\n') {
                exit(0); /* Exit with status 0 for newline with no data */
            }

            /* Check for valid input */
            if (sscanf(input, "%d %d", &x, &y) != 2) {
                /* Find the first illegal character */
                char *illegalChar = input;
                while (*illegalChar && (*illegalChar == ' ' || *illegalChar == '\n')) {
                    illegalChar++;
                }
                if (*illegalChar) {
                    fprintf(stderr, "Illegal character in input \"%c\"\n", *illegalChar);
                } else {
                    fprintf(stderr, "Illegal character in input\n");
                }
                printf("%c's turn > ", currentPlayer); /* Prompt again for the same player */
                continue; /* Invalid input, prompt again */
            }

            /* Validate coordinates */
            if (x < 1 || x > 3 || y < 1 || y > 3) {
                fprintf(stderr, "%d,%d is not a valid square; the numbers must be between 1 and 3 inclusive\n", x, y);
                printf("%c's turn > ", currentPlayer); /* Prompt again for the same player */
                continue; /* Invalid coordinates, prompt again */
            }

            /* Adjust for 0-based indexing */
            x--;
            y--;

            /* Check if the square is already occupied */
            if (board[x][y] != ' ') {
                fprintf(stderr, "%c has played %d,%d\n", board[x][y], x + 1, y + 1);
                printBoard(board); /* Reprint the board if the square is taken */
                printf("%c's turn > ", currentPlayer); /* Prompt again for the same player */
                continue; /* Square already occupied, prompt again */
            }

            validMove = 1; /* Move is valid */
        }

        /* Place the mark on the board */
        board[x][y] = currentPlayer;
        moveCount++;

        /* Print the board */
        printBoard(board);

        /* Check for a win */
        if (checkWin(board, currentPlayer)) {
            printf("Game over! %c won!\n", currentPlayer);
            return 0;
        }

        /* Check for a tie */
        if (checkTie(board)) {
            printf("Game over! It’s a tie!\n");
            return 0;
        }

        /* Switch player */
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}

/* Function to check for a win */
int checkWin(char board[3][3], char player) {
    int i;
    /* Check rows and columns */
    for (i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1;
        }
    }
    /* Check diagonals */
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1;
    }
    return 0;
}

/* Function to check for a tie */
int checkTie(char board[3][3]) {
    int row, col;
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            if (board[row][col] == ' ') {
                return 0; /* Found an empty spot, no tie */
            }
        }
    }
    return 1; /* No empty spots, it's a tie */
}

/* Function to print a line of the 'X' pattern in the target section */
void printXSection(int i) {
    if (i == 1 || i == 5) 
        printf(" X   X ");
    else if (i == 2 || i == 4)
        printf("  X X  ");
    else if (i == 3)
        printf("   X   ");
    else
        printf("       ");
}

/* Function to print a line of the 'O' pattern in the target section */
void printOSection(int i) {
    if (i == 1 || i == 5) 
        printf(" OOOOO ");
    else if (i == 2 |i == 3| i == 4)
        printf(" O   O ");
    else
        printf("       ");
}

/* Function to print a line of an empty section */
void printEmptySection(void) {
    printf("       ");
}

/* Function to print a row separator */
void printRowSeparator(void) {
    printf("#######################\n");
}

/* Function to print the entire board */
void printBoard(char board[3][3]) {
    int row, col, i;

    for (row = 0; row < 3; row++) {    /* Iterate over rows */
        for (i = 0; i < 7; i++) {      /* Iterate over the 7 lines in each section */
            for (col = 0; col < 3; col++) {  /* Iterate over columns */
                if (board[row][col] == 'X') {
                    printXSection(i);  /* Print 'X' pattern */
                } else if (board[row][col] == 'O') {
                    printOSection(i);  /* Print 'O' pattern */
                } else {
                    printEmptySection(); /* Print empty section */
                }
                if (col < 2) {
                    printf("#");
                }
            }
            printf("\n"); /* New line after each row of sections */
        }
        if (row < 2) {
            printRowSeparator(); /* Print row separator */
        }
    }
}
