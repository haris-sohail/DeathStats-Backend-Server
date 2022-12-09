//In my solituuuuuuuuuuuuuuuude
#include<iostream>
#include"SLinkedList.h"
#include"AVL.h"
#include"AVLString.h"
#include"Util.h"
using namespace std;

int main()
{	
	//readAndDisplay("C:/Users/Haris'/source/repos/haris-sohail/DS-Project/datafiles/sample1.csv");

	//askDataField();

	createAVL(1);

	AVL<int> tree1;
	string filename = "nothin.txt";
	int line = 20;
	tree1.root = tree1.insert(1, filename, line, tree1.root);
	tree1.root = tree1.insert(2, filename, line, tree1.root);
	tree1.root = tree1.insert(3, filename, line, tree1.root);
	tree1.root = tree1.insert(4, filename, line, tree1.root);

	//cout << tree1.equalityFound << endl;
	tree1.root = tree1.insert(1, filename, line, tree1.root);

	

	//tree1.LevelOrder(tree1.root);

	//tree1.LevelOrder(tree1.root);
}
