//
// Created by brian on 04/05/2021.
//
//Brian Alin
#include <stdio.h>
#include<time.h>
#include "Playable.h"
#include <string.h>
#define Max 16
void final_game_board(char player[],char player2[]);//This is a function which is used when the game ends to present the final board
void game_board(char player[],char player2[]);//After every move this function will be called to present the board
void display_score(char player[] , char player2[]);//This will display the score
void starting_positions( );//This will be used to insert the starting positions of B and W
char enter_player(char player[],char player2[]);//We ask user to enter Player names when called
void User_move( int *p_row, int *p_column );//Moves will be entered here in this function
char insert_move(int row , int column,char board[Max][Max] , int playable);//Here the moves will be put on the board if valid when function is called
void display_winner(char player[],char player2[], time_t seconds);//This will display the winner
void is_move_on_board(int i, int j);//Checking if the move is on board
//This struct will store the board and the current_player playing in the game
struct Display
{
    char board[Max][Max];//This will be our board for the program and where all moves will be stored
    int current_player;//This will store the current Player
};

struct Display Game;//Creating a struct called game that will store current player and game board

#define WHITE    0//We define WHITE as 0
#define BLACK    1//We set BLACK to 1
#define EMPTY    2//We define EMPTY as 2

#define WHITE_MARKER    "  W  "//WHITE on the board will appear as W
#define BLACK_MARKER    "  B  "//BLACK on the board will appear as B
#define EMPTY_MARKER    "     "//EMPTY on the board will appear as nothing

#define FALSE 0 //Defining False to 0
#define TRUE  1//Defining True to 1

FILE * Final;//File

const char *row_names = "012345678";//This will be used to call the rows in the display_board function

int scores[2];//This array will store the scores
int store[4];//This will store certain values for a certain function (we want to return the values from the function so i used an array instead of pointers)
int playable =0;//When this variable is 1 that means that the move is valid but when its 0 it isn't
int Player1_score;//Tracks player's 1 score
int Player2_score;//Tracks player's 2 score
int value[4];//We store certain things here throughout a function
int check_1=0;//We use this to store for PLAYER_1 the amount of moves possible
int check_2=0;//We use this to store for PLAYER_2 the amount of moves possible
char no_valid_1 ;//We use this to store when Player_1 passes
char no_valid_2 ;//We use this to store when Player_2 passes
char pass = 'p'; //We store the p into pass to compare later on

int main(void)
{
    time_t seconds;//We do the following two lines to get the time
    time(&seconds);
    int is_game_over = FALSE;//We initialize the variable is_game_over to FALSE as the game is not over
    int empty_count =0;//This will be used to check if there isnt any empty slots on the board
    int user_row;//taking users row
    int user_column;//taking users column
    char choice;
    char player[10];//Player 1 name
    char player2[10];//Player 2 name
    int print_once =0; //Print out a function once in the program
    int rob;//This will be used to take user input on whether they want to pass or not- Player 1
    int rob2;//This will be used to take user input on whether they want to pass or not - Player 2
    int random = 1;//We will use this to allow the moves function when checking before a move to do its work

    Final = fopen("othello-results.txt", "w+");//Opening a file to write to

    if(Final == NULL)//checking if its empty and it is PRINT MESSAGE
    {
        perror("ERROR NO SUCH FILE");
    }
    enter_player(player, player2);//We ask the users to enter player names
    starting_positions();//We program enters in the starting positions
    game_board(player, player2);//printing the first game board

    //Here we play the game will the the variable is_game_over (while the game is not over) isnt TRUE
    while(is_game_over != TRUE) {
        int Player_1_turn=1;
        int Player_2_turn=1;
        //We initialized print_once to 0 and while it isn't 1 then we print the gameboard only once in this if statement and for the whole program as print_once will be 1 later on

        //We do another while loop but this one is for PLAYER 1 and this will request Player 1 to input if he wants to pass or play
        //If he plays the user will be asked to input his moves and the is_move_on_board will check if its range
        while(Player_1_turn != 0) {
            Game.current_player = BLACK;//Set current player to BLACK
            for(int i=1; i<=8; i++)//Here we are using a nested for loop to see the amount of valid moves available and if there isnt any then skip turn
            {  value[0] = i;//storing row into value
                for(int j =1; j<=8; j++)
                {
                    value[1] = j;//storing column into value
                    random = 0;//Setting random to 0 so that it wont encounter that error message if there is no valid moves
                    moves(value, Game.board, Game.current_player,&check_1,&check_2,playable, random);//We call the function
                }
            }
            if(check_1 == 0)//if no valid moves then we skip turn using "break"
            {
                printf("Player_1: You have no valid moves please press 1 to pass your turn!\n");
                scanf(" %c", &no_valid_1);
                break;
            }
            printf("Player 1: %s\n",player);
            printf("Do you want to play?\n");
            printf("PLAY == > 1\n");

            scanf("%d", &rob);//Collects response

           while (rob !=1)//checks if 0 or 1 is inputted and if not asks the user for input again
            {
                scanf("%d", &rob);
            }
            if(rob == 1){
                playable =0;//Set playable to 0 so that in the valid function it can check if the move is valid and when it is it will turn to 1
                printf("Player 1: %s:",player);
                User_move(&user_row, &user_column);
                is_move_on_board(user_row,user_column);
                //Store will be used to receive certain information from this function
                store[0] = user_row;// We store the row number int the first position in the array store
                store[1] = user_column;//We store the column number into the second position in the array store
                random = 1;//We set random to 1 so that if no valid moves the error message pops up and then asks the user to enter another one
                moves(store, Game.board, Game.current_player,&check_1,&check_2,playable, random);//Here we check if it is a valid move
                user_row = store[0];//Then the row value we got from the function will be put back into user_row
                user_column = store[1];//Then the column value we got from the function will be put back into user_row
                playable = store[2];//Here we put back into playable the true value of playable if the moves where valid or not
                insert_move(user_row, user_column, Game.board, playable);//We then proceed to insert the move(s)
                game_board(player, player2);//Then the game board for Player 1 will be printed with his move
                Player_1_turn = 0;//Then we while terminate Player 1 loop  as Player_1_turn == 0

            }
        }
        //We do another while loop but this one is for PLAYER 2(all Player 2 things will be in this loop) and this will request Player 1 to input if he wants to pass or play
        //If he plays the user will be asked to input his moves and the is_move_on_board will check if its range
        //The procedure is the same as above
        while(Player_2_turn != 0) {
            Game.current_player = WHITE;
            for(int i=1; i<=8; i++)//Here we are using a nested for loop to see the amount of valid moves available and if there isnt any then skip turn
            {  value[0] = i;//row into array
                for(int j =1; j<=8; j++)
                {
                    value[1] = j;//column into array
                    random = 0;
                    moves(value, Game.board, Game.current_player,&check_1,&check_2,playable, random);
                }
            }
            if(check_2 == 0)//if no valid moves then we end his turn
            {
                printf("Player_2:You have no valid moves please press 1 to pass your turn!\n");
                scanf(" %c", &no_valid_2);
                break;
            }
                printf("Player 2: %s\n", player2);
                printf("Do you want to play?\n");
                printf("PLAY == > 1\n");

                scanf("%d", &rob2);//user input

                while (rob2 != 1)//checks if 1 is not inputted
                {
                    scanf("%d", &rob);
                }
                if (rob2 == 1) { // Same things that happend above is happening down here too
                    playable = 0;
                    printf("Player 2: %s:", player2);
                    User_move(&user_row, &user_column);
                    is_move_on_board(user_row, user_column);
                    store[0] = user_row;
                    store[1] = user_column;
                    random = 1;
                    moves(store, Game.board, Game.current_player, &check_1, &check_2, playable,random);//Here we check if it is a valid move
                    user_row = store[0];
                    user_column = store[1];
                    playable = store[2];
                    insert_move(user_row, user_column, Game.board, playable);
                    game_board(player, player2);
                    Player_2_turn = 0;
                }
            }
        //Here we check the positions in the board array to see if any is empty and if it is then we increment the empty_count
        for(int i=1; i<=8; i++)
        {
            for(int j=1; j<=8; j++)
            {
                if(Game.board[i][j] == EMPTY) {
                    empty_count++;
                }
            }
        }
        //If it is 0 so it there is not empty positions on the board then we set the variable to TRUE and the game end as the While loop above wont be accessed
        if(empty_count == 0)
        {
            is_game_over = TRUE;
        }
        //If any player doesnt have any markers on the board so if they 0 markers the game ends
        if( Player1_score == 0 || Player2_score == 0)
        {
            is_game_over = TRUE;
        }
        //Here this checks if both players pass the program will end
        if(no_valid_1 == pass && no_valid_2 == pass)
        {
            is_game_over = TRUE;
        }
        empty_count =0;//We set this to zero as when we start with player 1 again we want to keep checking every round
        check_1 = 0;
        check_2 =0;
    }
    //If the game is over we display_the winner of the game(we call the display_winner function)
    if(is_game_over == TRUE)
    {
        display_winner(player, player2, seconds);
    }

    printf("Today: %s", ctime(&seconds));//We print the date, time and  day
}
char enter_player(char player[],char player2[])//Here we ask the player to input their names
{
        printf("\t\t=== [Welcome to Othello] ===\n");
        printf("\t\tEnter name of Player 1 (Black): ");
        scanf("%s", player);
        printf("\t\tEnter name of Player 2 (White): ");
        scanf("%s", player2);

}
void starting_positions( )//This function initializes the board will starter positions for B and W
{
    for(int i=0; i<=16; i++)//Here we intialize every position to EMPTY
    {
        for(int j=0; j<=16; j++)
        {
            Game.board[i][j] = EMPTY;
        }
    }
    Game.board[4][4] = WHITE;
    Game.board[5][5] = WHITE;
    Game.board[4][5] = BLACK;
    Game.board[5][4] = BLACK;
    Player1_score = 2;//They both start on 2 points
    Player2_score = 2;
}

void display_score(char player[], char player2[])//Displays the score after each move
{
    printf( "\t\tScore: %s (Black) %d : %d %s (White)", player, Player1_score, Player2_score, player2 );
    printf("\n");
}
void game_board(char player[],char player2[])//This prints the game board onto the screen
{
    display_score( player ,  player2);//We call this to display the scores
    printf( "   _____ _____ _____ _____ _____ _____ _____ _____\n" );
    for ( int i=1; i<=8; i++ )
    {
        printf( "  |     |     |     |     |     |     |     |     |\n" );
        printf( "%c |", row_names[i] );
        for ( int j=1; j<=8; j++ )
        {
            if (Game.board[i][j] == WHITE ) // Here if the current positon is WHITE then we print W to the screen and if not then B
            {
                printf( "%s", WHITE_MARKER );
            } else if (Game.board[i][j] == BLACK ) {
                printf("%s", BLACK_MARKER);
            }

            else
            {
                printf( "%s", EMPTY_MARKER );//If not both above then its an empty positon
            }
            printf("|");
        }
        printf( "\n" );
        printf( "  |_____|_____|_____|_____|_____|_____|_____|_____|\n" );

    }
    printf( "     a     b     c     d     e     f     g     h\n" );//Printing the columns
    printf("\n");
}

void User_move(int *p_row, int *p_column)//Here we ask the user for the column and row
{
    char input_alpha; // This is a temporary char variable that will store the users' column
    char string[1];
    printf( "Enter column [a-h] & Enter the row [1-8]:(ex: c4):");
    scanf(" %c%d", &input_alpha,p_row);//reads column and row

    //Checks if it is in the range a-h and 1-8
    while(!(input_alpha>='a' && input_alpha<='h') && !(input_alpha>= 1 && input_alpha<=8))
    {
        scanf(" %c%d", &input_alpha, p_row);
    }

    string[0] = input_alpha;//We store it into an array of size 1
    string[1] = '\0';//Last position is a termination
    //The checks below check if the Letter inputted by the user for the Column is the from a-h and if it is then we input the right column integer for the correponding Letter
    if(strcmp(string,"a") ==0)
    {
        *p_column = 1;
    }
    if(strcmp(string,"b")== 0)
    {
        *p_column = 2;
    }
    if(strcmp(string,"c")== 0)
    {

        *p_column = 3;
    }
    if(strcmp(string,"d")== 0)
    {
        *p_column = 4;
    }
    if(strcmp(string,"e")== 0)
    {
        *p_column = 5;
    }
    if(strcmp(string,"f")== 0)
    {
        *p_column = 6;
    }
    if(strcmp(string,"g")== 0)
    {
        *p_column = 7;
    }
    if(strcmp(string,"h")== 0)
    {
        *p_column = 8;
    }

}
void is_move_on_board(int i, int j)//This checks if the row and column is in between  1-8 and if it isnt then it asks the user for different numbers
{
    while (!(i >= 1 && i <= 8) && !(j >= 1 && j <= 8)) {
        printf("Move isn't on the board, Try again!\n");
        scanf("%d %d", &i, &j);
    }
}
//Here it checks implements the row and column given by the user if its valid
char insert_move(int row , int column, char board[Max][Max] , int playable) {
    int i = row;//puts row into i
    int j = column;//puts column into j
    //If playable is 1 in other words if the position is valid for the corresponding color then enter the if statement
    if(playable == 1) {

        //Checks Left - This checks for WHITE
        if (Game.current_player == WHITE) {
            int r = j - 1;
            //If on the left of the desired position is BLACK and if next to that Black position its Not Empty and if next to the desired position it is BLACK and next to Black its white then it checks for the same condition but onwards in the row
            if (board[i][j + 1] == BLACK && board[i][j+2] != EMPTY &&((board[i][j + 1] == BLACK && board[i][j + 2] == WHITE) ||(board[i][j + 2] == BLACK && board[i][j + 3] == WHITE) ||(board[i][j + 3] == BLACK && board[i][j + 4] == WHITE) ||(board[i][j + 4] == BLACK && board[i][j + 5] == WHITE) ||
                                                                      (board[i][j + 5] == BLACK && board[i][j + 6] == WHITE)||(board[i][j+6] == BLACK &&board[i][j+7] == WHITE)||(board[i][j+7] == BLACK &&board[i][j+8] == WHITE))) {
                board[i][j] = Game.current_player;//Then we add it to the board
                //If the next position the desired position is BLACK and While its Not white then we add WHITE INSTEAD OF THAT BLACK and we do this while the current position is not WHITE
                if (board[i][r + 2] == BLACK) {
                    while (board[i][r + 2] != WHITE) {
                        board[i][r + 2] = Game.current_player;
                        r++;
                    }
                }
            }
        }
        //checking if the left position for black is a valid position
        if (Game.current_player == BLACK) {
            int r = j - 1;
            if (board[i][j + 1] != BLACK  && board[i][j+2] != EMPTY &&
                ((board[i][j + 1] == WHITE && board[i][j + 2] == BLACK) ||(board[i][j + 2] == WHITE && board[i][j + 3] == BLACK) ||(board[i][j + 3] == WHITE && board[i][j + 4] == BLACK) ||(board[i][j + 4] == WHITE && board[i][j + 5] == BLACK) ||(board[i][j + 5] == WHITE && board[i][j + 6] == BLACK)||(board[i][j+6] == WHITE &&board[i][j+7] == BLACK)||(board[i][j+7] == WHITE &&board[i][j+8] == BLACK))) {
                board[i][j] = Game.current_player;
                if (board[i][r + 2] == WHITE) {
                    while (board[i][r + 2] != BLACK) {
                        board[i][r + 2] = Game.current_player;
                        r++;
                    }
                }
            }
        }
        //CHECKS RIGHT IN THE ROW
        if (Game.current_player == BLACK) {
            int r = j + 1;
            if (board[i][j - 1] != BLACK && board[i][j - 1] == WHITE &&board[i][j-2] != EMPTY&&
                ((board[i][j - 1] == WHITE && board[i][j - 2] == BLACK)||(board[i][j - 2] == WHITE && board[i][j - 3] == BLACK) ||(board[i][j - 3] == WHITE && board[i][j - 4] == BLACK) ||(board[i][j - 4] == WHITE && board[i][j - 5] == BLACK) ||(board[i][j - 5] == WHITE && board[i][j - 6] == BLACK)||(board[i][j-6] == WHITE &&board[i][j-7] == BLACK)||(board[i][j-7] == WHITE &&board[i][j-8] == BLACK))) {
                board[i][j] = Game.current_player;
                if (board[i][r - 2] == WHITE) {
                    while (board[i][r - 2] != BLACK) {
                        board[i][r - 2] = Game.current_player;
                        r--;
                    }
                }
            }
        }
        if (Game.current_player == WHITE) {
            int r = j + 1;
            if (board[i][j - 1] != WHITE && board[i][j - 1] == BLACK &&  board[i][j-2] != EMPTY &&
                ((board[i][j - 1] == BLACK && board[i][j - 2] == WHITE) ||(board[i][j - 2] == BLACK && board[i][j - 3] == WHITE) ||(board[i][j - 3] == BLACK && board[i][j - 4] == WHITE) ||(board[i][j - 4] == BLACK && board[i][j - 5] == WHITE) ||(board[i][j - 5] == BLACK && board[i][j - 6] == WHITE)||(board[i][j-6] == BLACK && board[i][j-7] == WHITE)||(board[i][j-7] == BLACK &&board[i][j-8] == WHITE))) {
                board[i][j] = Game.current_player;
                if (board[i][r - 2] == BLACK) {
                    while (board[i][r - 2] != WHITE) {
                        board[i][r - 2] = Game.current_player;
                        r--;
                    }
                }
            }
        }
        //CHECKS UPWARDS
        if (Game.current_player == BLACK) {
            int r = i + 1;
            if ( board[i+1][j] != BLACK && board[i+1][j] == WHITE &&  board[i+2][j] != EMPTY &&
                 ((board[i+1][j] == WHITE && board[i+2][j] == BLACK)||(board[i+2][j] == WHITE && board[i+3][j] == BLACK) ||(board[i+3][j] == WHITE && board[i+4][j] == BLACK) ||(board[i+4][j] == WHITE && board[i+5][j] == BLACK) ||
                  (board[i+5][j] == WHITE && board[i+6][j] == BLACK)||(board[i+6][j] == WHITE &&board[i+7][j] == BLACK)||(board[i+7][j] == WHITE &&board[i+8][j] == BLACK))){
                board[i][j] = Game.current_player;
                if (board[r][j] == WHITE) {
                    while (board[r][j] != BLACK) {
                        board[r][j] = Game.current_player;
                        r++;
                    }
                }
            }
        }
        if (Game.current_player == WHITE) {
            int r = i + 1;
            if ( board[i+1][j] == BLACK && board[i+2][j] != EMPTY &&
                 ((board[i+1][j] == BLACK && board[i+2][j] == WHITE) ||(board[i+2][j] == BLACK && board[i+3][j] == WHITE) ||(board[i+3][j] == BLACK && board[i+4][j] == WHITE) ||(board[i+4][j] == BLACK && board[i+5][j] == WHITE) ||
                  (board[i+5][j] == BLACK && board[i+6][j] == WHITE)||(board[i+6][j] == BLACK &&board[i+7][j] == WHITE)||(board[i+7][j] == BLACK &&board[i+8][j] == WHITE))){
                board[i][j] = Game.current_player;
                if (board[r][j] == BLACK) {
                    while (board[r][j] != WHITE && board[r][j] != EMPTY) {
                        board[r][j] = Game.current_player;
                        r++;
                    }
                }
            }
        }
        // CHECKS DOWNWARDS
        if (Game.current_player == BLACK) {
            int r = i - 1;
            if ( board[i-1][j] != BLACK && board[i-1][j ] == WHITE && board[i-2][j] != EMPTY &&((board[i-1][j] == WHITE && board[i-2][j] == BLACK)||(board[i-2][j] == WHITE && board[i-3][j] == BLACK) ||(board[i-3][j] == WHITE && board[i-4][j] == BLACK) ||(board[i-4][j] == WHITE && board[i-5][j] == BLACK) ||
                 (board[i-5][j] == WHITE && board[i-6][j] == BLACK)||(board[i-6][j] == WHITE &&board[i-7][j] == BLACK)||(board[i-7][j] == WHITE &&board[i-8][j] == BLACK))){
                board[i][j] = Game.current_player;
                if (board[r][j] == WHITE) {
                    while (board[r][j] != BLACK && board[r][j] != EMPTY) {
                        board[r][j] = Game.current_player;
                        r--;
                    }
                }
            }
        }
        if (Game.current_player == WHITE) {
            int r = i - 1;
            if ( board[i-1][j] == BLACK && board[i-2][j] != EMPTY &&
                 ((board[i-1][j] == BLACK && board[i-2][j] == WHITE) ||(board[i-2][j] == BLACK && board[i-3][j] == WHITE) ||(board[i-3][j] == BLACK && board[i-4][j] == WHITE) ||(board[i-4][j] == BLACK && board[i-5][j] == WHITE) ||(board[i-5][j] == BLACK && board[i-6][j] == WHITE) ||(board[i-6][j] == BLACK &&board[i-7][j] == WHITE)||(board[i-7][j] == BLACK &&board[i-8][j] == WHITE))){
                board[i][j] = Game.current_player;
                if (board[r][j] == BLACK) {
                    while (board[r][j] != WHITE && board[r][j] != EMPTY) {
                        board[r][j] = Game.current_player;
                        r--;
                    }
                }
            }
        }
        //Bottom right DIAGONAL
        if (Game.current_player == BLACK) {
            int k = j - 1;
            int w = i - 1;
            if (board[w][k] == WHITE && board[w - 1][k - 1] != EMPTY &&
                ((board[i - 1][j - 1] == WHITE && board[i - 2][j - 2] == BLACK) ||(board[i - 2][j - 2] == WHITE && board[i - 3][j - 3] == BLACK) ||(board[i - 3][j - 3] == WHITE && board[i - 4][j - 4] == BLACK) ||(board[i - 4][j - 4] == WHITE && board[i - 5][j - 5] == BLACK) ||(board[i - 5][j - 5] == WHITE && board[i - 6][j - 6] == BLACK) ||(board[i-6][j-6] == WHITE &&board[i-7][j-7] == BLACK)||(board[i-7][j-7] == WHITE &&board[i-8][j-8] == BLACK))) {
                board[i][j] = Game.current_player;
                if (board[i - 1][j - 1] == WHITE) {
                    while (board[w][k] != BLACK) {
                        board[w][k] = Game.current_player;
                        w--;
                        k--;
                    }
                }
            }
        }
        if (Game.current_player == WHITE) {
            int k = j - 1;
            int w = i - 1;
            if (board[w][k] == BLACK && board[w - 1][k - 1] != EMPTY &&
                ((board[i - 1][j - 1] == BLACK && board[i - 2][j - 2] == WHITE) ||(board[i - 2][j - 2] == BLACK && board[i - 3][j - 3] == WHITE) ||(board[i - 3][j - 3] == BLACK && board[i - 4][j - 4] == WHITE) ||(board[i - 4][j - 4] == BLACK && board[i - 5][j - 5] == WHITE) ||
                 (board[i - 5][j - 5] == BLACK && board[i - 6][j - 6] == WHITE)||(board[i-6][j-6] == BLACK &&board[i-7][j-7] == WHITE)||(board[i-7][j-7] == BLACK &&board[i-8][j-8] == WHITE))) {
                board[i][j] = Game.current_player;
                if (board[i - 1][j - 1] == BLACK) {
                    while (board[w][k] != WHITE) {
                        board[w][k] = Game.current_player;
                        w--;
                        k--;
                    }
                }
            }
        }
        //Bottom LEFT DIAGONAL
        if (Game.current_player == WHITE) {
            int k = j + 1;
            int w = i - 1;
            if (board[w][k] == BLACK && board[w - 1][k + 1] != EMPTY &&((board[i - 1][j + 1] == BLACK && board[i - 2][j + 2] == WHITE) ||(board[i - 2][j + 2] == BLACK && board[i - 3][j + 3] == WHITE) ||(board[i - 3][j + 3] == BLACK && board[i - 4][j + 4] == WHITE) ||(board[i - 4][j + 4] == BLACK && board[i - 5][j + 5] == WHITE) ||
                 (board[i - 5][j + 5] == BLACK && board[i - 6][j + 6] == WHITE)||(board[i-6][j+6] == BLACK &&board[i-7][j+7] == WHITE)||(board[i-7][j+7] == BLACK &&board[i-8][j+8] == WHITE))) {
                board[i][j] = Game.current_player;
                if (board[w][k] == BLACK) {
                    while (board[w][k] != WHITE) {
                        board[w][k] = Game.current_player;
                        w--;
                        k++;
                    }
                }
            }
        }
        if (Game.current_player == BLACK) {
            int k = j + 1;
            int w = i - 1;
            if (board[w][k] == WHITE && board[w - 1][k + 1] != EMPTY &&((board[i - 1][j + 1] == WHITE && board[i - 2][j + 2] == BLACK) ||(board[i - 2][j + 2] == WHITE && board[i - 3][j + 3] == BLACK) ||(board[i - 3][j + 3] == WHITE && board[i - 4][j + 4] == BLACK) ||(board[i - 4][j + 4] == WHITE && board[i - 5][j + 5] == BLACK) ||
                 (board[i - 5][j + 5] == WHITE && board[i - 6][j + 6] == BLACK)||(board[i-6][j+6] == WHITE &&board[i-7][j+7] == BLACK)||(board[i-7][j+7] == WHITE &&board[i-8][j+8] == BLACK))) {
                board[i][j] = Game.current_player;
                if (board[w][k] == WHITE) {
                    while (board[w][k] != BLACK) {
                        board[w][k] = Game.current_player;
                        w--;
                        k++;
                    }
                }
            }
        }
        //TOP LEFT Diagonal
        if (Game.current_player == BLACK) {
            int k = j + 1;
            int w = i + 1;
            if (board[w][k] == WHITE && board[w + 1][k + 1] != EMPTY &&((board[i + 1][j + 1] == WHITE && board[i + 2][j + 2] == BLACK) ||(board[i + 2][j + 2] == WHITE && board[i + 3][j + 3] == BLACK) ||(board[i + 3][j + 3] == WHITE && board[i + 4][j + 4] == BLACK) ||(board[i + 4][j + 4] == WHITE && board[i + 5][j + 5] == BLACK) ||
                 (board[i + 5][j + 5] == WHITE && board[i + 6][j + 6] == BLACK)||(board[i+6][j+6] == WHITE &&board[i+7][j+7] == BLACK)||(board[i+7][j+7] == WHITE &&board[i+8][j+8] == BLACK))) {
                board[i][j] = Game.current_player;
                if (board[i + 1][j + 1] == WHITE) {
                    while (board[w][k] != BLACK) {
                        board[w][k] = Game.current_player;
                        w++;
                        k++;
                    }
                }
            }
        }
        if (Game.current_player == WHITE) {
            int k = j + 1;
            int w = i + 1;
            if (board[w][k] == BLACK && board[w + 1][k + 1] != EMPTY &&
                ((board[i + 1][j + 1] == BLACK && board[i + 2][j + 2] == WHITE) ||(board[i + 2][j + 2] == BLACK && board[i + 3][j + 3] == WHITE) ||(board[i + 3][j + 3] == BLACK && board[i + 4][j + 4] == WHITE) ||(board[i + 4][j + 4] == BLACK && board[i + 5][j + 5] == WHITE) ||
                 (board[i + 5][j + 5] == BLACK && board[i + 6][j + 6] == WHITE)||(board[i+6][j+6] == BLACK &&board[i+7][j+7] == WHITE)||(board[i+7][j+7] == BLACK &&board[i+8][j+8] == WHITE))) {
                board[i][j] = Game.current_player;
                if (board[w][k] == BLACK) {
                    while (board[w][k] != WHITE) {
                        board[w][k] = Game.current_player;
                        w++;
                        k++;
                    }
                }
            }
        }
//TOP RIGHT Diagonal
        if (Game.current_player == WHITE) {
            int k = j - 1;
            int w = i + 1;
            if (board[w][k] == BLACK && board[w + 1][k - 1] != EMPTY &&((board[i + 1][j - 1] == BLACK && board[i + 2][j - 2] == WHITE) ||(board[i + 2][j - 2] == BLACK && board[i + 3][j - 3] == WHITE) ||(board[i + 3][j - 3] == BLACK && board[i + 4][j - 4] == WHITE) ||(board[i + 4][j - 4] == BLACK && board[i + 5][j - 5] == WHITE) ||
                 (board[i + 5][j - 5] == BLACK && board[i + 6][j - 6] == WHITE)||(board[i+6][j-6] == BLACK &&board[i+7][j-7] == WHITE)||(board[i+7][j-7] == BLACK &&board[i+8][j-8] == WHITE))) {
                board[i][j] = Game.current_player;
                if (board[w][k] == BLACK) {
                    while (board[w][k] != WHITE) {
                        board[w][k] = Game.current_player;
                        w++;
                        k--;
                    }
                }
            }
        }
        if (Game.current_player == BLACK) {
            int k = j - 1;
            int w = i + 1;
            if (board[w][k] == WHITE && board[w + 1][k - 1] != EMPTY &&((board[i + 1][j - 1] == WHITE && board[i + 2][j - 2] == BLACK) ||(board[i + 2][j - 2] == WHITE && board[i + 3][j - 3] == BLACK) ||(board[i + 3][j - 3] == WHITE && board[i + 4][j - 4] == BLACK) ||(board[i + 4][j - 4] == WHITE && board[i + 5][j - 5] == BLACK) ||
                  (board[i + 5][j - 5] == WHITE && board[i + 6][j - 6] == BLACK)||(board[i+6][j-6] == WHITE &&board[i+7][j-7] == BLACK)||(board[i+7][j-7] == WHITE &&board[i+8][j-8] == BLACK))) {
                board[i][j] = Game.current_player;
                if (board[w][k] == WHITE) {
                    while (board[w][k] != BLACK) {
                        board[w][k] = Game.current_player;
                        w++;
                        k--;
                    }
                }
            }
        }
        Player2_score = 0;//Set the scores to zero
        Player1_score = 0;
        //Here we will check the whole board for W and B and will increment the scores for the corresponding Player_score variables
        for (int i = 1; i <= 8; i++) {
            for (int k = 1; k <= 8; k++) {
                if (board[i][k] == WHITE) {
                    Player2_score++;
                }
                if (board[i][k] == BLACK) {
                    Player1_score++;
                }
            }
        }
    }
}
//This will display the WINNER of the game
void display_winner(char player[],char player2[], time_t seconds)
{
    fprintf(Final,"%s" , ctime(&seconds));
    fprintf(Final, "============================ [FINAL SCORE] =====================================\n");
    fprintf(Final, "Final score:\n%s: %d %s: %d\n", player, Player1_score, player2, Player2_score );
    //If Player 2 score is bigger than Player 1 then it prints the w wins which means Player 2 wins as player 2 is white
    //Else if the player 2 score is less then Player 1 then Player 1 wins and if neither conditions then its a draw
    if ( Player2_score > Player1_score ) {
        fprintf(Final,"%s wins.\n", WHITE_MARKER);
    }
    else if (Player2_score < Player1_score ) {
        fprintf(Final,"%s wins.\n", player);
    }
    else {
        fprintf(Final,"Draw game.\n");
    }
    //The code below will be printed to a file called final_score.txt
    fprintf(Final,"================================================================================\n");
    fprintf(Final,"============================ [FINAL BOARD] =====================================\n");
    final_game_board(player,player2);//calls the function that prints the final game board
    fprintf(Final,"================================================================================\n");
    fclose(Final);
}
//Prints the final board which is the same as the display_board function board but this one will be printed to the file
void final_game_board(char player[],char player2[])
{
    fprintf(Final,"   _____ _____ _____ _____ _____ _____ _____ _____\n" );
    for ( int i=1; i<=8; i++ )
    {
        fprintf(Final,"  |     |     |     |     |     |     |     |     |\n" );
        fprintf(Final,"%c |", row_names[i] );
        for ( int j=1; j<=8; j++ )
        {
            if (Game.board[i][j] == WHITE )
            {
                fprintf(Final,"%s", WHITE_MARKER );
            } else if (Game.board[i][j] == BLACK ) {
                fprintf(Final,"%s", BLACK_MARKER);
            }

            else
            {
                fprintf(Final,"%s", EMPTY_MARKER );
            }
            fprintf(Final,"|");
        }
        fprintf(Final,"\n" );
        fprintf(Final,"  |_____|_____|_____|_____|_____|_____|_____|_____|\n" );

    }
    fprintf(Final,"     a     b     c     d     e     f     g     h\n" );
    fprintf(Final,"\n");
}

