/*
 * Sudoku.cpp
 *
 *  Created on: 3 Mar 2013
 *      Author: shreegovind
 */

#include <iostream>
#include <sstream>
#include <ctime>
#include <fstream>
using namespace std;

int input[9][9]; //multi-dimentional array which holds the sudoku
string posse[9][9]; //multi-dimentional string array containing the number possibilities for each square

struct posseVals {
	string value;
	int row;
	int col;
	bool exists;
};

void printin(int a[9][9]) { //function to print the two dimensional array with sudoku
	for (int i = 0; i < 9; i++) {
		if ((i % 3) == 0) { //extra line every three lines
			cout << endl << endl;
		} else {
			cout << endl;
		}
		for (int j = 0; j < 9; j++) {
			if (((j + 1) % 3) == 0) { //extra spaces every three numbers
				cout << a[i][j] << "   ";
			} else {
				cout << a[i][j] << " ";
			}
		}
	}
}

void printstr(string a[9][9]) { //function to print the two dimensional string array with possibilities of each box, used in testing
	for (int i = 0; i < 9; i++) {
		if ((i % 3) == 0) { //extra line every three lines
			cout << endl << endl;
		} else {
			cout << endl;
		}
		for (int j = 0; j < 9; j++) {
			if (((j + 1) % 3) == 0) { //extra spaces every three numbers
				cout << a[i][j] << "   ";
			} else {
				cout << a[i][j] << " ";
			}
		}
	}
}

string convertInt(int a) { //function to convert an integer to a string
	stringstream ss;
	ss << a;
	return ss.str();
}

int convertStr(string a) { //function to convert a string to an integer
	istringstream buffer(a);
	int value;
	buffer >> value;
	return value;
}

int convertChar(char a) { //function to convert a character to an integer
	return (a - '0');
}

void setArray(int a[9][9]) { //function to set a newly defined two dimensional array equal to the input array
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			a[i][j] = input[i][j];
		}
	}
}

void setInput(int a[9][9]) { //function to set the input array equal to a separate array
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			input[i][j] = a[i][j];
		}
	}
}

void setString(string a[9][9]) { //function to set a newly defined two dimensional string array equal to the posse array
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			a[i][j] = posse[i][j];
		}
	}
}

void setArrayPosse(string a[9][9]) { //function to set the posse array equal to a separate string array
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			posse[i][j] = a[i][j];
		}
	}
}

int findQuadrant(int x, int y) { //function which given the coordinates of a square finds the origin (top left) square of the quadrant
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

string remove(string initial, char toremove) { //function to remove a character from a string
	string result = "";
	for (unsigned int i = 0; i < initial.length(); i++) {
		if (initial[i] != toremove) {
			result += initial[i]; //makes a new string with all elements of the previous string except the char to remove
		}
	}
	return result;
}

string removeString(string initial, string toremove) { //function to remove multiple characters (e.g. another string) from a string
	string result = initial;
	for (unsigned int i = 0; i < toremove.length(); i++) {
		result = remove(result, toremove[i]);
	}
	return result;
}

bool hasChanges(int a[9][9], int b[9][9]) { //function to calculate and compare the total sums of all the numbers in two different sudoku arrays to see if they are different
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

bool update() { //function to check the posse array if there are any squares with only one possibility left for which it assigns it to the input sudoku
	int count = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (posse[i][j].length() == 1) { //if the length of the posse string of a square is 1
				if (input[i][j] == 0) {
					count++; //count to inform us whether a change has taken place
				}
				stringstream(posse[i][j]) >> input[i][j]; //the value of the posse string is entered to the input sudoku
			}
		}
	}
	return (count > 0);
}


int duplicateR(int a[9][9], int value, int row) { //function to check if there are any duplicate numbers in a specified row
	int count = 0;
	for (int i = 0; i < 9; i++) {
		if (a[row][i] == value) {
			count++; //every time the specified appears in the row, the count increases
		}
	}
	if (count == 1) { //if the number appears more than once in the row, it is duplicated
		return 0;
	} else {
		return 1;
	}
}


int duplicateC(int a[9][9], int value, int col) { //function to check if there are any duplicate numbers in a specified column
	int count = 0;
	for (int i = 0; i < 9; i++) {
		if (a[i][col] == value) {
			count++; //every time the specified appears in the column, the count increases
		}
	}
	if (count == 1) { //if the number appears more than once in the row, it is duplicated
		return 0;
	} else {
		return 1;
	}
}


int duplicateS(int a[9][9], int value, int row, int col) { //function to check if there are any duplicate numbers in a square
	int Ori = findQuadrant(row, col); //finds the origin square of the quadrant
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (a[i + ((Ori - (Ori % 10)) / 10)][j + (Ori % 10)] == value) {
				count++; //every time the specified appears in the quadrant, the count increases
			}
		}
	}
	if (count == 1) { //if the number appears more than once in the quadrant, it is duplicated
		return 0;
	} else {
		return 1;
	}
}


bool isSolved(int a[9][9]) { //function to check whether all of the numbers in the sudoku are filled out
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (a[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}


bool check(int a[9][9]) { //function to check whether all the numbers entered so far are valid i.e. no duplicates
	int count = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (a[i][j] != 0) { //for all the squares with values in them, check for duplicates
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


bool isValid(int in[9][9]) { //function to check a solved sudoku is valid by checking for duplicates and separate row, column and quadrant totals
	if (check(in) && isSolved(in)) { //if the sudoku is completely filled in with out any duplicates, continue
		int rowtot = 0, coltot = 0;
		for (int i = 0; i < 9; i++) {
			rowtot = 0;
			coltot = 0;
			for (int j = 0; j < 9; j++) {
				rowtot += in[i][j];
				coltot += in[j][i];
			}
			if (rowtot != 45) { //ensures each row total is 45
				return false;
			}
			if (coltot != 45) { //ensures each column total is 45
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
			if (squatot != 45) { //ensures each quadrant total is 45
				return false;
			}
		}

		return true;
	}
	return false;
}


void simplifyR(int row) { //function to remove possibilities of a square if the number exists in the row
	string foundCells = "";
	for (int i = 0; i < 9; i++) {
		if (posse[row][i].length() == 1) {
			foundCells += posse[row][i]; //makes a string with all of the found values of all the squares in the row
		}
	}
	for (int i = 0; i < 9; i++) { //removes the found values from the posse strings of the rest of the squares not found in the row
		if (posse[row][i].length() != 1) {
			posse[row][i] = removeString(posse[row][i], foundCells);
		}
	}
}


void simplifyC(int col) { //function to remove possibilities of a square if the number exists in the column
	string foundCells = "";
	for (int i = 0; i < 9; i++) {
		if (posse[i][col].length() == 1) {
			foundCells += posse[i][col]; //makes a string with all of the found values of all the squares in the column
		}
	}
	for (int i = 0; i < 9; i++) { //removes the found values from the posse strings of the rest of the squares not found in the column
		if (posse[i][col].length() != 1) {
			posse[i][col] = removeString(posse[i][col], foundCells);
		}
	}
}


void simplifyS(int row, int col) { //function to remove possibilities of a square if the number exists in the square
	int Ori = findQuadrant(row, col); //find the origin square of the quadrant
	int a = ((Ori - (Ori % 10)) / 10);
	int b = (Ori % 10);
	string foundCells = "";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (posse[i + a][j + b].length() == 1) {
				foundCells += posse[i + a][j + b]; //makes a string with all of the found values of all the squares in the quadrant
			}
		}
	}

	for (int i = 0; i < 3; i++) { //removes the found values from the posse strings of the rest of the squares not found in the square
		for (int j = 0; j < 3; j++) {
			if (posse[i + a][j + b].length() != 1) {
				posse[i + a][j + b] = removeString(posse[i + a][j + b],
						foundCells);
			}
		}
	}

}


void simplify() { //function to remove possibilities of a square bringing together the separate row, column and square checks
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			simplifyR(i);
			simplifyC(j);
			simplifyS(i, j);
		}
	}
	update();
}


void singletonR(int row) { //function to go through the possibilities of the squares in a row and find if a number only appears once
	string foundCells = "";
	string foundSingles = "";
	int count[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 9; i++) { //makes a new string with all of the possibilities of all squares (not already found) in the row
		if (posse[row][i].length() != 1) {
			foundCells += posse[row][i];
		}
	}

	for (unsigned int i = 0; i < foundCells.length(); i++) { //uses the count array which counts the number of times each number 1-9 appears and stores it in its respective array position
		count[foundCells[i] - '1']++;
	}

	for (int i = 0; i < 9; i++) { //goes through the count array looking for and number that only appears once
		if (count[i] == 1) {
			foundSingles += convertInt(i + 1); //makes a string of numbers only appearing once
		}
	}

	for (unsigned int i = 0; i < foundSingles.length(); i++) {
		for (int j = 0; j < 9; j++) {
			if (posse[row][j] != remove(posse[row][j], foundSingles[i])) {
				posse[row][j] = foundSingles[i]; //string is then fed into the posse string array which will be fed into the input sudoku with the update function
			}
		}
	}
}


void singletonC(int col) { //function to go through the possibilities of the squares in a column and find if a number only appears once
	string foundCells = "";
	string foundSingles = "";
	int count[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 9; i++) { //makes a new string with all of the possibilities of all squares (not already found) in the column
		if (posse[i][col].length() != 1) {
			foundCells += posse[i][col];
		}
	}

	for (unsigned int i = 0; i < foundCells.length(); i++) { //uses the count array which counts the number of times each number 1-9 appears and stores it in its respective array position
		count[foundCells[i] - '1']++;
	}

	for (int i = 0; i < 9; i++) { //goes through the count array looking for and number that only appears once
		if (count[i] == 1) {
			foundSingles += convertInt(i + 1); //makes a string of numbers only appearing once
		}
	}

	for (unsigned int i = 0; i < foundSingles.length(); i++) {
		for (int j = 0; j < 9; j++) {
			if (posse[j][col] != remove(posse[j][col], foundSingles[i])) {
				posse[j][col] = foundSingles[i]; //string is then fed into the posse string array which will be fed into the input sudoku with the update function
			}
		}
	}
}


void singletonS(int row, int col) { //function to go through the possibilities of the squares in a quadrant and find if a number only appears once
	int Ori = findQuadrant(row, col);
	int a = ((Ori - (Ori % 10)) / 10);
	int b = (Ori % 10);
	string foundCells = "";
	string foundSingles = "";
	int count[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < 3; i++) { //makes a new string with all of the possibilities of all squares (not already found) in the square
		for (int j = 0; j < 3; j++) {
			if (posse[i + a][j + b].length() != 1) {
				foundCells += posse[i + a][j + b];
			}
		}
	}

	for (unsigned int i = 0; i < foundCells.length(); i++) { //uses the count array which counts the number of times each number 1-9 appears and stores it in its respective array position
		count[foundCells[i] - '1']++;
	}

	for (int i = 0; i < 9; i++) { //goes through the count array looking for and number that only appears once
		if (count[i] == 1) {
			foundSingles += convertInt(i + 1); //makes a string of numbers only appearing once
		}
	}

	for (unsigned int i = 0; i < foundSingles.length(); i++) {
		for (int j = 0; j < 3; j++) { //string is then fed into the posse string array which will be fed into the input sudoku with the update function
			for (int k = 0; k < 3; k++) {
				if (posse[j + a][k + b]
						!= remove(posse[j + a][k + b], foundSingles[i])) {
					posse[j + a][k + b] = foundSingles[i];
				}
			}

		}
	}
}


void singleton() { //function to go through the possibilities of the squares to find if a number only appears once combining the separate row, column and quadrant functions
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			simplify();
			singletonR(i);
			singletonC(j);
			singletonS(i, j);
		}
		simplify();
	}
	update();
}

bool backtrack(int a[9][9]); //early declaration for the backtracking function


bool solveSudoku() { //combines the various different functions above in loops to solve the sudoku
	int a[9][9];
	setArray(a);
	singleton();
	update();
	while (hasChanges(input, a)) { //while the sudoku is changing, keep applying the singleton and simplify functions to solve it
		setArray(a);
		singleton();
		update();
	}
	if (!isSolved(input)) { //once it is no longer changing but is not solved, start the backtracking function
		backtrack(input);
	}
	return (isSolved(input));
}


posseVals findUnassigned(int a[9][9]) { //function to find a square without an assigned value
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
				result.value = posse[i][j];
				result.exists = true;
			}
			j++;
		}
		i++;
	}
	return result;
}


bool backtrack(int a[9][9]) { //function to guess a value when at a stand still which if correct will continue otherwise will "backtrack" to the last correctly made decision
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
	for (int i = 1; i < 10; i++) { //BACKTRACKING WHERE YOU CHECK VALUES FROM 1 TO 9
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
//	string pos = posse[row][col];							//BACKTRACKING WHERE YOU CHECK USING POSSIBLE (POSSE) VALUES (DOES NOT WORK CORRECTLY)
//	for (unsigned int i = 0; i < pos.length(); i++) {
//		b[row][col] = convertChar(pos[i]);
//		setInput(b);
//		if (check(b)) {
//			if (backtrack(b)) {
//				return true;
//			} else {
//				input[row][col] = 0;
//				b[row][col] = 0;
//			}
//		}
//	}
	return false;
}


void inputsudoku() { //function to input the sudoku from the user using files
	string name = "";
	cout << "Enter the sudoku input file name: ";
	cin >> name;
	ifstream myfile(name.c_str());
	string lines[9] = { "", "", "", "", "", "", "", "", "" };
	string line;
	int i = 0;
	if (!myfile) {
		cout << endl << "Could not open file : " << name;
	}
	myfile.clear(); //SETS FILE TO THE START
	myfile.seekg(0, ios::beg); //SETS FILE TO THE STARTx

	while (getline(myfile, line)) { //reading the file for the sudoku
		lines[i] = line;
		i++;
	}
	myfile.close();

	for (int i = 0; i < 9; i++) { //setting the posse string array
		for (int j = 0; j < 9; j++) {
			posse[i][j] = lines[i][j];
			if (convertStr(posse[i][j]) == 0) {
				posse[i][j] = "123456789";
			}
		}
	}
	update(); //sets the input array
	simplify();
	cout << endl << endl << "Input sudoku: ";
	printin(input);
}


int main() {

	inputsudoku();

	int in1[9][9];
	int in2[9][9];
	setArray(in1);
	setArray(in2);

	cout << endl << endl << endl;

	setInput(in1); //solves and times the sudoku using the singleton and simplify functions
	clock_t time = clock();
	if (check(input)) {
		solveSudoku();
	} else {
		cout << "Sudoku is not valid" << endl << endl;
	}
	time = clock() - time;
	cout << "Time taken for execution with simplification is "
			<< (((float) time) / CLOCKS_PER_SEC) << " seconds";

	cout << endl << endl;

	setInput(in2); //solves and times the sudoku using only the backtracking function
	clock_t time1 = clock();
	if (check(input)) {
		backtrack(input);
	}
	time1 = clock() - time1;
	cout << "Time taken for execution with backtracking is "
			<< (((float) time1) / CLOCKS_PER_SEC) << " seconds";

	cout << endl << endl << endl;

	cout << "Output sudoku: ";
	printin(input);

	return 0;
}

