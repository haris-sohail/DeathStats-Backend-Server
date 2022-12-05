//====================================================
//
// this header file contains all the utility functions
//
// ===================================================
#pragma once


#include<fstream>
#include<iostream>
#include<string>
using namespace std;

void readAndDisplay(string filename)
{
	ifstream fileIn;

	fileIn.open(filename);
	string line; // string to temporarily store the current line of the file being read

	if (fileIn)
	{
		while (fileIn.good())
		{
			getline(fileIn, line, ','); // read until you get to the comma. (CSV file)

			cout << line << endl;
		}
	}
	else
	{
		cout << "Error opening file" << endl;
	}
}
