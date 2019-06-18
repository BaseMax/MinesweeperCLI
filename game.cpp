/**
*
* @Name : MinesweeperCLI/game.cpp
* @Version : 1.0
* @Programmer : Max
* @Date : 2019-07-12, 2019-07-17
* @Released under : https://github.com/BaseMax/MinesweeperCLI/blob/master/LICENSE
* @Repository : https://github.com/BaseMax/MinesweeperCLI
*
**/
#include <algorithm>// not required!
// #include <stdlib.h>
// #include <stdio.h>
// #include <time.h>
#include <iostream>
#include <cstdlib> //rand()?
// #include <cstdio>
#include <ctime>
using namespace std;

const unsigned int size=8;// 8 * 8 = 64
// enum Type {BOMB, EMPTY};
#define BOMB        -1
#define SELECTED    -2
#define NUMBER      1
// #define SHOW_BOMBS  1
#define SHOW_BOMBS  0

bool isSelected(int board[size][size], int rowIndex, int columnIndex) {
    if(board[rowIndex][columnIndex] == SELECTED) {
        return true;
    }
    // else {
    //     return false;
    // }
    return false;
}

bool isBomb(int board[size][size], int rowIndex, int columnIndex) {
    if(rowIndex < 0 || columnIndex < 0) {
        return false;
    }
    if(board[rowIndex][columnIndex] == BOMB) {
        return true;
    }
    // else if(board[rowIndex][columnIndex] == SELECTED) {
    //     return false;
    // }
    // else {
    //     return false;
    // }
    return false;
}

int countBomb(int board[size][size], int rowIndex, int columnIndex) {
    // \ 0 1 2
    // 0 # # #
    // 1 # @ #
    // 2 # # #
    int count=0;
    // cout << "Bombs: ";
    for (int _x = rowIndex - 1; _x <= rowIndex+1; _x++) {
        for (int _y = columnIndex -1; _y <= columnIndex+1; _y++) {
            if (_x >= 0 && _x < size && _y >= 0 && _y < size) {
                if (isBomb(board, _x, _y)) {
                    // cout << "(" << _x << ", " << _y << ")\n";
                    count++;
                }
            }
        }
    }
    // for(int x=columnIndex-1; x< columnIndex+1; x++) {
    //     for(int y=rowIndex-1; y< rowIndex+1; y++) {
    //         if(isBomb(board, x, y)) {
    //             cout << "(" << x << ", " << y << ") ";
    //             count++;
    //         }
    //     }
    // }
    // cout << "\n";
    return count;
}

void boardRender(int board[size][size]) {
    cout << "  ";
    for(int index=0; index < size; index++) {
        cout << index << " ";
    }
    cout << "\n";
    for(int rowIndex=0; rowIndex < size; rowIndex++) {
        cout << rowIndex;
        for(int columnIndex=0; columnIndex < size; columnIndex++) {
            cout << "|";
            if(board[rowIndex][columnIndex] == BOMB) {
                #if SHOW_BOMBS
                    cout << "*";
                #else
                    cout << " ";
                #endif
            }
            else if(board[rowIndex][columnIndex] == SELECTED) {
                #if NUMBER
                    cout << countBomb(board, rowIndex, columnIndex);
                #else
                    cout << "#";
                #endif
            }
            else {
                cout << " ";
            }
        }
        cout << "\n";
    }
}

void trim(std::string& input) {
    if(input.empty())
        return;
    int first = 0, last = input.size()  - 1;
    while(first < input.size() && std::isspace(input[first++])); 
    while(last >= 0 && std::isspace(input[last--]));
    if(first > last)
        input = "";
    else {
        first--;
        last++;
        int wi = 0;
        while(first <= last)
            input[wi++] = input[first++];
            input.erase(wi);
    }
    return;
}

int main(int argc, char const *argv[]) {
    // unsigned int width=8;
    // unsigned int height=8;
    srand(time(0)); // Seed
    unsigned int bomb;
    // cout << "How many bomb do you want?";
    // cin >> bomb;
    /*
     E.g: Plans:
        - Easy (bomb=10)
        - Medium (bomb=15)
        - Hard (bomb=20)
        - Very Hard (bomb=50)
    */
    string ask;
    cout << "Choose your level? (easy, medium, hard, veryhard)\n > ";
    cin >> ask;
    // trim(ask);
    transform(ask.begin(), ask.end(), ask.begin(), ::tolower);
    if(ask == "easy") {
        bomb=10;
    }
    else if(ask == "medium") {
        bomb=20;
    }
    else if(ask == "hard") {
        bomb=30;
    }
    else if(ask == "veryhard") {
        bomb=50;
    }
    else {
        bomb=atoi(ask.c_str());
        if(bomb >= (size*size)) {
            bomb=size*size-1;
        }
    }
    cout << bomb << endl;
    int board[size][size]={0};
    int bombFill=0;
    int notBomb=(size*size) - bomb;
    int randomRow;
    int randomColumn;
    // We can optimize it...
    while(bombFill <= bomb) {
        randomRow=rand() % size;
        randomColumn=rand() % size;
        if(board[randomRow][randomColumn] == 0) {
            board[randomRow][randomColumn]=BOMB;
            // We can make it with a better way...
            bombFill++;
        }
        else {
            // Aleady there is a bomb at here...
        }
    }
    int x, y;
    while(true) {
        // cout << "Render:\n";
        // boardRender(board);
        // for(int w=0; w<= size; w++) {
        //     for(int h=0; h<= size; h++) {
        //         cout << "Bombs of " << w << ", " << h << ": ";
        //         cout << countBomb(board, w, h);
        //         cout << "\n";
        //     }
        // }
        boardRender(board);
        cout << "Enter your positions:\nX> ";
        cin >> x;
        cout << "Y> ";
        cin >> y;
        if(isBomb(board, x, y)) {
            cout << "GAME OVER!\n";
            break;
        }
        else if(isSelected(board, x, y)) {
            cout << "Danger: Aleady selected!\n";
        }
        else {
            board[x][y]=SELECTED;
        }
        #ifdef _WIN32
            system("cls");
        #elif __linux__
            cout << "\033[2J";
            // system("clear");
        #endif
    }
    return 0;
}
