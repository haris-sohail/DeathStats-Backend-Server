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
#include"Stack.h"
#include"Node.h"
#include"SLinkedList.h"
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

void setFileNumber(int numToSet, char*& destination)
{
	char initial[] = "../trees/AVL_ID/node";

	int i;
	for (i = 0; i < strlen(initial); i++)
	{
		destination[i] = initial[i];
	}

	// now we store the number of the file
	string fileNum = to_string(numToSet);

	for (int j = 0; j < fileNum.length(); j++)
	{
		destination[i++] = fileNum[j];
	}

	char ext[] = ".txt\0";

	for (int j = 0; j <= strlen(ext); j++)
	{
		destination[i++] = ext[j];
	}
}

void storeTreeInFile(AVL<int>& tree)
{
	node<string>* currentNodeFile;
	node<int>* currentNodeLine;

	char* nodeFilename = new char[50];
	int fileNum = 1;

	strcpy(nodeFilename, "../trees/AVL_ID/node1.txt");

	// data will be stored like this :
	// 1. key
	// 2. File(s)  :  file1, file2, .....
	// 3. Line(s)  :  line1, line2, .....
	// ==============================

	// store the nodes in a pre order fashion

	stack<TreeNode<int>*> nodeStack;

	nodeStack.push(tree.root);

	while (nodeStack.isEmpty() == false)
	{
		TreeNode<int>* node = nodeStack.pop();

		// open the current node file
		
		ofstream nodeO(nodeFilename);

		node->nodeFileName = nodeFilename; // store the node filename so that we can access this later

		// no we store the data

		nodeO << node->val << endl;

		// traverse through the list of file names and store them in a comma seperated way

		currentNodeFile = node->file.head;

		while (currentNodeFile)
		{
			nodeO << currentNodeFile->val << ",";
			currentNodeFile = currentNodeFile->next;
		}

		nodeO << endl;

		// traverse through the list of lines and store them in a comma seperated way

		currentNodeLine = node->line.head;

		while (currentNodeLine)
		{
			nodeO << currentNodeLine->val << ",";
			currentNodeLine = currentNodeLine->next;
		}

		nodeO << endl;

		fileNum++;
		setFileNumber(fileNum, nodeFilename);
		//nodeFilename[20]++;

		// Push right and left children in the stack
		if (node->right)
			nodeStack.push(node->right);
		if (node->left)
			nodeStack.push(node->left);
	}

	// now open the node files again and store the left and right subtrees' reference 

	fileNum = 1;
	strcpy(nodeFilename, "../trees/AVL_ID/node1.txt"); // reset to the first file

	stack<TreeNode<int>*> nodeST;

	nodeST.push(tree.root);

	while (nodeST.isEmpty() == false)
	{
		TreeNode<int>* Node = nodeST.pop();

		ofstream nodeSubO;

		nodeSubO.open(nodeFilename, ios::app);

		if (Node->left)
		{
			nodeSubO << "left:" << Node->left->nodeFileName << endl;
		}
		else
		{
			nodeSubO << "left:NULL" << endl;
		}

		if (Node->right)
		{
			nodeSubO << "right:" << Node->right->nodeFileName << endl;
		}
		else
		{
			nodeSubO << "right:NULL" << endl;
		}
		

		fileNum++;
		setFileNumber(fileNum, nodeFilename);

		// Push right and left children in the stack
		if (Node->right)
			nodeST.push(Node->right);
		if (Node->left)
			nodeST.push(Node->left);
	}


	delete[] nodeFilename;
}

void createAVLonID()
{
	// first we iterate through all the files and create an AVL tree based on the index choice given

	AVL<int> indexTree;

	// ------ declaring variables for filenames

	char* filename = new char[200];
	//char currentFile[] = "C:/Users/Haris'/source/repos/haris-sohail/DS-Project/datafiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv\0";

	char currentFile[] = "../datafiles/sample1.csv\0";

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
		while (fileIn.eof() == false) // read the file till the end of file
		{
			fileIn.get(temp);

			if (temp == '\n') // in case we find a new line, the ID is stored right after it
			{
				line++;

				getline(fileIn, key, ','); // read until the comma

				if (fileIn.eof() == true) 
				{
					break;
				}

				intKey = convertStringToInt(key.length(), key); // convert the character value of ID to int

				indexTree.root = indexTree.insert(intKey, filename, line, indexTree.root); // insert the index in the tree
			}
		}

		// now we have to store the index tree in files

		indexTree.LevelOrder(indexTree.root);
		
		storeTreeInFile(indexTree);

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
