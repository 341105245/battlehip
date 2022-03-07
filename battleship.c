#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define rows 10
#define columns 10

char grid[rows][columns];
char guessGrid[rows][columns];
int gameOver = 1;
int boat1check[2][5];
int boat2check[2][4];
int boat3check[2][3];
int boat4check[2][2];
int guessCheck = 0;
int guessCheck1 = 0;
int guessCheck2 = 0;
int guessCheck3 = 0;

void setArray(char inputGrid[10][10]) {
//set default value to array
for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
        inputGrid[i][j] = '~'; //~ is water
    }
}
//set visible row/column numbers
inputGrid[0][0] = ' ';
for(int i=1; i<10; i++) {
        char x = i+'0'; // adding '0' turns numbers into char
        inputGrid[0][i] = x;
}
for(int i=1; i<10; i++) {
        inputGrid[i][0] = i+'0'; // adding '0' turns numbers into char
}
}
void printArray(char inputGrid[10][10]) {
    //print grid
for(int i=0; i<10; i++) {
    for(int j=0; j<10; j++) {
        if(i == 0 || j == 0) {
            printf("\e[1;37m%c\e[0m ", inputGrid[i][j]);
        } else {
            printf("%c ", inputGrid[i][j]);
    }
    }
        printf("\n");
}
}
void placeBoats(boatNumber, verHor, boatLength) {
srand(time(NULL));   // Initialization, should only be called once.
//create boat 1
int b = verHor; //variable for vertical or horizontal boat placement
char boat1[boatLength][1]; //horizontal boat
int z = (rand() %boatLength)+1;
int y = (rand() %boatLength)+1;
int x = (rand() %boatLength)+1;
int w = (rand() %boatLength)+1;
//above int declarations are for where boat should be placed on grid
//for loop below generates new boat position if place is occupied
for(int r=0; r<boatLength; r++) {
    do {
        z = (rand() %boatLength)+1; //generates now boat coords
        y = (rand() %boatLength)+1;
        } while(grid[z+r][y]=='x'); //checks if boat is already in grid place for each boat coord
}
//below is same loop as above but for vertical boats
for(int s=0; s<boatLength; s++) {
    do {
        w = (rand() %boatLength)+1;
        x = (rand() %boatLength)+1;
        break;
    } while(grid[w][x+s]=='x');
}
//fills boat array with x to mark boat
for(int i=0; i<boatLength; i++) {
        boat1[i][0] = 'x';} //horizontal boat
char boat1a[1][boatLength];
for(int i=0; i<boatLength; i++) {
        boat1a[0][i] = 'x';} // vertical boat
if(b==1) { //checks if boat used is horizontal or vertical
    for(int o=0; o<boatLength; o++) {
            grid[z+o][y]=boat1[o][0]; //sets values in grid array to boat array if boat is horizontal
            if(boatLength == 5) {
            boat1check[0][o]=z+o; //sets coordinate values to array to check if boat sunk
            boat1check[1][o]=y;
            } else if(boatLength == 4) {
            boat2check[0][o]=z+o;
            boat2check[1][o]=y;
            } else if(boatLength == 3) {
            boat3check[0][o]=z+o;
            boat3check[1][o]=y;
            } else if(boatLength == 2) {
            boat4check[0][o]=z+o;
            boat4check[1][o]=y;
            }
    } }else {
        for(int o=0; o<boatLength; o++) {
            grid[w][x+o]=boat1a[0][o]; //sets values in grid array to boat array if boat is vertical
            if(boatLength == 5) {
            boat1check[0][o]=w;
            boat1check[1][o]=x+o;
            } else if(boatLength == 4) {
            boat2check[0][o]=w;
            boat2check[1][o]=x+o;
            } else if(boatLength == 3) {
            boat3check[0][o]=w;
            boat3check[1][o]=x+o;
            } else if(boatLength == 2) {
            boat4check[0][o]=w;
            boat4check[1][o]=x+o;
            }
        }
    }
}
void userGuess() {
    char guess[3]; //user guess string
    strcpy(guess, get_string("\e[4;37mInput your guess coordinates below:\e[0m \nExample: (X Y)/(3 4) - Do not include brackets\n\n")); //copies user guess to char array
    system("clear");
    int x = guess[0] - '0'; // converts char input to int
    int y = guess[2] - '0';
    if (grid[y][x] == 'x') { //checks if guess coords have boat
        grid[y][x] = '*'; // prints hit & changes grid coord to * for hit
        guessGrid[y][x] = '*'; // prints hit & changes grid coord to * for hit
        printf("\e[4;32mHit at ");
        printf("%d", x);
        printf(", ");
        printf("%d", y);
        printf("\e[0m\n");
    } else if (grid[y][x] == '~') { //checks if miss
        grid[y][x] = '-'; // prints hit & changes grid coord to - for miss
        guessGrid[y][x] = '-'; // prints hit & changes grid coord to - for miss
        printf("\e[4;31mYou missed!\e[0m\n");
    } else if (grid[y][x] == '*') { //checks if already hit
        printf("\e[4;31mAlready hit!\e[0m\n");
    }
}
void checkIfSunk() {
    //boat 1
if(guessCheck != 5) {
    for(int i = 0; i<5; i++) {
        int y1 = boat1check[1][i]; //sets y1 to stored y coord of boat
        int y2 = boat1check[0][i]; //sets y2 to stored x coord of boat
        if(grid[y2][y1] == '*') { //checks if stored boat coords have hit symbol
            guessCheck ++; //adds 1 to guess check variable
        }
    }
    if(guessCheck == 5) { //if all boat coords have hit marker then print boat sunk
        printf("\e[1;32m\e[4;32mBoat Sunk\e[0m\n");
    } else {
        guessCheck = 0; //reset checking variable to prevent number going above spaces on boat
    }
}
//boat 2 (repetition of boat 1 code but for second boat)
if(guessCheck1 != 4) {
    for(int i = 0; i<4; i++) {
        int y1 = boat2check[1][i];
        int y2 = boat2check[0][i];
        if(grid[y2][y1] == '*') {
            guessCheck1 ++;
        }
    }
    if(guessCheck1 == 4) {
        printf("\e[1;32m\e[4;32mBoat Sunk\e[0m\n");
    } else {
        guessCheck1 = 0;
    }
}
//boat 3
if(guessCheck2 != 3) {
    for(int i = 0; i<3; i++) {
        int y1 = boat3check[1][i];
        int y2 = boat3check[0][i];
        if(grid[y2][y1] == '*') {
            guessCheck2 ++;
        }
    }
    if(guessCheck2 == 3) {
        printf("\e[1;32m\e[4;32mBoat Sunk\e[0m\n");
    } else {
        guessCheck2 = 0;
    }
}
//boat 4
if(guessCheck3 != 2) {
    for(int i = 0; i<2; i++) {
        int y1 = boat4check[1][i];
        int y2 = boat4check[0][i];
        if(grid[y2][y1] == '*') {
            guessCheck3 ++;
        }
    }
    if(guessCheck3 == 2) {
        printf("\e[1;32m\e[4;32mBoat Sunk\e[0m\n");
    } else {
        guessCheck3 = 0;
    }
}
}
void checkGameOver() {
    if(guessCheck == 5){
        if (guessCheck1 == 4) {
            if (guessCheck2 == 3) {
                if (guessCheck3 == 2) {
                    printf("\e[1;32m\e[4;32mGame Over! You win!\e[0m\n");
                    gameOver = 0;
                }
            }
        }
    }
}

// all left to do is make user input guess and check for 'x' in array coordinates
// also need to figure out how to detect if boat is sunk when boats do not have space between them
int main(void) {
    string gameType = get_string("\e[4;37mWhat gamemode would you like to play?\e[0m\n\n Type 'ai' to play against the computer\n Type 'solo' to play without an opponent\n\n");
    if(strcmp(gameType,"solo") == 0) {
        sleep(1);
        system("clear");
        setArray(grid); //creates array
        setArray(guessGrid);
    //placing boats on array, print statements were for checking bugs
        placeBoats(1, (rand() %2), 5);
        placeBoats(2, (rand() %2), 4);
        placeBoats(3, (rand() %2), 3);
        placeBoats(4, (rand() %2), 2);
        do {
            if(gameOver == 0) {
                break;
            }
            printf("\n");
            printArray(guessGrid);
            printf("\n");
                sleep(1);
            userGuess();
                sleep(1);
            checkIfSunk();
            checkGameOver();
        } while(gameOver == 1);
    }
}
