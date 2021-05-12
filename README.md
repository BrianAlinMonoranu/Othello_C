# Othello_C
Othello in C- 2 Player Game
How I decided on implementing the game etc - C OTHELLO

1)Starting the game:
First of all I used a struct called struct Display which had the a 2D Array and int variable,(I used struct Display Game) and I had to think of how to initialize the board and players therefore I used a 2D array(16 x 16 for a specific reason as our checks throughout the program needs the borders outside to be empty and it was conveniant for me) to use as the board and use and int variable
to store the current player. All of this I inserted into a struct called display .Then I defined WHITE as the number 0 and BLACK as 1 then set an EMPTY position as 2 so the board in other words will contain numbers
but I made it easier for the user and myself to read if so I called them WHITE BLACK and EMPTY.

Then I created 2 char arrays to store the players' names and created a function called enter_player which will be called only once in the program
which will take the names of the players from user.Then I thought about how to initialize the scores and players on the board , therefore I created a function called starting positions
Here we put the starting positions into the board 2d array we created at the start but before that we initialized the whole board with EMPTY

Then I created a function that will present the board each round called display_board and it will print the board in a certain way.
We used a nested for loop to loop around each column and row and check if there is a white in a certain position print a variable called WHITE_MARKER which essentially
is "W" and same thing with BLACK and if any of both aren't in a certain position then we print EMPTY_Marker which is a space bar

-Functions:
A functions to check if 2 things, to check if a move is valid and to check how many valid moves can the current player make (move function)
A function to print the game board after each move (game_board function)
A function to display the current score (Display_score)
A function that inputs starting positions ( starting_positions)
A function that enters the move on the board ( insert_move function):
This function has the same conditions as the move function except the one (board[i][j] == EMPTY) which means that it doesnt check if the current position is empty as maybe the move inputted catches two moves
A function that displays the winner at the end of the game (display_winner)

2) Game Logic:
In the int main function I used 3 while loops , the outer while loop which doesnt terminate unless the game is over (if the variable turns to TRUE)
Then the first inner While loop is Player 1 and wont terminated unless the variable turns 0 which it does at the end of the while loop (we then set current_player to BLACK).
Then we check if there is any valid position the player can place with 2 for loops for each position (function: move) and if not valid moves then we skip the turn.
The program then asks the player to insert a move (user_move) then in it checks if the move is within the range so if it is in between 1-8 and a-h but
we also convert the letter into an int so it will be used for array manipulation then it checks if it is a valid position(using move function) and if it is then we input it
on the board with the insert_move function and then the while loop will terminate as the condition in the while loop turns to == 0 then it terminates as we set the variable to 0 at the end
then it goes to the next loop and does the same things again then after player 2 while loop it goes to the top of the outer while loop and starts
again

3) How did I check if the moves are valid?
We basically created a function but we put it into a different file called Playable.c and created a library called Playable.h and we check if a certain move
is valid( move function) and here we have a series of if statements with while loops and it will be a bit hard to explain as it is long but i will try to summarise it
We start the function with a while loop that checks if Playable is 0 and it will be for each move  and then we check the series of if statements if Playable == 0
and if one of them correlate to the corresponding position desired by the user then Playable turns to 1 and it will avoid the error message because
it isn't 0 then it leaves the while loop. Before a move is even asked from the user we do a check with two for loops(nested for loops)
To check whether there are any valid positions for the current player and if not then we leave the program with the same function, move!

I will use 1 if statement that demonstrates my method , as I a lot more and it will take too long to explain each one but they have similar styles
As all conditions have has if statements and while loops
We created conditions to check LEFT,RIGHT,UP,DOWN,TOP LEFT DIAGONAL, TOP RIGHT DIAGONAL, BOTTOM LEFT DIAGONAL, BOTTOM RIGHT DIAGONAL:
-> Checking left in a row:
WHITE:We have used  an if statement that checks  if the position inputted by user is EMPTY and then checking if the [j+1] and is BLACK and if the next position to the right of it is not EMPTY
      and if so then we check  if next to black on the [J + 2(up to 8)] is a WHITE then enters if statement, We also
      Here is the code to visualize it better:
       CHECKS IF EMPTY    CHECKS IF NEXT POSITION IS BLACK      CHECKS IF 2 POSITION AWAY FROM THE POSITION IS NOT EMPTY
      board[i][j] == EMPTY && board[i][j + 1] == BLACK && board[i][j + 2] != EMPTY &&
      ((board[i][j + 1] == BLACK && board[i][j + 2] == WHITE) ||(board[i][j + 2] == BLACK && board[i][j + 3] == WHITE)
       ||(board[i][j + 3] == BLACK && board[i][j + 4] == WHITE) ||(board[i][j + 4] == BLACK && board[i][j + 5] == WHITE)
       ||(board[i][j + 5] == BLACK && board[i][j + 6] == WHITE) ||(board[i][j + 6] == BLACK && board[i][j + 7] == WHITE)
        ||(board[i][j + 7] == BLACK && board[i][j + 8] == WHITE)))

      If these conditions are met in the if statement then we set the  position [i][j] position entered by user with WHITE
      Then we have a while loop that loops around while it isnt BLACK and starts filling in the columns that are not BLACK with white in
      between the two WHITES. Then when the code leaves the checking function it implements the positions as playable is 1 in the insert move function
      and instead of a for loop we used a longer if statement
      CHECKS:EMPTY -> B -> B -> W
      IMPLEMENTS: W -> W -> W  -> W
BLACK: Same concept as above

->Checking Right in a row:
BLACK:We have used  an if statement that checks  if the position inputted by user is EMPTY and then checking if the [j+1] and is WHITE and if the next position to the right of it is not EMPTY
     and if so then we check  if next to WHITE on the [J + 2(up to 8)] is a BLACK then enters if statement, We also
      If these conditions are met in the if statement then we set the  position [i][j] position entered by user with WHITE
      Then we have a while loop that loops around while it isnt BLACK and starts filling in the columns that are not BLACK with white in
      between the two WHITES.Then when the code leaves the checking function it implements the positions as playable is 1 in the insert move function
      and instead of a for loop we used a longer if statement
      CHECKS:EMPTY -> W -> W -> B
      IMPLEMENTS: B->B->B->B
Similar methods are implemented the differences will be that the positions it will check is different and it will take very long to write
each one down but I hope you get the point

4)Ending the Program
At the end of the int main program we are able to see that we have a few if statements that check certain things

1) If there is no empty spaces on the board:
   We have a nested for loop that checks each row and column each round and increments empty_count if a position is empty
   Then we have a if statement that checks if empty_count == 0 then we set the variable is_game_over to == TRUE and then it doesn't enter the outer while loop
   above and ends the game

2)If there is not valid move:
  In the move function the function checks before the user inputs a move if the amount of valid spaces and if there isnt any then we ask the user
  to input 1 and then terminate the turn by using break;

3)If only BLACK markers are on the board or if only  WHITES are on the board:
  This was easy enough as we have an if statement that checks if the one players score is 0 then sets is_game_over to TRUE


