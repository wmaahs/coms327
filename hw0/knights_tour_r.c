#include <stdio.h>
#include <stdlib.h>

int n;  //width of chess board
int m;  //height of chess board



#define MAX_INPUT_SIZE 100  //max amount of characters the user is allowed to input

//move patterns in the x and y coordinates

#define KNIGHT_MOVES 8
static int mpx[KNIGHT_MOVES] = {1, 1, 2, 2, -1, -1, -2, -2};
static int mpy[KNIGHT_MOVES] = {2, -2, 1, -1, 2, -2, 1, -1};

// check if (x,y) is on the board
int boarder_check(int x, int y) {
    if((x >= 0 && y >= 0) && (x <= n && y <= m)) {
        //success
        return 0;
    }
    else {
        //failure
        return 1;
    }
}

// function to check if the location (x,y)
// has been visited
int is_jump_valid(int a[n][m], int x, int y) {
    
    if(boarder_check(x, y) == 1) {
        //boarder check failed
        return  1;
    }
    else if(a[x][y] > 0) {
        //square has already been reached
        return 1;
    }
    else {
        //success
        return 0;
    }
}

void format_output(int chess_board[n][m]){
    for (int x = 0; x < n; x++){
        for(int y = 0; y < m; y++){
            printf("%2d,", chess_board[x][y]);
        }
    }
    printf("\n");

}

int knights_tour_recursion(int x, int y, int move_ind, int chess_board[n][m]) {

    int move;
    int next_x;     //the next x in the array
    int next_y;     //the next y in the array
    
    //have completed the chessboard
    if(move_ind == n*m + 1){
        //go back to finding more solutions
        format_output(chess_board);
        move_ind = 1;
        return 0;
    }

    for(move = 0; move < KNIGHT_MOVES; move++){
        next_x = x + mpx[move];
        next_y = y + mpy[move];
        
        if(is_jump_valid(chess_board, next_y, next_x) == 0){
            //success
            chess_board[next_x][next_y] = move_ind;
            if(knights_tour_recursion(next_x, next_y, move_ind + 1, chess_board) == 1){
                //need to add a check here

                //backtrack
                return 1;
            }
            else{
                chess_board[next_x][next_y] = -1;
            }
        }
        //no path found from that next move
    }
    return 0;
}

int knights_tour_solver(){

    // generate empty chess board (empty => -1)
    int chess_board[n][m];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            chess_board[i][j] = -1;
        }
    }

    for(int x = 0; x < n; x++){
        for(int y = 0; y < m; y++){
            chess_board[x][y] = 0;

            if(knights_tour_recursion(0, 0, 1, chess_board) == 1) {
                printf("solution does not exits");
                return 1;
            }
            else{
                //solution found and printed
                //reset the chess board and check the next spot
                for(int i = 0; i < n; i++) {
                    for(int j = 0; j < m; j++) {
                        chess_board[i][j] = -1;
                    }
                }
            }

        }
    }
    
    return 0;
}

int main() {

    char input[MAX_INPUT_SIZE] = {'\0'};

    //prompt user for size of chess board
    // printf("Enter width (n): \n");
    // fgets(input, MAX_INPUT_SIZE, stdin);
    //write input to n
    // n = atoi(input);
    n = 4;

    //do the same for height
    // printf("Enter height (m): \n");
    // fgets(input, MAX_INPUT_SIZE, stdin);
    //write input to m
    // m = atoi(input);
    m = 4;

    knights_tour_solver();
    return 0;
}