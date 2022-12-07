//====================================================
//
// this header file contains all the utility functions
//
// ===================================================
#pragma once
#pragma warning(disable : 4996)


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

int convertStringToInt(int length, string toBeConverted)
{
	int result = 0, unit = 1;
	char temp;
	for (int i = 0; i < length; i++)
	{
		temp = toBeConverted[i];
		result = (result * unit) + (temp - 48);
		unit = 10;
	}
	//cout << result;
	return result;
}

void createAVLonID()
{
	// first we iterate through all the files and create an AVL tree based on the index choice given

	AVL<int> indexTree;

	// ------ declaring variables for filenames

	char* filename = new char[200];
	//char currentFile[] = "C:/Users/Haris'/source/repos/haris-sohail/DS-Project/datafiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv\0";

	char currentFile[] = "C:/Users/Haris'/source/repos/haris-sohail/DS-Project/datafiles/sample1.csv\0";

	strcpy(filename, currentFile);

	// ------ opening the file

	ifstream fileIn;

	int keyForTree, line = 1;

	string key;
	int intKey;

	char temp;

	fileIn.open(filename);

	if (fileIn)
	{
		while (fileIn.eof() == false)
		{
			fileIn.get(temp);

			if (temp == '\n')
			{
				line++;

				getline(fileIn, key, ',');

				if (fileIn.eof() == true)
				{
					break;
				}

				intKey = convertStringToInt(key.length(), key);

				indexTree.root = indexTree.insert(intKey, filename, line, indexTree.root);
			}
		}

		indexTree.LevelOrder(indexTree.root);
	}
	else
	{
		cout << "Error opening file" << endl;
	}

	delete[] filename;
}

void createAVL(int indexChoice)
{
	if (indexChoice == 1)
	{
		createAVLonID();
	}
}

void createIndexTree(int treeChoice, int indexChoice)
{
	if (treeChoice == 1) // AVL Tree
	{
		createAVL(indexChoice);
	}
	else if (treeChoice == 2) // Red Black Tree
	{

	}
	else if (treeChoice == 3) // B - Tree
	{

	}
	else
	{
		cout << "Invalid." << endl;
		return;
	}

}
