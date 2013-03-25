/*
 * InputFile.cpp
 *
 *  Created on: 24 Mar 2013
 *      Author: shreegovind
 */


#include <iostream>
#include <fstream>
using namespace std;

class InputFile {

	struct myarray{
		int grid[9][9];
	};

	string filename;

	ofstream myfile;


	string getfilename() {
		return filename;
	}

	void setfilename(string fname) {
		filename = fname;
	}

	myarray getgrid() {
		myarray a;
		a.grid = grid;
		return a;
	}
};
