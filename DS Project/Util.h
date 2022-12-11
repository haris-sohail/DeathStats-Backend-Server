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

int displayMenu()
{
	short choice;


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

	cout << endl << "What do you want to do? " << endl << endl;

	cout << "Enter your choice: ";

	cin >> choice;

	return choice;
}

int askForTree()
{
	short choice;

	cout << endl;
	cout << "Which tree do you want? " << endl;
	cout << "1: AVL tree" << endl;
	cout << "2: Red Black tree" << endl;
	cout << "3: B - tree" << endl;

	cout << endl << "Enter your choice: ";
	cin >> choice;

	return choice;
}

int askDataField()
{
	int choice;
	cout << endl;
	cout << "On which data field do you want to create an index tree? \n";
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

int askDataFieldSearch()
{
	int choice;
	cout << endl;
	cout << "Enter the searching data field \n";
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

void storeInitial(char*& initial, int dataField)
{
	char folderpath[50] = "../trees/";

	int i;
	for (i = 0; i <= strlen(folderpath); i++)
	{
		initial[i] = folderpath[i];
	}

	// store the folder according to the data field
	char ID[] = "AVL_ID/node";
	char Year[] = "AVL_Year/node\0";
	char Cause113[] = "AVL_113 Cause Name/node";
	char CauseName[] = "AVL_Cause Name/node";
	char State[] = "AVL_State/node";
	char Deaths[] = "AVL_Deaths/node";
	char Age[] = "AVL_Age Adjusted Death Rate/node";

	if (dataField == 1)
	{
		strcat(folderpath, ID);
	}
	else if (dataField == 2)
	{
		strcat(folderpath, Year);
	}
	else if (dataField == 3)
	{
		strcat(folderpath, Cause113);
	}
	else if (dataField == 4)
	{
		strcat(folderpath, CauseName);
	}
	else if (dataField == 5)
	{
		strcat(folderpath, State);
	}
	else if (dataField == 6)
	{
		strcat(folderpath, Deaths);
	}
	else if (dataField == 7)
	{
		strcat(folderpath, Age);
	}

	strcpy(initial, folderpath);

}

void setFileNumber(int numToSet, char*& destination, int dataField)
{
	char* initial = new char[40];

	storeInitial(initial, dataField);


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
void storeTreeInFile(AVL<T>& tree, int dataField)
{
	node<string>* currentNodeFile;
	node<int>* currentNodeLine;

	char* nodeFilename = new char[50];
	int fileNum = 1;

	setFileNumber(1, nodeFilename, dataField); // set the file number to 1 in the beginning

	// data will be stored like this :
	// 1. key
	// 2. File(s)  :  file1, file2, .....
	// 3. Line(s)  :  line1, line2, .....
	// 4. left: 
	// 5. right:
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
		setFileNumber(fileNum, nodeFilename, dataField);
		//nodeFilename[20]++;

		// Push right and left children in the stack
		if (node->right)
			nodeStack.push(node->right);
		if (node->left)
			nodeStack.push(node->left);
	}

	// now open the node files again and store the left and right subtrees' reference 

	fileNum = 1;
	setFileNumber(1, nodeFilename, dataField); // reset to the first file

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
		setFileNumber(fileNum, nodeFilename, dataField);

		// Push right and left children in the stack
		if (Node->right)
			nodeST.push(Node->right);
		if (Node->left)
			nodeST.push(Node->left);
	}


	delete[] nodeFilename;
}

void storeStringTreeInFile(AVLString tree, int dataField)
{
	node<string>* currentNodeFile;
	node<int>* currentNodeLine;

	char* nodeFilename = new char[50];
	int fileNum = 1;

	setFileNumber(1, nodeFilename, dataField); // reset to the first file

	// data will be stored like this :
	// 1. key
	// 2. File(s)  :  file1, file2, .....
	// 3. Line(s)  :  line1, line2, .....
	// 4. left: 
	// 5. right:
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
		setFileNumber(fileNum, nodeFilename, dataField);

		// Push right and left children in the stack
		if (node->right)
			nodeStack.push(node->right);
		if (node->left)
			nodeStack.push(node->left);
	}

	// now open the node files again and store the left and right subtrees' reference 

	fileNum = 1;
	setFileNumber(1, nodeFilename, dataField); // reset to the first file

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
		setFileNumber(fileNum, nodeFilename, dataField);

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

string askForSearchKey_string()
{
	string key;

	cout << "Enter the key to be searched: ";

	cin.ignore();
	getline(cin, key);

	return key;
}

void askForRangeKey_Num(double& startingKey, double& endingKey)
{
	cout << "Enter the starting key: ";
	cin >> startingKey;

	cout << endl;
	cout << "Enter the ending key: ";
	cin >> endingKey;
}

double askForSearchKey_Num()
{
	double key;
	cout << "Enter the key to be searched: ";
	cin >> key;

	return key;
}

int askForSearchKeyType()
{
	int choice;
	cout << endl;
	cout << "Enter the type of key: " << endl;
	cout << "1: Number" << endl;
	cout << "2: String" << endl;

	cout << endl << "Enter your choice: ";

	cin >> choice;

	return choice;
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
			//indexTree.LevelOrder(indexTree.root);
		}
		else
		{
			cout << "Error opening file" << endl;
		}
	}

	// now we have to store the index tree in files
		
	storeTreeInFile(indexTree, dataField);
	

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

	storeStringTreeInFile(indexTree, dataField);


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

template <typename T>
int getTotalAsciiValue(T toCalculate)
{
	int asciiValue = 0;
	for (int i = 0; i < toCalculate.length(); i++)
	{
		asciiValue += toCalculate[i];
	}

	return asciiValue;
}

void storeFileNames(SLinkedList<string>& filename, string allFileNames)
{
	string tempFileName;
	int i, j = 0;
	bool newLineFlag = 1;

	// read till the ','
	for (; newLineFlag;)
	{
		tempFileName = "../datafiles/NCHS_-_Leading_Causes_of_Death__United_States_10.csv";
		for (i = 0; ; i++, j++)
		{
			if (allFileNames[j] != ',')
			{
				tempFileName[i] = allFileNames[j];
			}
			else if (allFileNames[j] == ',')
			{
				j++;

				if (allFileNames[j] == '\n')
				{
					newLineFlag = false;
				}

				break;
			}
		}
		tempFileName[i] = '\0';

		// now store the filename in the linked list
		filename.insert(tempFileName);
	}
	

	
}

void storeLineNums(SLinkedList<int>& lineNums, string allLineNums)
{
	string tempLineNum;
	int i, j = 0;
	bool newLineFlag = 1;

	// read till the ','
	for (; newLineFlag;)
	{
		tempLineNum = "1000";
		for (i = 0; ; i++, j++)
		{
			if (allLineNums[j] != ',')
			{
				tempLineNum[i] = allLineNums[j];
			}
			else if (allLineNums[j] == ',')
			{
				j++;

				if (allLineNums[j] == '\n')
				{
					newLineFlag = false;
				}

				break;
			}
		}
		tempLineNum[i] = '\0';

		// now convert into int and store the line num in the linked list
		lineNums.insert(stoi(tempLineNum));
	}
}
void printTupleData(string tupleData)
{
	for (int i = 0; i < tupleData.length(); i++)
	{
		if (tupleData[i] != ',')
		{
			cout << tupleData[i];
		}
		else
		{
			cout << "         ";
		}
	}
	cout << endl;
}

void printTuples(SLinkedList<string> filenames, SLinkedList<int> lineNums)
{
	string currentFileName;
	int currentLineNum;
	string tupleData;

	node<string>* currentNodeFile = filenames.head; // iterator node for filenames linked list
	node<int>* currentNodeLineNum = lineNums.head; // iterator node for line numbers linked list

	while (currentNodeFile) // traverse through the linked lists, since both have same size, we only need one node pointer to check the end
	{
		ifstream fileIn;
		// open the file
		fileIn.open(currentNodeFile->val);

		if (fileIn)
		{
			// go to the line number
			for (int i = 1; i <= currentNodeLineNum->val; i++) // i = 1 because lines are starting from 1
			{
				getline(fileIn, tupleData, '\n'); // this stores the tuple data in string

				if (i == currentNodeLineNum->val)
				{
					// print the data
					printTupleData(tupleData);
					cout << endl;
				}
			}
		}
		else
		{
			cout << endl << "Error opening file" << endl;
		}
		


		// jump to the next nodes

		currentNodeLineNum = currentNodeLineNum->next;
		currentNodeFile = currentNodeFile->next;
	}
}

void storeCstringinString(string& nodefilename, char* nodeFileName)
{
	for (int i = 0; i <= strlen(nodeFileName); i++)
	{
		nodefilename[i] = nodeFileName[i];
	}
}

template <typename T>
void pointSearchNumbers(T key, int dataField)
{
	double keyNumber;

	ifstream fileIn;

	// traverse through the node files and search for keys
	string tempKey;

	string allFileNames;
	string allLineNums;

	string filenameTemp;
	string lineNumTemp;

	// lists for storing all the filenames and line numbers of the tuples found
	SLinkedList<string> filenames;
	SLinkedList<int> lineNums;

	// ------ declaring variables for filenames

	char* nodeFileName = new char[50];

	setFileNumber(1, nodeFileName, dataField); // set the initial file name as node1(root) and set the folder appopriately

	fileIn.open(nodeFileName);

	string nodefilename = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

	storeCstringinString(nodefilename, nodeFileName);

	if (fileIn)
	{

		while (fileIn.eof() == false)
		{
			ifstream fileIn;

			fileIn.open(nodefilename);

			// traverse through the files

			getline(fileIn, tempKey, '\n'); // read till the first endline occurs. key is stored in the first line

			keyNumber = convertStringToDouble(tempKey); // convert the string to double		

			// now compare it to the search key

			if (keyNumber == key) // key found 
			{
				// read the line number and file name

				// reading all the filenames
				getline(fileIn, allFileNames, '\n');

				allFileNames.append("\n"); // \n to indicate the end of string

				// now we store all the filenames in a list

				storeFileNames(filenames, allFileNames);

				// similarly store the line numbers in the list

				// first read the fileNums and store in allFileNums

				getline(fileIn, allLineNums, '\n');

				allLineNums.append("\n"); // \n to indicate the end of string

				storeLineNums(lineNums, allLineNums);

				// now we go to the file and line nums and print the tuples one by one

				cout << endl << "ID        113 Cause Name        Cause Name        State        Deaths        Age Adjusted Death Rate" << endl << endl;
				printTuples(filenames, lineNums);

				break;
			}

			else if (key < keyNumber) // go to left
			{
				// change the nodeFileName 

				// read the left file

				getline(fileIn, nodefilename, '\n'); // read the file Names
				getline(fileIn, nodefilename, '\n'); // read the line numbers

				getline(fileIn, nodefilename, ':'); // read till the : of "left:"

				// now read the file name
				getline(fileIn, nodefilename, '\n');

				if (nodefilename == "NULL")
				{
					cout << endl << "Not found" << endl;
					break;
				}
			}

			else if (key > keyNumber) // go right
			{
				// change the nodeFileName 

				// read the left file

				getline(fileIn, nodefilename, '\n'); // read the file Names
				getline(fileIn, nodefilename, '\n'); // read the line numbers
				getline(fileIn, nodefilename, '\n'); // read the left file name

				getline(fileIn, nodefilename, ':'); // read till the : of "right:"

				// now read the file name
				getline(fileIn, nodefilename, '\n');

				if (nodefilename == "NULL")
				{
					cout << endl << "Not found" << endl;
					break;
				}
			}

		}
	}
	else
	{
		cout << endl << "Error opening file" << endl;
	}
	


}

void pointSearchStrings(string key, int dataField)
{
	int asciiValueKey = getTotalAsciiValue(key);
	int asciiValue;

	ifstream fileIn;

	// traverse through the node files and search for keys
	string tempKey;

	string allFileNames;
	string allLineNums;

	string filenameTemp;
	string lineNumTemp;

	// lists for storing all the filenames and line numbers of the tuples found
	SLinkedList<string> filenames;
	SLinkedList<int> lineNums;

	// ------ declaring variables for filenames

	char* nodeFileName = new char[50];

	setFileNumber(1, nodeFileName, dataField); // set the initial file name as node1(root) and set the folder appopriately

	fileIn.open(nodeFileName);

	string nodefilename = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

	storeCstringinString(nodefilename, nodeFileName);

	if (fileIn)
	{

		while (fileIn.eof() == false)
		{
			ifstream fileIn;

			fileIn.open(nodefilename);

			// traverse through the files

			getline(fileIn, tempKey, '\n'); // read till the first endline occurs. key is stored in the first line

			asciiValue = getTotalAsciiValue(tempKey); // convert the string to double		

			// now compare it to the search key

			if (asciiValue == asciiValueKey) // key found 
			{
				// read the line number and file name

				// reading all the filenames
				getline(fileIn, allFileNames, '\n');

				allFileNames.append("\n"); // \n to indicate the end of string

				// now we store all the filenames in a list

				storeFileNames(filenames, allFileNames);

				// similarly store the line numbers in the list

				// first read the fileNums and store in allFileNums

				getline(fileIn, allLineNums, '\n');

				allLineNums.append("\n"); // \n to indicate the end of string

				storeLineNums(lineNums, allLineNums);

				// now we go to the file and line nums and print the tuples one by one

				cout << endl << "ID        113 Cause Name        Cause Name        State        Deaths        Age Adjusted Death Rate" << endl << endl;
				printTuples(filenames, lineNums);

				break;
			}

			else if (asciiValueKey < asciiValue) // go to left
			{
				// change the nodeFileName 

				// read the left file

				getline(fileIn, nodefilename, '\n'); // read the file Names
				getline(fileIn, nodefilename, '\n'); // read the line numbers

				getline(fileIn, nodefilename, ':'); // read till the : of "left:"

				// now read the file name
				getline(fileIn, nodefilename, '\n');

				if (nodefilename == "NULL")
				{
					cout << endl << "Not found" << endl;
					break;
				}
				
			}

			else if (asciiValueKey > asciiValue) // go right
			{
				// change the nodeFileName 

				// read the left file

				getline(fileIn, nodefilename, '\n'); // read the file Names
				getline(fileIn, nodefilename, '\n'); // read the line numbers
				getline(fileIn, nodefilename, '\n'); // read the left file name

				getline(fileIn, nodefilename, ':'); // read till the : of "right:"

				// now read the file name
				getline(fileIn, nodefilename, '\n');

				if (nodefilename == "NULL")
				{
					cout << endl << "Not found" << endl;
					break;
				}
			}

		}
	}
	else
	{
		cout << endl << "Error opening file" << endl;
	}


}

void RangeSearchNumbers(double startingKey, double endingKey, int dataField)
{
	double keyNumber;

	ifstream fileIn;

	// traverse through the node files and search for keys
	string tempKey;

	string allFileNames;
	string allLineNums;

	string filenameTemp;
	string lineNumTemp;


	// ------ declaring variables for filenames

	char* nodeFileName = new char[50];

	setFileNumber(1, nodeFileName, dataField); // set the initial file name as node1(root) and set the folder appopriately

	fileIn.open(nodeFileName);

	string nodefilename = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

	cout << endl << "ID        113 Cause Name        Cause Name        State        Deaths        Age Adjusted Death Rate" << endl << endl;

	storeCstringinString(nodefilename, nodeFileName);

	if (fileIn)
	{
		stack<string> nodeFileStack;

		nodeFileStack.push(nodefilename);

		while (nodeFileStack.isEmpty() == false)
		{
			// lists for storing all the filenames and line numbers of the tuples found
			SLinkedList<string> filenames;
			SLinkedList<int> lineNums;

			ifstream fileIn;

			nodefilename = nodeFileStack.pop();

			fileIn.open(nodefilename);

			// traverse through the files

			getline(fileIn, tempKey, '\n'); // read till the first endline occurs. key is stored in the first line

			keyNumber = convertStringToDouble(tempKey); // convert the string to double

			// now compare it to the search key

			if ((keyNumber >= startingKey && keyNumber <= endingKey)) // key found 
			{
				// read the line number and file name

				// reading all the filenames
				getline(fileIn, allFileNames, '\n');

				allFileNames.append("\n"); // \n to indicate the end of string

				// now we store all the filenames in a list

				storeFileNames(filenames, allFileNames);

				// similarly store the line numbers in the list

				// first read the fileNums and store in allFileNums

				getline(fileIn, allLineNums, '\n');

				allLineNums.append("\n"); // \n to indicate the end of string

				storeLineNums(lineNums, allLineNums);

				// now we go to the file and line nums and print the tuples one by one

				printTuples(filenames, lineNums);

				getline(fileIn, nodefilename, ':'); // read till the : of "left:"

				getline(fileIn, nodefilename, '\n'); // read the left file name

				if (nodefilename != "NULL")
				{
					nodeFileStack.push(nodefilename); // push the left filename
				}
				

				getline(fileIn, nodefilename, ':'); // read till the : of "right:"

				getline(fileIn, nodefilename, '\n'); // read the righ file name

				if (nodefilename != "NULL")
				{
					nodeFileStack.push(nodefilename); // push the right filename
				}

			}

			else
			{
				// push the left and right file names in the stack

				// read the left file

				getline(fileIn, nodefilename, '\n'); // read the file Names
				getline(fileIn, nodefilename, '\n'); // read the line numbers

				getline(fileIn, nodefilename, ':'); // read till the : of "left:"

				// now read the file name
				getline(fileIn, nodefilename, '\n');

				if (nodefilename != "NULL")
				{
					nodeFileStack.push(nodefilename);
				}


				// read the right file

				getline(fileIn, nodefilename, ':'); // read till the : of "right:"

				// now read the file name
				getline(fileIn, nodefilename, '\n');

				if (nodefilename != "NULL")
				{
					nodeFileStack.push(nodefilename);
				}
			}
			

		}
	}
	else
	{
		cout << endl << "Error opening file" << endl;
	}
}
