#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>

using namespace std;

//GLOBAL VARIABLES AND CONSTS
const int CAPACITY = 9;
int backTrack = 0;
int row = 0;
int column = 0;
bool setOriginalNumToOneNextTurn = true;


//FUNCTION DECLARATIONS
void setStartingNums(char[2][CAPACITY][CAPACITY], bool[CAPACITY][CAPACITY]);
//setStartingNums - Allows user to input starting numbers in to a position which they choose
//@param board[2][CAPACITY][CAPACITY] - sudoku board data

void printBoard(char[2][CAPACITY][CAPACITY]);
//printBoard - prints board
//@pararm char board[CAPACITY][CAPACITY] - sudoku board data

void solve(char[2][CAPACITY][CAPACITY], bool[CAPACITY][CAPACITY]);
//solve - recursive function that controls everything
//@pararm char board[CAPACITY][CAPACITY] - sudoku board data

void getNumber(char[2][CAPACITY][CAPACITY], bool[CAPACITY][CAPACITY]);
//getNumber - gets next number
//@pararm char board[CAPACITY][CAPACITY] - sudoku board data

void setSpot(char[2][CAPACITY][CAPACITY], bool[CAPACITY][CAPACITY]);
//getSpot - gets next or previous spot based on backtrack bool
//@pararm char board[CAPACITY][CAPACITY] - sudoku board data

void testValues(char[2][CAPACITY][CAPACITY], bool[CAPACITY][CAPACITY]);
//tryValues returns false if no value fits
//@pararm char board[CAPACITY][CAPACITY] - sudoku board data

bool solved(char[2][CAPACITY][CAPACITY]);
//solved - tells if board has been solved
//@pararm char board[CAPACITY][CAPACITY] - sudoku board data
//@return bool - true if puzzle solved, false if not

bool isLegal(char[2][CAPACITY][CAPACITY]);
//isLegal - determines if the number that was just put in the current spot is legal
//@pararm char board[CAPACITY][CAPACITY] - sudoku board data
//@return bool - if it is legal or not
 void notOverRightable(char board[2][CAPACITY][CAPACITY]);
 //notOverRightable - does protocal for when program comes across a spot that isnt overRightable
 //@param char board[CAPACITY][CAPACITY] - sudoku board data


int main(){

    char board[2][CAPACITY][CAPACITY];
    bool overRightable[CAPACITY][CAPACITY];

    for(int i = 0; i < 9; i++){
        for(int f = 0; f < 9; f++){
            board[0][i][f] = '0';
            board[1][i][f] = '0';
            overRightable[i][f] = true;
        }
    }

    setStartingNums(board, overRightable);

    solve(board, overRightable);

    printBoard(board);
    cout << endl;
    cout << "Congratulations!! Your puzzle has been solved!!" << endl;

}

void solve(char board[2][CAPACITY][CAPACITY], bool overRightable[CAPACITY][CAPACITY]){

    while(!solved(board)){

        setSpot(board, overRightable);

        if(overRightable[row][column]){

            getNumber(board, overRightable);

            testValues(board, overRightable);

        }else{
            notOverRightable(board);
        }

        solve(board, overRightable);

        }

}

void setSpot(char board[2][CAPACITY][CAPACITY], bool overRightable[CAPACITY][CAPACITY]){

    if(backTrack == 1){
        //go back 1 spot

        if(column == 0){
            column = 8;
            row--;
        }else{
            column--;
        }

    }

    if(backTrack == 0){
        //go to next spot
        //before this we need to store the number it has and set the proper used num s

        if(column == 8){
            column = 0;
            row++;
        }else{
            column++;
        }
    }
    //when backtrack is set to 2 it means keep the same spot and will keep looping through numbers

    if(backTrack == 0){
        if(board[1][row][column] == '0'){
            board[1][row][column] = board[0][row][column];
            setOriginalNumToOneNextTurn = true;

        }

    }
}

void getNumber(char board[2][CAPACITY][CAPACITY], bool overRightable[CAPACITY][CAPACITY]){



    if(board[0][row][column] == '9'){
        board[0][row][column] = '1';
    }else{
        board[0][row][column]++;
    }

}

void testValues(char board[2][CAPACITY][CAPACITY], bool overRightable[CAPACITY][CAPACITY]){

    if(isLegal(board)){
        backTrack = 0;
    }else{
        backTrack = 2;
    }

    //case for when no number is legal in that spot
    //has to set backtrack to 1;

    if(board[0][row][column] == board[1][row][column]){
        backTrack = 1;
        board[0][row][column] = '0';
        board[1][row][column] = '0';
    }

    if(setOriginalNumToOneNextTurn){
            board[1][row][column] = '1';
    }
    setOriginalNumToOneNextTurn = false;
}

bool solved(char board[2][CAPACITY][CAPACITY]){

    for(int i = 0; i < CAPACITY; i++){
        for(int u = 0; u < CAPACITY; u++){

            if(board[0][i][u] == '0'){
            return false;
            }
        }
    }
    return true;

}

char ZeroToSpaceKey(char character){
    if(character == '0')
        return ' ';
    else
        return character;
}

void printBoard(char board[2][CAPACITY][CAPACITY]){
    cout << endl;
    for(int i = 0; i < CAPACITY; i++){
        cout << " ";
        for(int j = 0; j < CAPACITY; j++){
            cout << ZeroToSpaceKey(board[0][i][j]) << " | ";
        }
        cout << "\n-----------------------------------" << endl;

    }
}

bool isLegal(char board[2][CAPACITY][CAPACITY]){

    char num = board[0][row][column];
    int counter = 0;
    int box;

    for(int i = 0; i < 9; i++){

        if(board[0][row][i] == num){
            counter++;
        }
        if(counter > 1){
            return false;
        }

    }

    counter = 0;

    for(int o = 0; o < 9; o++){

        if(board[0][o][column] == num){
            counter++;
        }
        if(counter > 1){
            return false;
        }

    }

    counter = 0;

    if(row == 0 || row == 1 || row == 2){
        if(column == 0 || column == 1 || column == 2){box = 0;}
        if(column == 3 || column == 4 || column == 5){box = 1;}
        if(column == 6 || column == 7 || column == 8){box = 2;}

    }

    if(row == 3 || row == 4 || row == 5){
        if(column == 0 || column == 1 || column == 2){box = 3;}
        if(column == 3 || column == 4 || column == 5){box = 4;}
        if(column == 6 || column == 7 || column == 8){box = 5;}

    }

    if(row == 6 || row == 7 || row == 8){
        if(column == 0 || column == 1 || column == 2){box = 6;}
        if(column == 3 || column == 4 || column == 5){box = 7;}
        if(column == 6 || column == 7 || column == 8){box = 8;}

    }

    //box has been set

    switch(box){

        case 0:

            if(board[0][0][0] == num){counter++;}
            if(board[0][0][1] == num){counter++;}
            if(board[0][0][2] == num){counter++;}
            if(board[0][1][0] == num){counter++;}
            if(board[0][1][1] == num){counter++;}
            if(board[0][1][2] == num){counter++;}
            if(board[0][2][0] == num){counter++;}
            if(board[0][2][1] == num){counter++;}
            if(board[0][2][2] == num){counter++;}
            break;

        case 1:

            if(board[0][0][3] == num){counter++;}
            if(board[0][0][4] == num){counter++;}
            if(board[0][0][5] == num){counter++;}
            if(board[0][1][3] == num){counter++;}
            if(board[0][1][4] == num){counter++;}
            if(board[0][1][5] == num){counter++;}
            if(board[0][2][3] == num){counter++;}
            if(board[0][2][4] == num){counter++;}
            if(board[0][2][5] == num){counter++;}
            break;

        case 2:

            if(board[0][0][6] == num){counter++;}
            if(board[0][0][7] == num){counter++;}
            if(board[0][0][8] == num){counter++;}
            if(board[0][1][6] == num){counter++;}
            if(board[0][1][7] == num){counter++;}
            if(board[0][1][8] == num){counter++;}
            if(board[0][2][6] == num){counter++;}
            if(board[0][2][7] == num){counter++;}
            if(board[0][2][8] == num){counter++;}
            break;

        case 3:

            if(board[0][3][0] == num){counter++;}
            if(board[0][3][1] == num){counter++;}
            if(board[0][3][2] == num){counter++;}
            if(board[0][4][0] == num){counter++;}
            if(board[0][4][1] == num){counter++;}
            if(board[0][4][2] == num){counter++;}
            if(board[0][5][0] == num){counter++;}
            if(board[0][5][1] == num){counter++;}
            if(board[0][5][2] == num){counter++;}
            break;

        case 4:

            if(board[0][3][3] == num){counter++;}
            if(board[0][3][4] == num){counter++;}
            if(board[0][3][5] == num){counter++;}
            if(board[0][4][3] == num){counter++;}
            if(board[0][4][4] == num){counter++;}
            if(board[0][4][5] == num){counter++;}
            if(board[0][5][3] == num){counter++;}
            if(board[0][5][4] == num){counter++;}
            if(board[0][5][5] == num){counter++;}
            break;

        case 5:

            if(board[0][3][6] == num){counter++;}
            if(board[0][3][7] == num){counter++;}
            if(board[0][3][8] == num){counter++;}
            if(board[0][4][6] == num){counter++;}
            if(board[0][4][7] == num){counter++;}
            if(board[0][4][8] == num){counter++;}
            if(board[0][5][6] == num){counter++;}
            if(board[0][5][7] == num){counter++;}
            if(board[0][5][8] == num){counter++;}
            break;

        case 6:

            if(board[0][6][0] == num){counter++;}
            if(board[0][6][1] == num){counter++;}
            if(board[0][6][2] == num){counter++;}
            if(board[0][7][0] == num){counter++;}
            if(board[0][7][1] == num){counter++;}
            if(board[0][7][2] == num){counter++;}
            if(board[0][8][0] == num){counter++;}
            if(board[0][8][1] == num){counter++;}
            if(board[0][8][2] == num){counter++;}
            break;

        case 7:

            if(board[0][6][3] == num){counter++;}
            if(board[0][6][4] == num){counter++;}
            if(board[0][6][5] == num){counter++;}
            if(board[0][7][3] == num){counter++;}
            if(board[0][7][4] == num){counter++;}
            if(board[0][7][5] == num){counter++;}
            if(board[0][8][3] == num){counter++;}
            if(board[0][8][4] == num){counter++;}
            if(board[0][8][5] == num){counter++;}
            break;

        case 8:

            if(board[0][6][6] == num){counter++;}
            if(board[0][6][7] == num){counter++;}
            if(board[0][6][8] == num){counter++;}
            if(board[0][7][6] == num){counter++;}
            if(board[0][7][7] == num){counter++;}
            if(board[0][7][8] == num){counter++;}
            if(board[0][8][6] == num){counter++;}
            if(board[0][8][7] == num){counter++;}
            if(board[0][8][8] == num){counter++;}
            break;

    }

    if(counter > 1){
            return false;
        }

    return true;
}

void setStartingNums(char board[2][CAPACITY][CAPACITY], bool overRightable[CAPACITY][CAPACITY]){

    cout << "The board look like this: \n" << endl;
    cout << "       [1] [2] [3] [4] [5] [6] [7] [8] [9] \n      -------------------------------------" << endl;
    cout << " [1]      |   |   |   |   |   |   |   |   \n      -------------------------------------" << endl;
    cout << " [2]      |   |   |   |   |   |   |   |   \n      -------------------------------------" << endl;
    cout << " [3]      |   |   |   |   |   |   |   |   \n      -------------------------------------" << endl;
    cout << " [4]      |   |   |   |   |   |   |   |   \n      -------------------------------------" << endl;
    cout << " [5]      |   |   |   |   |   |   |   |   \n      -------------------------------------" << endl;
    cout << " [6]      |   |   |   |   |   |   |   |   \n      -------------------------------------" << endl;
    cout << " [7]      |   |   |   |   |   |   |   |   \n      -------------------------------------" << endl;
    cout << " [8]      |   |   |   |   |   |   |   |   \n      -------------------------------------" << endl;
    cout << " [9]      |   |   |   |   |   |   |   |   " << endl;
    cout << "row and column numbers are indicated, set the starting values: \n";

    bool quit = false;
    while(!quit){

        int y;
        char temp;
        cout << "Enter the row of the entry to set or enter q to quit\n";

        while(!(cin >> y)){
            cin.clear();
            cin.ignore(123, '\n');
            cout << "would you like to quit (y/n)";
            cin >> temp;
            if(temp == 'y'){
                quit = true;
                break;
            }
            cout << "you need to enter a digit or enter q to quit\n";
        }
        if(quit) break;

        cout << "Enter the column of the entry to set or enter q to quit\n";

        int x;
        while(!(cin >> x)){
            cin.clear();
            cin.ignore(123, '\n');
            cout << "would you like to quit (y/n). ";
            cin.get(temp);
            if(temp == 'y'){
                quit = true;
                break;
            }
            cout << "you need to enter a digit or enter q to quit\n";
        }
        if(quit) break;

        char val;
        cout << "Enter a value to put in that spot: ";
        while(!(cin >> val)){
            cin.clear();
            std::cin.ignore(123, '\n');
            cout << "would you like to quit (y/n)";
            cin >> temp;
            if(temp == 'y'){
                quit = true;
                break;
            }
            cout << "Enter a digit to put in that spot: ";
            cin >> val;
        }

        board[0][y -1][x-1] = val;
        overRightable[y-1][x-1] = false;

        cout << "The board with your entry added looks like this: ";
        printBoard(board);

    }

    cout << "Sucess you have entered all of your starting numbers!!" << endl;


}

void notOverRightable(char board[2][CAPACITY][CAPACITY]){

    if(isLegal(board)){

        if(backTrack == 1){
            //do nothing just keep backtrask at 1
        }

        if(backTrack == 0){
            //do nothing just keep backtrack at 0
        }

         if(backTrack == 2){
            backTrack = 0;
        }

    }else{

        if(backTrack == 1){
            //doNothing
        }

        if(backTrack == 0){
            backTrack = 1;
        }
    }
}



