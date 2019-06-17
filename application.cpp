/**
*
* @Name : MinesweeperCLI/application.cpp
* @Version : 1.0
* @Programmer : Max
* @Date : 2018-07-17
* @Released under : https://github.com/BaseMax/MinesweeperCLI/blob/master/LICENSE
* @Repository : https://github.com/BaseMax/MinesweeperCLI
*
**/
#include <iostream>
#include <algorithm>
// #include <stdlib.h>
// #include <stdio.h>
// #include <time.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

const int size = 8;

int main() {
	int board[size][size] = {-10};
	int selected[size][size] = {0};
	srand(time(0));
	int boms;
	cin >> boms;
	int bombsCount = 0;
	int rand1, rand2;
	if (boms >= size*size) {
		cout << "Error: Bad values!\n";
		system("pause");
		return 0;
	}
	while (bombsCount < boms) {
		rand1 = rand() % size;// row
		rand2 = rand() % size;// column
		if (board[rand1][rand2] != -1) {
			board[rand1][rand2] = -1;
			// cout << "(" << rand1 << ", " << rand2 << ")" << "\n";
			bombsCount++;
		}
	}
	int wins = 0;
	while (true) {
		#ifdef _WIN32
			system("cls");
		#elif __linux__
			// cout << "\033[2J";
			system("clear");
		#endif
		cout << "  ";
		for (int x = 0; x < size; x++) {
			cout << x << "|";
		}
		cout << "\n";
		for (int x = 0; x < size; x++) {
			cout << x << "|";
			for (int y = 0; y < size; y++) {
				if (board[x][y] == -1) {
					cout << "#";
				}
				else if (board[x][y] >= 0 && selected[x][y] == true) {
					cout << board[x][y];
				}
				else {
					cout << " ";
				}
				cout << "|";
			}
			cout << "\n";
		}

		int x, y;
		cout << "Enter your position:\n> ";
		cin >> x;
		cout << "> ";
		cin >> y;
		if (board[x][y] == -1) {
			cout << "Error: Game Over!\n";
			break;
		}
		else {
			int number = 0;
			if (x >= 0 && x < size && y >= 0 && y < size) {
				/*
				if (x > 0 && y > 0 && board[x - 1][y - 1] == -1) number++;
				if (x > 0 && board[x - 1][y] == -1) number++;
				if (x > 0 && y > 0 && y < size - 1 && board[x - 1][y + 1] == -1) number++;

				if (y > 0 && board[x][y - 1] == -1) number++;
				if (board[x][y] == -1) number++;
				if (y < size - 1 && board[x][y + 1] == -1) number++;

				if (x < size - 1 && y > 0 && board[x + 1][y - 1] == -1) number++;
				if (x < size-1 && board[x + 1][y] == -1) number++;
				if (x < size-1 && y < size-1 && board[x + 1][y + 1] == -1) number++;
				*/
				for (int _x = x - 1; _x <= x+1; _x++) {
					for (int _y = y -1; _y <= y+1; _y++) {
						if (_x >= 0 && _x < size && _y >= 0 && _y < size) {
							if (board[_x][_y] == -1) {
								cout << "(" << _x << ", " << _y << ")\n";
								number++;
							}
						}
					}
				}
				wins++;
				if (wins == (size*size) - bombsCount) {
					cout << "Win!\n";
					break;
				}
				selected[x][y] = true;
				board[x][y] = number;
			}
			else {
				// cout << "Error!\n";
				// break;
			}
		}
	}
	cin.get();
	cin.get();
	return 0;
}
