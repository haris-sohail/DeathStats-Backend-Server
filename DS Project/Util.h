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
//#include"AVLString.h"
#include"Stack.h"
#include"Node.h"
#include"SLinkedList.h"
using namespace std;

class AVLString
{
public:
	TreeNode<string>* root;

public:
	AVLString()
	{
		root = NULL;
	}

	TreeNode<string>*& getRoot()
	{
		return root;
	}

	int getTotalAsciiValue(string toCalculate)
	{
		int asciiValue = 0;
		for (int i = 0; i < toCalculate.length(); i++)
		{
			asciiValue += toCalculate[i];
		}

		return asciiValue;
	}

	TreeNode<string>* insert(string data, string filename, int line, TreeNode<string>* root)
	{
		if (root == NULL)
		{
			root = new TreeNode<string>;

			root->val = data;
			root->file.insert(filename);
			root->line.insert(line);
			root->left = NULL;
			root->right = NULL;
		}
		else if (getTotalAsciiValue(data) < getTotalAsciiValue(root->val)) // insertion in left subtree
		{
			root->left = insert(data, filename, line, root->left);

			//check imbalancing 
			if (height(root->left) - height(root->right) == 2)
			{
				if (getTotalAsciiValue(data) < getTotalAsciiValue(root->left->val))
				{
					root = RR(root);
				}
				else
				{
					root = RL(root);
				}
			}
		}
		else if (getTotalAsciiValue(data) > getTotalAsciiValue(root->val)) // insertion in right subtree
		{
			root->right = insert(data, filename, line, root->right);

			// check imbalancing
			if (height(root->right) - height(root->left) == 2) // right is heavy
			{
				if (getTotalAsciiValue(data) > getTotalAsciiValue(root->right->val))
				{
					root = LL(root);
				}
				else
				{
					root = LR(root);
				}
			}
		}

		else if (getTotalAsciiValue(data) == getTotalAsciiValue(root->val)) // data is equal to previous insertion
		{
			root->file.insert(filename);
			root->line.insert(line);

			return root;
		}

		root->height = getMax(height(root->left), height(root->right)) + 1;

		return root;
	}

	int height(TreeNode<string>* root)
	{
		// base case: empty tree has a height of 0
		if (root == nullptr) {
			return -1;
		}

		// recur for the left and right subtree and consider maximum depth
		return 1 + getMax(height(root->left), height(root->right));
	}

	bool retreive(string data)
	{
		TreeNode<string>* current = root;
		string searchDataItem;

		// tree is not initialized
		if (root == NULL)
		{
			cout << "Tree is undefined" << endl;
			return false;
		}

		else
		{
			while (current)
			{
				if (getTotalAsciiValue(data) < getTotalAsciiValue(current->val))
				{
					current = current->left;
				}
				else if (getTotalAsciiValue(data) > getTotalAsciiValue(current->val))
				{
					current = current->right;
				}
				else if (getTotalAsciiValue(data) == getTotalAsciiValue(current->val))
				{
					searchDataItem = current->val;
					return true;
				}
			}

			return false;
		}
	}

	void preOrder(TreeNode<string>*& root)
	{
		if (root == NULL)
		{
			return;
		}

		// root - left - right
		cout << root->val;

		preOrder(root->left);

		preOrder(root->right);
	}

	void postOrder(TreeNode<string>*& root)
	{
		if (root == NULL)
		{
			return;
		}

		// left - right - root

		preOrder(root->left);

		preOrder(root->right);

		cout << root->val;
	}

	void InOrder(TreeNode<string>*& root)
	{
		if (root == NULL)
		{
			return;
		}

		// left - root - right

		preOrder(root->left);

		cout << root->val;

		preOrder(root->right);
	}

	void LevelOrder(TreeNode<string>* root)
	{
		// enque all children of the front TreeNode on the queue
		// then deque the front TreeNode
		TreeNode<string>* current = root;
		Queue<TreeNode<string>> q;
		q.Enqueue(*current);

		TreeNode<int>* visit;

		while (!q.isEmpty())
		{
			TreeNode<string> visit = q.Dequeue();
			cout << visit.val << " ";

			if (visit.left != NULL)
			{
				//current = current->left;
				q.Enqueue(*visit.left);
			}

			if (visit.right != NULL)
			{
				//current = current->right;
				q.Enqueue(*visit.right);
			}

		}

	}

	string getMin()
	{
		TreeNode <string>* current = this->root;

		string val;
		// we are going to iterate towards the left until we find NULL

		while (current)
		{
			val = current->val;

			current = current->left;
		}

		return val;
	}

	string getMin(TreeNode<string>*& startFrom)
	{
		TreeNode <string>* current = this->root;

		string val;
		// we are going to iterate towards the left until we find NULL

		while (current)
		{
			val = current->val;

			startFrom = current;
			current = current->left;
		}

		return val;
	}

	int getMax(int n1, int n2)
	{
		if (n1 > n2) return n1;

		else
			return n2;
	}

	TreeNode<string>* LL(TreeNode<string>* K1)
	{
		TreeNode<string>* K2;
		K2 = K1->right;

		K1->right = K2->left;
		K2->left = K1;

		K1->height = getMax(height(K1->left), height(K1->right)) + 1;
		K2->height = getMax(height(K2->right), K1->height) + 1;
		return K2;
	}

	TreeNode<string>* RR(TreeNode<string>* K1)
	{
		TreeNode<string>* K2 = K1->left;
		K1->left = K2->right;
		K2->right = K1;

		K1->height = getMax(height(K1->left), height(K1->right)) + 1;
		K2->height = getMax(height(K2->left), K1->height) + 1;
		return K2;
	}

	TreeNode<string>* LR(TreeNode<string>* K1)
	{
		K1->right = RR(K1->right);

		return LL(K1);
	}

	TreeNode<string>* RL(TreeNode<string>* K1)
	{
		K1->left = LL(K1->left);

		return RR(K1);
	}

	TreeNode<string>* balance(TreeNode<string>* root)
	{
		if (height(root->left) - height(root->right) == 2) // left tree is heavy
		{
			RR(root);
		}
		else if (height(root->right) - height(root->left) == 2) // right is heavy
		{
			LL(root);
		}
	}
};

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

double convertStringToDouble(string toBeConverted)
{
	return stod(toBeConverted);
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

template <typename T>
void storeTreeInFile(AVL<T>& tree)
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

	stack<TreeNode<T>*> nodeStack;

	nodeStack.push(tree.root);

	while (nodeStack.isEmpty() == false)
	{
		TreeNode<T>* node = nodeStack.pop();

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

	stack<TreeNode<T>*> nodeST;

	nodeST.push(tree.root);

	while (nodeST.isEmpty() == false)
	{
		TreeNode<T>* Node = nodeST.pop();

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

void storeStringTreeInFile(AVLString tree)
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

	stack<TreeNode<string>*> nodeStack;

	nodeStack.push(tree.root);

	while (nodeStack.isEmpty() == false)
	{
		TreeNode<string>* node = nodeStack.pop();

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

	stack<TreeNode<string>*> nodeST;

	nodeST.push(tree.root);

	while (nodeST.isEmpty() == false)
	{
		TreeNode<string>* Node = nodeST.pop();

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

void moveCurrentFile(char*& filename, int numToSet)
{
	char initial[] = "../datafiles/NCHS_-_Leading_Causes_of_Death__United_States_";

	int i;
	for (i = 0; i < strlen(initial); i++)
	{
		filename[i] = initial[i];
	}

	// now we store the number of the file
	string fileNum = to_string(numToSet);

	for (int j = 0; j < fileNum.length(); j++)
	{
		filename[i++] = fileNum[j];
	}

	char ext[] = ".csv\0";

	for (int j = 0; j <= strlen(ext); j++)
	{
		filename[i++] = ext[j];
	}
}

bool checkKey(string key)
{
	string acc = "\"Accidents";

	string acc1 = "\"Intentional";

	for (int i = 0; i < acc.length(); i++)
	{
		if (acc[i] != key[i])
		{
			return 0;
		}
	}
	return 1;
}



template <typename T> 
void createAVLonNumbers(int dataField)
{
	// first we iterate through all the files and create an AVL tree based on the index choice given

	AVL<T> indexTree;

	// ------ declaring variables for filenames

	int fileNum = 1;

	char* filename = new char[200];

	//char currentFile[] = "C:/Users/Haris'/source/repos/haris-sohail/DS-Project/datafiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv\0";

	for (int i = 0; i < 1; i++, fileNum++) // make index tree on all the files
	{
		moveCurrentFile(filename, fileNum);

		//strcpy(filename, "../datafiles/sample1.csv");

		// ------ opening the file

		ifstream fileIn;
		ofstream fileOut;

		int keyForTree, line = 1;

		string key;
		int intKey;
		double doubleKey;
		bool tempFlag = 0;

		char temp;

		fileIn.open(filename);

		if (fileIn)
		{
			while (fileIn.eof() == false) // read the file till the end of file
			{
				fileIn.get(temp);

				if (tempFlag == 1)
				{
					temp = '\n';
				}

				if (temp == '\n') // in case we find a new line, the ID is stored right after it
				{
					line++;

					if (dataField == 1) // ID
					{
						getline(fileIn, key, ','); // read until the first comma
					}

					else if (dataField == 2) // Year
					{
						// read until the 2nd comma

						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
					}
					else if (dataField == 6) // Deaths
					{
						// read until the 6th comma

						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
					}

					else if (dataField == 7) // Age Adjusted Death Rate
					{
						// read until the 7th comma

						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
						getline(fileIn, key, ',');		
						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
						getline(fileIn, key, '\n');
						
						tempFlag = 1;

					}

					if (fileIn.eof() == true)
					{
						break;
					}

					if (dataField != 7) // key is an integer
					{
						intKey = convertStringToInt(key.length(), key); // convert the character value of ID to int

						indexTree.root = indexTree.insert(intKey, filename, line, indexTree.root); // insert the index in the tree
					}
					else // key is a double
					{
						doubleKey = convertStringToDouble(key);

						indexTree.root = indexTree.insert(doubleKey, filename, line, indexTree.root); // insert the index in the tree
					}
				}
			}
		}
		else
		{
			cout << "Error opening file" << endl;
		}
	}

	// now we have to store the index tree in files
		
	storeTreeInFile(indexTree);
	

	delete[] filename;
	
}


void createAVLonStringKey(int dataField)
{
	// first we iterate through all the files and create an AVL tree based on the index choice given

	AVLString indexTree;

	// ------ declaring variables for filenames

	int fileNum = 1;

	char* filename = new char[200];

	//char currentFile[] = "C:/Users/Haris'/source/repos/haris-sohail/DS-Project/datafiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv\0";

	for (int i = 0; i < 10; i++, fileNum++) // make index tree on all the files
	{
		moveCurrentFile(filename, fileNum);

		//strcpy(filename, "../datafiles/sample1.csv");

		// ------ opening the file

		ifstream fileIn;
		ofstream fileOut;

		int keyForTree, line = 1;

		string key;
		int intKey;
		double doubleKey;
		bool tempFlag = 0;

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

					if (dataField == 3) // 113 Cause Name
					{
						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
						getline(fileIn, key, ','); // read until the 3rd comma
					}

					else if (dataField == 4) // Cause Name
					{
						// read until the 4th comma

						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
						getline(fileIn, key, ','); 
						getline(fileIn, key, ',');
					}
					else if (dataField == 5) // State
					{
						// read until the 5th comma

						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
						getline(fileIn, key, ',');
					}

					if (fileIn.eof() == true)
					{
						break;
					}

					indexTree.root = indexTree.insert(key, filename, line, indexTree.root); // insert the index in the tree

				}
			}
		}
		else
		{
			cout << "Error opening file" << endl;
		}
	}

	// now we have to store the index tree in files

	storeStringTreeInFile(indexTree);


	delete[] filename;

}

void createAVL(int indexChoice)
{
	if ((indexChoice == 1) || (indexChoice == 2) || (indexChoice == 6)) // these are all the int key choices
	{
		createAVLonNumbers<int>(indexChoice);
	}
	else if ((indexChoice == 7)) // this is the floating point key choice
	{
		createAVLonNumbers<double>(indexChoice);
	}

	else if ((indexChoice >= 3) && (indexChoice <= 5)) // these are all string key choices
	{
		createAVLonStringKey(indexChoice);
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
