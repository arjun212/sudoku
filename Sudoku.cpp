/*
 * Sudoku.cpp
 *
 *  Created on: 24 Feb 2013
 *      Author: arjun212
 */

#include <iostream>
#include <sstream>
#include <ctime>
#include <time.h>
using namespace std;

int input[9][9];
string posse[9][9];

struct posseVals {
	string value;
	int row;
	int col;
	bool exists;
};

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

int convertStr(string a) {
	istringstream buffer(a);
	int value;
	buffer >> value;
	return value;
}

int convertChar(char a) {
	return (a - '0');
}

void setArray(int a[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			a[i][j] = input[i][j];
		}
	}
}

void setInput(int a[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			input[i][j] = a[i][j];
		}
	}
}

void setString(string a[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			a[i][j] = posse[i][j];
		}
	}
}

void setArrayPosse(string a[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			posse[i][j] = a[i][j];
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

bool update() {
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
	return (count > 0);
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

bool isSolved(int a[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (a[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

bool check(int a[9][9]) {
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
	return (count == 0);
}

bool isValid(int in[9][9]) {
	if (check(in) && isSolved(in)) {
		int rowtot = 0, coltot = 0;
		for (int i = 0; i < 9; i++) {
			rowtot = 0;
			coltot = 0;
			for (int j = 0; j < 9; j++) {
				rowtot += in[i][j];
				coltot += in[j][i];
			}
			if (rowtot != 45) {
				return false;
			}
			if (coltot != 45) {
				return false;
			}
		}
		int orivals[9] = { 0, 3, 6, 30, 33, 36, 60, 63, 66 };
		int squatot = 0;
		for (int i = 0; i < 9; i++) {
			int a = ((orivals[i] - (orivals[i] % 10)) / 10);
			int b = (orivals[i] % 10);
			squatot = 0;
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					squatot += in[a + j][b + k];
				}
			}
			if (squatot != 45) {
				return false;
			}
		}

		return true;
	}
	return false;
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
		simplify();
	}
	update();
}

bool backtrack(int a[9][9]);

bool solveSudoku() {
	int b[9][9];
	setArray(b);
	singleton();
	setArray(b);
	update();
	while (hasChanges(input, b)) {
		setArray(b);
		singleton();
		update();
	}
	if (!isSolved(input)) {
		backtrack(input);
	}
	return (isSolved(input));
}

posseVals findUnassigned(int a[9][9]) {
	bool unassignedFound = false;
	int i = 0;
	int j = 0;
	posseVals result;
	result.exists = false;
	while (i < 9 && !unassignedFound) {
		j = 0;
		while (j < 9 && !unassignedFound) {
			if (a[i][j] == 0) {
				unassignedFound = true;
				result.row = i;
				result.col = j;
				//result.value = posse[i][j];
				result.exists = true;
			}
			j++;
		}
		i++;
	}
	return result;
}

bool backtrack(int a[9][9]) {
	int row;
	int col;
	int b[9][9];
	setInput(a);
	setArray(b);
	if (!findUnassigned(b).exists) {
		return true;
	}
	row = findUnassigned(b).row;
	col = findUnassigned(b).col;
	for (int i = 1; i < 10; i++) {
		b[row][col] = i;
		setInput(b);
		if (check(b)) {
			if (backtrack(b)) {
				return true;
			} else {
				input[row][col] = 0;
				b[row][col] = 0;
			}
		}
	}
	return false;
}

int main() {

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			input[i][j] = 0;
			posse[i][j] = "123456789";
		}
	}

	///*

	input[0][0] = 8;
	input[2][1] = 7;
	input[3][1] = 5;
	input[8][1] = 9;
	input[1][2] = 3;
	input[6][2] = 1;
	input[7][2] = 8;
	input[1][3] = 6;
	input[5][3] = 1;
	input[7][3] = 5;
	input[2][4] = 9;
	input[4][4] = 4;
	input[3][5] = 7;
	input[4][5] = 5;
	input[2][6] = 2;
	input[4][6] = 7;
	input[8][6] = 4;
	input[5][7] = 3;
	input[6][7] = 6;
	input[7][7] = 1;
	input[6][8] = 8;

	posse[0][0] = "8";
	posse[2][1] = "7";
	posse[3][1] = "5";
	posse[8][1] = "9";
	posse[1][2] = "3";
	posse[6][2] = "1";
	posse[7][2] = "8";
	posse[1][3] = "6";
	posse[5][3] = "1";
	posse[7][3] = "5";
	posse[2][4] = "9";
	posse[4][4] = "4";
	posse[3][5] = "7";
	posse[4][5] = "5";
	posse[2][6] = "2";
	posse[4][6] = "7";
	posse[8][6] = "4";
	posse[5][7] = "3";
	posse[6][7] = "6";
	posse[7][7] = "1";
	posse[6][8] = "8";

	//*/

	/*

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

	 */

	/*

	 input[0][0] = 1;
	 input[1][0] = 9;
	 input[4][0] = 4;
	 input[8][0] = 2;
	 input[3][1] = 1;
	 input[4][1] = 8;
	 input[8][1] = 4;
	 input[2][2] = 5;
	 input[6][2] = 9;
	 input[7][3] = 3;
	 input[0][4] = 3;
	 input[1][4] = 4;
	 input[4][4] = 6;
	 input[7][4] = 7;
	 input[8][4] = 8;
	 input[1][5] = 5;
	 input[2][6] = 3;
	 input[6][6] = 1;
	 input[0][7] = 9;
	 input[4][7] = 5;
	 input[5][7] = 7;
	 input[0][8] = 6;
	 input[4][8] = 3;
	 input[7][8] = 8;
	 input[8][8] = 9;

	 posse[0][0] = "1";
	 posse[1][0] = "9";
	 posse[4][0] = "4";
	 posse[8][0] = "2";
	 posse[3][1] = "1";
	 posse[4][1] = "8";
	 posse[8][1] = "4";
	 posse[2][2] = "5";
	 posse[6][2] = "9";
	 posse[7][3] = "3";
	 posse[0][4] = "3";
	 posse[1][4] = "4";
	 posse[4][4] = "6";
	 posse[7][4] = "7";
	 posse[8][4] = "8";
	 posse[1][5] = "5";
	 posse[2][6] = "3";
	 posse[6][6] = "1";
	 posse[0][7] = "9";
	 posse[4][7] = "5";
	 posse[5][7] = "7";
	 posse[0][8] = "6";
	 posse[4][8] = "3";
	 posse[7][8] = "8";
	 posse[8][8] = "9";

	 */

	printin(input);

	int b[9][9];
	setArray(b);

	cout << endl;
	cout << endl;

	clock_t time = clock();
	time = clock();
	solveSudoku();
	time = clock() - time;
	cout << "Time taken for execution with simplification is "
			<< (((float) time) / CLOCKS_PER_SEC);

	cout << endl;
	cout << endl;

	clock_t time1 = clock();
	time1 = clock();
	backtrack(b);
	time1 = clock() - time1;
	cout << "Time taken for execution with backtracking is "
			<< (((float) time1) / CLOCKS_PER_SEC);

	cout << endl;
	cout << endl;

	printin(input);

	cout << endl;
	cout << endl;

	return 0;
}

