// Max Base
// https://github.com/BaseMax/MinesweeperCLI
#include <algorithm>
// #include <stdlib.h>
// #include <stdio.h>
// #include <time.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;

const unsigned int size=8;// 8 * 8 = 64
// enum Type {BOMB, EMPTY};
#define BOMB -1

void boardRender(int board[size][size]) {
	cout << size << "\n";
	cout << "  ";
	for(int index=0; index < size; index++) {
		cout << index << " ";
	}
	cout << "\n";
	for(int rowIndex=0; rowIndex < size; rowIndex++) {
		cout << rowIndex;
		for(int columnIndex=0; columnIndex < size; columnIndex++) {
			cout << "|";
			if(board[rowIndex][columnIndex] == -1) {
				cout << "*";
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
	cout << "Render:\n";
	boardRender(board);
	return 0;
}
