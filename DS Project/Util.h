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

int askDataField()
{
	int choice;
	cout << "Which data field do you want to create an index tree? \n";
	cout << endl << "1: ID" << endl;
	cout << "2: Year" << endl;
	cout << "3: 113 Cause Name" << endl;
	cout << "4: Cause Name" << endl;
	cout << "5: State" << endl;
	cout << "6: Deaths" << endl;
	cout << "7: Age-Adjusted Death Rate" << endl;

	cout << endl << "Enter your choice: ";

	cin >> choice;

	return choice;
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
