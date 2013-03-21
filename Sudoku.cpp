/*
 * Sudoku.cpp
 *
 *  Created on: 24 Feb 2013
 *      Author: arjun212
 */

#include <iostream>
#include <sstream>
using namespace std;

int input[9][9];
string posse[9][9];

void printin(int a[9][9]) {
	for (int i = 0; i < 9; i++) {
		if ((i % 3) == 0) {
			cout << endl << endl;
		} else {
			cout << endl;
		}
		for (int j = 0; j < 9; j++) {
			if (((j + 1) % 3) == 0) {
				cout << a[i][j] << "   ";
			} else {
				cout << a[i][j] << " ";
			}
		}
	}
}

void printstr(string a[9][9]) {
	for (int i = 0; i < 9; i++) {
		if ((i % 3) == 0) {
			cout << endl << endl;
		} else {
			cout << endl;
		}
		for (int j = 0; j < 9; j++) {
			if (((j + 1) % 3) == 0) {
				cout << a[i][j] << "   ";
			} else {
				cout << a[i][j] << " ";
			}
		}
	}
}

string convertInt(int a) {
	stringstream ss;
	ss << a;
	return ss.str();
}

void setArray(int a[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			a[i][j] = input[i][j];
		}
	}
}

int findQuadrant(int x, int y) {
	int result = 0;
	if (x < 3) {
		result = 0;
	} else if (x < 6) {
		result = 30;
	} else if (x < 9) {
		result = 60;
	}

	if (y < 3) {
		result += 0;
	} else if (y < 6) {
		result += 3;
	} else if (y < 9) {
		result += 6;
	}
	return result;
}

string remove(string initial, char toremove) {
	string result = "";
	for (unsigned int i = 0; i < initial.length(); i++) {
		if (initial[i] != toremove) {
			result += initial[i];
		}
	}
	return result;
}

string removeString(string initial, string toremove) {
	string result = initial;
	for (unsigned int i = 0; i < toremove.length(); i++) {
		result = remove(result, toremove[i]);
	}
	return result;
}

bool hasChanges(int a[9][9], int b[9][9]) {
	int suma = 0;
	int sumb = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			suma += a[i][j];
			sumb += b[i][j];
		}
	}
	return (suma != sumb);
}

int update() {
	int count = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (posse[i][j].length() == 1) {
				if (input[i][j] == 0) {
					count++;
				}
				stringstream(posse[i][j]) >> input[i][j];
			}
		}
	}
	if (count > 0) {
		return 1;
	} else {
		return 0;
	}
}

int duplicateR(int a[9][9], int value, int row) {
	int count = 0;
	for (int i = 0; i < 9; i++) {
		if (a[row][i] == value) {
			count++;
		}
	}
	if (count == 1) {
		return 0;
	} else {
		return 1;
	}
}

int duplicateC(int a[9][9], int value, int col) {
	int count = 0;
	for (int i = 0; i < 9; i++) {
		if (a[i][col] == value) {
			count++;
		}
	}
	if (count == 1) {
		return 0;
	} else {
		return 1;
	}
}

int duplicateS(int a[9][9], int value, int row, int col) {
	int Ori = findQuadrant(row, col);
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (a[i + ((Ori - (Ori % 10)) / 10)][j + (Ori % 10)] == value) {
				count++;
			}
		}
	}
	if (count == 1) {
		return 0;
	} else {
		return 1;
	}
}

int check(int a[9][9]) {
	int count = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (a[i][j] != 0) {
				int val = a[i][j];
				int row = i;
				int col = j;
				count += duplicateR(a, val, row);
				count += duplicateC(a, val, col);
				count += duplicateS(a, val, row, col);
			}
		}
	}
	if (count == 0) {
		return 1;
	} else {
		return 0;
	}
}

void simplifyR(int row) {
	string foundCells = "";
	for (int i = 0; i < 9; i++) {
		if (posse[row][i].length() == 1) {
			foundCells += posse[row][i];
		}
	}
	for (int i = 0; i < 9; i++) {
		if (posse[row][i].length() != 1) {
			posse[row][i] = removeString(posse[row][i], foundCells);
		}
	}
}

void simplifyC(int col) {
	string foundCells = "";
	for (int i = 0; i < 9; i++) {
		if (posse[i][col].length() == 1) {
			foundCells += posse[i][col];
		}
	}
	for (int i = 0; i < 9; i++) {
		if (posse[i][col].length() != 1) {
			posse[i][col] = removeString(posse[i][col], foundCells);
		}
	}
}

void simplifyS(int row, int col) {
	int Ori = findQuadrant(row, col);
	int a = ((Ori - (Ori % 10)) / 10);
	int b = (Ori % 10);
	string foundCells = "";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (posse[i + a][j + b].length() == 1) {
				foundCells += posse[i + a][j + b];
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (posse[i + a][j + b].length() != 1) {
				posse[i + a][j + b] = removeString(posse[i + a][j + b],
						foundCells);
			}
		}
	}

}

void simplify() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			simplifyR(i);
			simplifyC(j);
			simplifyS(i, j);
		}
	}
	update();
}

void singletonR(int row) {
	string foundCells = "";
	string foundSingles = "";
	int count[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 9; i++) {
		if (posse[row][i].length() != 1) {
			foundCells += posse[row][i];
		}
	}

	for (unsigned int i = 0; i < foundCells.length(); i++) {
		count[foundCells[i] - '1']++;
	}

	for (int i = 0; i < 9; i++) {
		if (count[i] == 1) {
			foundSingles += convertInt(i + 1);
		}
	}

	for (unsigned int i = 0; i < foundSingles.length(); i++) {
		for (int j = 0; j < 9; j++) {
			if (posse[row][j] != remove(posse[row][j], foundSingles[i])) {
				posse[row][j] = foundSingles[i];
			}
		}
	}
}

void singletonC(int col) {
	string foundCells = "";
	string foundSingles = "";
	int count[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 9; i++) {
		if (posse[i][col].length() != 1) {
			foundCells += posse[i][col];
		}
	}

	for (unsigned int i = 0; i < foundCells.length(); i++) {
		count[foundCells[i] - '1']++;
	}

	for (int i = 0; i < 9; i++) {
		if (count[i] == 1) {
			foundSingles += convertInt(i + 1);
		}
	}

	for (unsigned int i = 0; i < foundSingles.length(); i++) {
		for (int j = 0; j < 9; j++) {
			if (posse[j][col] != remove(posse[j][col], foundSingles[i])) {
				posse[j][col] = foundSingles[i];
			}
		}
	}
}

void singletonS(int row, int col) {
	int Ori = findQuadrant(row, col);
	int a = ((Ori - (Ori % 10)) / 10);
	int b = (Ori % 10);
	string foundCells = "";
	string foundSingles = "";
	int count[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (posse[i + a][j + b].length() != 1) {
				foundCells += posse[i + a][j + b];
			}
		}
	}

	for (unsigned int i = 0; i < foundCells.length(); i++) {
		count[foundCells[i] - '1']++;
	}

	for (int i = 0; i < 9; i++) {
		if (count[i] == 1) {
			foundSingles += convertInt(i + 1);
		}
	}

	for (unsigned int i = 0; i < foundSingles.length(); i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				if (posse[j + a][k + b]
						!= remove(posse[j + a][k + b], foundSingles[i])) {
					posse[j + a][k + b] = foundSingles[i];
				}
			}

		}
	}
}

void singleton() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			singletonR(i);
			simplify();
			singletonC(j);
			simplify();
			singletonS(i, j);
			simplify();
		}
	}
	update();
}

int main() {

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			input[i][j] = 0;
			posse[i][j] = "123456789";
		}
	}

	input[0][0] = 1;
	input[1][0] = 2;
	input[4][0] = 8;
	input[8][0] = 3;
	input[3][1] = 5;
	input[4][1] = 2;
	input[8][1] = 6;
	input[2][2] = 8;
	input[6][2] = 7;
	input[7][3] = 3;
	input[0][4] = 4;
	input[1][4] = 5;
	input[4][4] = 6;
	input[7][4] = 8;
	input[8][4] = 9;
	input[1][5] = 9;
	input[2][6] = 2;
	input[6][6] = 1;
	input[0][7] = 7;
	input[4][7] = 9;
	input[5][7] = 8;
	input[0][8] = 6;
	input[4][8] = 3;
	input[7][8] = 9;
	input[8][8] = 2;

	posse[0][0] = "1";
	posse[1][0] = "2";
	posse[4][0] = "8";
	posse[8][0] = "3";
	posse[3][1] = "5";
	posse[4][1] = "2";
	posse[8][1] = "6";
	posse[2][2] = "8";
	posse[6][2] = "7";
	posse[7][3] = "3";
	posse[0][4] = "4";
	posse[1][4] = "5";
	posse[4][4] = "6";
	posse[7][4] = "8";
	posse[8][4] = "9";
	posse[1][5] = "9";
	posse[2][6] = "2";
	posse[6][6] = "1";
	posse[0][7] = "7";
	posse[4][7] = "9";
	posse[5][7] = "8";
	posse[0][8] = "6";
	posse[4][8] = "3";
	posse[7][8] = "9";
	posse[8][8] = "2";

	printin(input);


	int b[9][9];
	setArray(b);
	singleton();
	while (hasChanges(input,b)) {
		setArray(b);
		singleton();
	}


	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	printin(input);
	cout << endl;
	cout << endl;
	printstr(posse);

	return 0;
}

