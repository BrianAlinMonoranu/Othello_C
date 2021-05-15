//Created by brian on 03/05/2021.
#include "Playable.h"
#include<stdio.h>
#include<string.h>
#define WHITE    0
#define BLACK    1
#define EMPTY    2

void moves(int value[4],char board[Max][Max], int current_player, int *check_1, int *check_2, int Playable, int random) {

    int i = value[0];//we take the row and put it into i
    int j = value[1];//we take the column from array and put it into j
    Playable= 0;//set Playable to 0 to enter the while loop and the first for loop
    while(Playable == 0) {
        if (Playable == 0){
            //We have a series of if statements i could have used for loops instead but i just went with if statements and while loops
            //Therefor i will write the comments in the first if statement because it would take long and I have written a bit in the essay on GITHUB
            if (current_player == WHITE) {
                //If on the left of the desired position is BLACK and if next to that Black position its Not Empty and if next to the desired position it is BLACK and next to Black its white then it checks for the same condition but onwards in the row
                if (board[i][j] == EMPTY && board[i][j + 1] == BLACK && board[i][j + 2] != EMPTY &&
                    ((board[i][j + 1] == BLACK && board[i][j + 2] == WHITE) ||(board[i][j + 2] == BLACK && board[i][j + 3] == WHITE) ||(board[i][j + 3] == BLACK && board[i][j + 4] == WHITE) ||(board[i][j + 4] == BLACK && board[i][j + 5] == WHITE) ||(board[i][j + 5] == BLACK && board[i][j + 6] == WHITE) ||(board[i][j + 6] == BLACK && board[i][j + 7] == WHITE) ||(board[i][j + 7] == BLACK && board[i][j + 8] == WHITE))) {
                    *check_2 = *check_2 + 1;//we increment check that checks if there is valid moves and it increments
                    Playable = 1;//Playable turns to 1 which means there is a valid move
                }
            }

            if (current_player == BLACK) {
                //checking if the left position for black is a valid position
                if (board[i][j] == EMPTY && board[i][j + 1] == WHITE && board[i][j + 2] != EMPTY &&((board[i][j + 1] == WHITE && board[i][j + 2] == BLACK) ||(board[i][j + 2] == WHITE && board[i][j + 3] == BLACK) ||
                    (board[i][j + 3] == WHITE && board[i][j + 4] == BLACK) ||(board[i][j + 4] == WHITE && board[i][j + 5] == BLACK) ||(board[i][j + 5] == WHITE && board[i][j + 6] == BLACK) ||(board[i][j + 6] == WHITE && board[i][j + 7] == BLACK) ||(board[i][j + 7] == WHITE && board[i][j + 8] == BLACK))) {
                    *check_1 = *check_1 + 1;
                    Playable = 1;
                }
            }
            //check right
            if (current_player == BLACK) {
                if (board[i][j] == EMPTY && board[i][j - 1] != BLACK && board[i][j - 1] == WHITE && board[i][j - 2] != EMPTY &&((board[i][j - 1] == WHITE && board[i][j - 2] == BLACK) ||(board[i][j - 2] == WHITE && board[i][j - 3] == BLACK) ||(board[i][j - 3] == WHITE && board[i][j - 4] == BLACK) ||(board[i][j - 4] == WHITE && board[i][j - 5] == BLACK) ||(board[i][j - 5] == WHITE && board[i][j - 6] == BLACK) ||(board[i][j - 6] == WHITE && board[i][j - 7] == BLACK) ||
                    (board[i][j - 7] == WHITE && board[i][j - 8] == BLACK))) {
                    *check_1 = *check_1 + 1;
                    Playable = 1;
                }
            }
            if (current_player == WHITE) {
                if (board[i][j] == EMPTY && board[i][j - 1] != WHITE && board[i][j - 1] == BLACK && board[i][j - 2] != EMPTY &&((board[i][j - 1] == BLACK && board[i][j - 2] == WHITE) ||(board[i][j - 2] == BLACK && board[i][j - 3] == WHITE) ||(board[i][j - 3] == BLACK && board[i][j - 4] == WHITE) ||(board[i][j - 4] == BLACK && board[i][j - 5] == WHITE) ||(board[i][j - 5] == BLACK && board[i][j - 6] == WHITE) ||(board[i][j - 6] == BLACK && board[i][j - 7] == WHITE) ||
                    (board[i][j - 7] == BLACK && board[i][j - 8] == WHITE))) {
                    *check_2 = *check_2 + 1;
                    Playable =1;
                }
            }
            // UP
            if (current_player == BLACK) {
                if (board[i][j] == EMPTY && board[i + 1][j] != BLACK && board[i + 1][j] == WHITE && board[i + 2][j] != EMPTY &&((board[i + 1][j] == WHITE && board[i + 2][j] == BLACK) ||(board[i + 2][j] == WHITE && board[i + 3][j] == BLACK) ||(board[i + 3][j] == WHITE && board[i + 4][j] == BLACK) ||(board[i + 4][j] == WHITE && board[i + 5][j] == BLACK) ||(board[i + 5][j] == WHITE && board[i + 6][j] == BLACK) ||(board[i + 6][j] == WHITE && board[i + 7][j] == BLACK) ||
                    (board[i + 7][j] == WHITE && board[i + 8][j] == BLACK))) {
                    *check_1 = *check_1 + 1;
                    Playable = 1;
                }
            }
            if (current_player == WHITE) {
                if (board[i][j] == EMPTY && board[i + 1][j] == BLACK && board[i + 2][j] != EMPTY &&((board[i + 1][j] == BLACK && board[i + 2][j] == WHITE) ||(board[i + 2][j] == BLACK && board[i + 3][j] == WHITE) ||(board[i + 3][j] == BLACK && board[i + 4][j] == WHITE) ||(board[i + 4][j] == BLACK && board[i + 5][j] == WHITE) ||(board[i + 5][j] == BLACK && board[i + 6][j] == WHITE) ||(board[i + 6][j] == BLACK && board[i + 7][j] == WHITE) ||
                    (board[i + 7][j] == BLACK && board[i + 8][j] == WHITE))) {
                    *check_2 = *check_2 + 1;
                    Playable = 1;
                }
            }
            // DOWNWARDS
            if (current_player == BLACK) {
                if (board[i][j] == EMPTY && board[i - 1][j] != BLACK && board[i - 1][j] == WHITE && board[i - 2][j] != EMPTY &&((board[i - 1][j] == WHITE && board[i - 2][j] == BLACK) ||(board[i - 2][j] == WHITE && board[i - 3][j] == BLACK) ||(board[i - 3][j] == WHITE && board[i - 4][j] == BLACK) ||(board[i - 4][j] == WHITE && board[i - 5][j] == BLACK) ||(board[i - 5][j] == WHITE && board[i - 6][j] == BLACK) ||(board[i - 6][j] == WHITE && board[i - 7][j] == BLACK) ||
                    (board[i - 7][j] == WHITE && board[i - 8][j] == BLACK))) {
                    *check_1 = *check_1 + 1;
                    Playable = 1;
                }
            }
            if (current_player == WHITE) {
                if (board[i][j] == EMPTY && board[i - 1][j] == BLACK && board[i - 2][j] != EMPTY &&((board[i - 1][j] == BLACK && board[i - 2][j] == WHITE) ||(board[i - 2][j] == BLACK && board[i - 3][j] == WHITE) ||(board[i - 3][j] == BLACK && board[i - 4][j] == WHITE) ||(board[i - 4][j] == BLACK && board[i - 5][j] == WHITE) ||(board[i - 5][j] == BLACK && board[i - 6][j] == WHITE) ||(board[i - 6][j] == BLACK && board[i - 7][j] == WHITE) ||
                     (board[i - 7][j] == BLACK && board[i - 8][j] == WHITE))) {
                    *check_2 = *check_2 + 1;
                    Playable = 1;
                }
            }
            //Bottom right DIAGONAL
            if (current_player == BLACK) {
                int k = j - 1;
                int w = i - 1;
                if (board[i][j] == EMPTY && board[w][k] == WHITE && board[w - 1][k - 1] != EMPTY &&((board[i - 1][j - 1] == WHITE && board[i - 2][j - 2] == BLACK) ||(board[i - 2][j - 2] == WHITE && board[i - 3][j - 3] == BLACK) ||(board[i - 3][j - 3] == WHITE && board[i - 4][j - 4] == BLACK) ||(board[i - 4][j - 4] == WHITE && board[i - 5][j - 5] == BLACK) ||(board[i - 5][j - 5] == WHITE && board[i - 6][j - 6] == BLACK) ||(board[i - 6][j - 6] == WHITE && board[i - 7][j - 7] == BLACK) ||
                      (board[i - 7][j - 7] == WHITE && board[i - 8][j - 8] == BLACK))) {
                    *check_1 = *check_1 + 1;
                    Playable = 1;
                }
            }
            if (current_player == WHITE) {
                int k = j - 1;
                int w = i - 1;
                if (board[i][j] == EMPTY && board[w][k] == BLACK && board[w - 1][k - 1] != EMPTY &&((board[i - 1][j - 1] == BLACK && board[i - 2][j - 2] == WHITE) ||(board[i - 2][j - 2] == BLACK && board[i - 3][j - 3] == WHITE) ||(board[i - 3][j - 3] == BLACK && board[i - 4][j - 4] == WHITE) ||(board[i - 4][j - 4] == BLACK && board[i - 5][j - 5] == WHITE) ||(board[i - 5][j - 5] == BLACK && board[i - 6][j - 6] == WHITE) ||(board[i - 6][j - 6] == BLACK && board[i - 7][j - 7] == WHITE) ||
                     (board[i - 7][j - 7] == BLACK && board[i - 8][j - 8] == WHITE))) {
                    *check_2 = *check_2 + 1;
                    Playable = 1;
                }
            }
            //Bottom LEFT DIAGONAL
            if (current_player == WHITE) {
                int k = j + 1;
                int w = i - 1;
                if (board[i][j] == EMPTY && board[w][k] == BLACK && board[w - 1][k + 1] != EMPTY &&((board[i - 1][j + 1] == BLACK && board[i - 2][j + 2] == WHITE) ||(board[i - 2][j + 2] == BLACK && board[i - 3][j + 3] == WHITE) ||(board[i - 3][j + 3] == BLACK && board[i - 4][j + 4] == WHITE) ||(board[i - 4][j + 4] == BLACK && board[i - 5][j + 5] == WHITE) ||(board[i - 5][j + 5] == BLACK && board[i - 6][j + 6] == WHITE) ||(board[i - 6][j + 6] == BLACK && board[i - 7][j + 7] == WHITE) ||
                     (board[i - 7][j + 7] == BLACK && board[i - 8][j + 8] == WHITE))) {
                    *check_2 = *check_2 + 1;
                    Playable = 1;
                }
            }
            if (current_player == BLACK) {
                int k = j + 1;
                int w = i - 1;
                if (board[i][j] == EMPTY && board[w][k] == WHITE && board[w - 1][k + 1] != EMPTY &&((board[i - 1][j + 1] == WHITE && board[i - 2][j + 2] == BLACK) ||(board[i - 2][j + 2] == WHITE && board[i - 3][j + 3] == BLACK) ||(board[i - 3][j + 3] == WHITE && board[i - 4][j + 4] == BLACK) ||(board[i - 4][j + 4] == WHITE && board[i - 5][j + 5] == BLACK) ||(board[i - 5][j + 5] == WHITE && board[i - 6][j + 6] == BLACK) ||(board[i - 6][j + 6] == WHITE && board[i - 7][j + 7] == BLACK) ||
                      (board[i - 7][j + 7] == WHITE && board[i - 8][j + 8] == BLACK))) {
                    *check_1 = *check_1 + 1;
                    Playable = 1;
                }
            }
            //TOP LEFT Diagonal
            if (current_player == BLACK) {
                int k = j + 1;
                int w = i + 1;
                if (board[i][j] == EMPTY && board[w][k] == WHITE && board[w + 1][k + 1] != EMPTY &&((board[i + 1][j + 1] == WHITE && board[i + 2][j + 2] == BLACK) ||(board[i + 2][j + 2] == WHITE && board[i + 3][j + 3] == BLACK) ||(board[i + 3][j + 3] == WHITE && board[i + 4][j + 4] == BLACK) ||(board[i + 4][j + 4] == WHITE && board[i + 5][j + 5] == BLACK) ||(board[i + 5][j + 5] == WHITE && board[i + 6][j + 6] == BLACK) ||(board[i + 6][j + 6] == WHITE && board[i + 7][j + 7] == BLACK) ||
                     (board[i + 7][j + 7] == WHITE && board[i + 8][j + 8] == BLACK))) {
                    *check_1 = *check_1 + 1;
                    Playable = 1;
                }
            }
            if (current_player == WHITE) {
                int k = j + 1;
                int w = i + 1;
                if (board[i][j] == EMPTY && board[w][k] == BLACK && board[w + 1][k + 1] != EMPTY &&((board[i + 1][j + 1] == BLACK && board[i + 2][j + 2] == WHITE) ||(board[i + 2][j + 2] == BLACK && board[i + 3][j + 3] == WHITE) ||(board[i + 3][j + 3] == BLACK && board[i + 4][j + 4] == WHITE) ||(board[i + 4][j + 4] == BLACK && board[i + 5][j + 5] == WHITE) ||(board[i + 5][j + 5] == BLACK && board[i + 6][j + 6] == WHITE) ||(board[i + 6][j + 6] == BLACK && board[i + 7][j + 7] == WHITE) ||
                    (board[i + 7][j + 7] == BLACK && board[i + 8][j + 8] == WHITE))) {
                    *check_2 = *check_2 + 1;
                    Playable= 1;
                }
            }
//TOP RIGHT Diagonal
            if (current_player == WHITE) {
                int k = j - 1;
                int w = i + 1;
                if (board[i][j] == EMPTY && board[w][k] == BLACK && board[w + 1][k - 1] != EMPTY &&((board[i + 1][j - 1] == BLACK && board[i + 2][j - 2] == WHITE) ||(board[i + 2][j - 2] == BLACK && board[i + 3][j - 3] == WHITE) ||(board[i + 3][j - 3] == BLACK && board[i + 4][j - 4] == WHITE) ||(board[i + 4][j - 4] == BLACK && board[i + 5][j - 5] == WHITE) ||(board[i + 5][j - 5] == BLACK && board[i + 6][j - 6] == WHITE) ||(board[i + 6][j - 6] == BLACK && board[i + 7][j - 7] == WHITE) ||
                   (board[i + 7][j - 7] == BLACK && board[i + 8][j - 8] == WHITE))) {
                    *check_2 = *check_2 + 1;
                    Playable = 1;
                }
            }
            if (current_player == BLACK) {
                int k = j - 1;
                int w = i + 1;
                if (board[i][j] == EMPTY && board[w][k] == WHITE && board[w + 1][k - 1] != EMPTY &&((board[i + 1][j - 1] == WHITE && board[i + 2][j - 2] == BLACK) ||(board[i + 2][j - 2] == WHITE && board[i + 3][j - 3] == BLACK) ||(board[i + 3][j - 3] == WHITE && board[i + 4][j - 4] == BLACK) ||(board[i + 4][j - 4] == WHITE && board[i + 5][j - 5] == BLACK) ||(board[i + 5][j - 5] == WHITE && board[i + 6][j - 6] == BLACK) ||(board[i + 6][j - 6] == WHITE && board[i + 7][j - 7] == BLACK) ||
                     (board[i + 7][j - 7] == WHITE && board[i + 8][j - 8] == BLACK))) {
                    *check_1 = *check_1 + 1;
                    Playable = 1;
                }
            }
        }
        if(Playable == 0 && random == 1)//Here we check if the move is invalid  we ask the user to enter another one
        {
            int sub;
            printf("==========================================\n");
            printf("CURRENT MOVE IS INVALID MOVE PLEASE TRY AGAIN\n");
            printf("==========================================\n");
            char input_alpha;
            printf("Enter column [a-h] and row [1-8] like (eg.: c4).\n");
            scanf(" %c%d", &input_alpha, &sub);
            //Here we are checking if they are alphabetical and numbers are in between 1-8 and if not then we read new input
            while (!(input_alpha >= 'a' && input_alpha <= 'h') && !(input_alpha >= 1 && input_alpha <= 8)) {
                scanf(" %c%d", &input_alpha, &sub);
            }
            char string[1];
            i = sub;//putting the row into i
            string[0] = input_alpha;//putting the letter into an array
            string[1] = '\0';//second element in the array is a termination signal so position 0 is the important one atm
            //We have a series of if statements that check if the letter put in by the user is a certain letter and if that give it a number
            //which will be the column
            if (strcmp(string, "a") == 0) {
                j = 1;
            }
            if (strcmp(string, "b") == 0) {
                j = 2;
            }
            if (strcmp(string, "c") == 0) {

                j = 3;
            }
            if (strcmp(string, "d") == 0) {
                j = 4;
            }
            if (strcmp(string, "e") == 0) {
                j = 5;
            }
            if (strcmp(string, "f") == 0) {
                j = 6;
            }
            if (strcmp(string, "g") == 0) {
                j = 7;
            }
            if (strcmp(string, "h") == 0) {
                j = 8;
            }
        }
        if(random == 0)//if we are checking before a move is given then we try and terminate this function to go back to the nested loop by setting playable to 0 and breaking the while loop
        {
            Playable = 1;
        }
    }
    if(random == 1)//if we are checking if the position is valid then we put the row column and variable Playable back into the array and bring it back
    {
        value[0] = i;
        value[1] = j;
        value[2] = Playable;
    }
}