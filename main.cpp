#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>

using namespace std;

//GLOBAL VARIABLES AND CONSTS
const int CAPACITY = 9;
bool backTracking = false;
int row = 0;
int column = -1;
bool setOriginalNumToOneNextTurn = true;


//FUNCTION DECLARATIONS
void setStartingNums(char[CAPACITY][CAPACITY], bool[CAPACITY][CAPACITY]);
//setStartingNums - Allows user to input starting numbers in to a position which they choose
//@param board[2][CAPACITY][CAPACITY] - sudoku board data

void printBoard(char[CAPACITY][CAPACITY]);
//printBoard - prints board
//@pararm char board[CAPACITY][CAPACITY] - sudoku board data

void solve(char[CAPACITY][CAPACITY], bool[CAPACITY][CAPACITY]);
//solve - recursive function that controls everything
//@pararm char board[CAPACITY][CAPACITY] - sudoku board data

bool solved(char[CAPACITY][CAPACITY]);
//solved - tells if board has been solved
//@pararm char board[CAPACITY][CAPACITY] - sudoku board data
//@return bool - true if puzzle solved, false if not

bool isLegal(char[CAPACITY][CAPACITY]);
//isLegal - determines if the number that was just put in the current spot is legal
//@pararm char board[CAPACITY][CAPACITY] - sudoku board data
//@return bool - if it is legal or not

void backTrack();
//backTrack - moves the row and column pointers to the previous entry

void forwardTrack();
//forwardTrack - moves the row and column pointers to the next entry

void increaseVal(char board[CAPACITY][CAPACITY]);
//increaseVal - increases value of the entry indexed by 'row' and 'column'
//@pararm char board[CAPACITY][CAPACITY] - sudoku board data

int main(){

    char board[CAPACITY][CAPACITY];
    bool overRightable[CAPACITY][CAPACITY];

    for(int i = 0; i < 9; i++){
        for(int f = 0; f < 9; f++){
            board[i][f] = '0';
            board[i][f] = '0';
            overRightable[i][f] = true;
        }
    }

    setStartingNums(board, overRightable);

    if(isLegal(board)){
        solve(board, overRightable);
        printBoard(board);
        cout << endl;
        cout << "Congratulations!! Your puzzle has been solved!!" << endl;
        system("pause");
    }else
        cout << "The board entered is invalid";

}

void solve(char board[CAPACITY][CAPACITY], bool overRightable[CAPACITY][CAPACITY]){

    while(!solved(board)){
        backTracking? backTrack() : forwardTrack();
        if(backTracking && board[row][column] == '9')
            backTracking = true;
        else{
            if(overRightable[row][column]){
                backTracking = false;
                //find and apply legal move if there is one. if there isn't backtrack
                while(board[row][column] != '9'){
                    increaseVal(board);
                    if(isLegal(board)) break;
                }
                if(!isLegal(board)){
                    backTracking = true;
                    board[row][column] = '0';
                }
            }
        }
    }
}

bool solved(char board[CAPACITY][CAPACITY]){

    for(int i = 0; i < CAPACITY; i++){
        for(int u = 0; u < CAPACITY; u++){

            if(board[i][u] == '0'){
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

void printBoard(char board[CAPACITY][CAPACITY]){
    cout << endl;
    for(int i = 0; i < CAPACITY; i++){
        cout << " ";
        for(int j = 0; j < CAPACITY; j++){
            cout << ZeroToSpaceKey(board[i][j]) << " | ";
        }
        cout << "\n-----------------------------------" << endl;

    }
}

bool isLegal(char board[CAPACITY][CAPACITY]){

    int numOccurances[CAPACITY];

    //check that all columns contain unique elements
    for(int icol = 0; icol < 9; icol++){
        //clear numOccurances because moving to next col
        for(int i = 0; i < 9; i++)
            numOccurances[i] = 0;

        //set numOccurances for the column icol
        for(int i = 1; i < 10; i++){
            for(int irow = 0; irow < 9; irow++){
                if((board[irow][icol] - '0') == i)
                    numOccurances[i-1]++;
            }
        }

        //make sure the column icol has no more than one occurance of a digit
        for(int i = 0; i < 9; i++){
            if(numOccurances[i] > 1)
                return false;
        }
    }

    //check that all columns contain unique elements
    for(int irow = 0; irow < 9; irow++){
        //clear numOccurances because moving to next col
        for(int i = 0; i < 9; i++)
            numOccurances[i] = 0;

        //set numOccurances for the column icol
        for(int i = 1; i < 10; i++){
            for(int icol = 0; icol < 9; icol++){
                if((board[irow][icol] - '0') == i)
                    numOccurances[i-1]++;
            }
        }

        //make sure the column icol has no more than one occurance of a digit
        for(int i = 0; i < 9; i++){
            if(numOccurances[i] > 1)
                return false;
        }
    }

    //check that boxes contain unnique elements
    for(int digit = 1; digit < 10; digit++){
        for(int offset1 = 0; offset1 < 7; offset1 += 3){
            for(int offset2 = 0; offset2 < 7; offset2 += 3){
                //clear numOccurances because moving to next box
                for(int i = 0; i < 9; i++)
                    numOccurances[i] = 0;
                //calculate numOccurances
                for(int i = 0 + offset1; i < 3 + offset1; i++){
                    for(int j = 0 + offset2; j < 3 + offset2; j++){
                        if((board[i][j] - '0') == digit) numOccurances[digit-1]++;
                    }
                }

                for(int i = 0; i < 9; i++){
                    if(numOccurances[i] > 1)
                        return false;
                }
            }
        }
    }
    return true;

}

void setStartingNums(char board[CAPACITY][CAPACITY], bool overRightable[CAPACITY][CAPACITY]){

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
    char temp;

    while(!quit){

        int y = 's';
        cout << "Enter the row of the entry to set or enter s to solve puzzle\n";
        while(!(cin >> y)){
            cin.clear();
            cin.ignore(123, '\n');
            cout << "solve? (y/n)\n";
            cin >> temp;
            if(temp == 'y'){
                 quit = true;
                 break;
            }

            cin.clear();
            cin.ignore(123, '\n');
            cout << "You must enter a digit\n";
        }
        if(quit) break;

        int x = 's';
        cout << "Enter the column of the entry to set or enter s to solve\n";
        while(!(cin >> x)){
            cin.clear();
            cin.ignore(123, '\n');
            cout << "solve? (y/n)\n";
            cin >> temp;
            if(temp == 'y'){
                 quit = true;
                 break;
            }

            cin.clear();
            cin.ignore(123, '\n');
            cout << "You must enter a digit\n";
        }
        if(quit) break;

        int val;
        cout << "Enter a value to put in that spot or enter s to solve\n";
        while(!(cin >> val)){
            cin.clear();
            cin.ignore(123, '\n');
            cout << "solve? (y/n)\n";
            cin >> temp;
            if(temp == 'y'){
                 quit = true;
                 break;
            }

            cin.clear();
            cin.ignore(123, '\n');
            cout << "You must enter a digit\n";
        }

        if(!quit){
            char aChar = '0' + val;
            board[y -1][x-1] = aChar;
            overRightable[y-1][x-1] = false;
        }

        cout << "The board with your entry added looks like this: ";
        printBoard(board);

    }
    cout << endl;
}

void backTrack(){
    if(column == 0){
        row--;
        column = 8;
    }else
        column--;
}

void forwardTrack(){
    if(column == 8){
        row++;
        column = 0;
    }else
        column++;
}

void increaseVal(char board[CAPACITY][CAPACITY]){
    board[row][column] += 1;
}
