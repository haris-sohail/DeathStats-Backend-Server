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

void displayMenu()
{
	cout << "\n\t      ****** WELCOME TO DATABASE MANAGEMENT SYSTEM ******                           \n\n";


	cout << "================================================================================\n"
		<< "================================================================================\n"
		<< "===  1- Create Index                                                         ===\n"
		<< "===  2- Point Search                                                         ===\n"
		<< "===  3- Range Search                                                         ===\n"
		<< "===  4- Update Key                                                           ===\n"
		<< "===  5- Delete Key                                                           ===\n"
		<< "===  6- Help                                                                 ===\n"
		<< "===  7- Exit                                                                 ===\n"
		<< "================================================================================\n"
		<< "================================================================================\n";
}

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
