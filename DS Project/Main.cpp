//In my solituuuuuuuuuuuuuuuude
#include<iostream>
#include"SLinkedList.h"
#include"AVL.h"
#include"Util.h"
using namespace std;

int main()
{
	AVL<int> tree1;
	tree1.root = tree1.insert(1, tree1.root);
	tree1.root = tree1.insert(2, tree1.root);
	tree1.root = tree1.insert(3, tree1.root);
	tree1.root = tree1.insert(4, tree1.root);
	tree1.root = tree1.insert(5, tree1.root);

	
	//readAndDisplay("C:/Users/Haris'/source/repos/haris-sohail/DS-Project/datafiles/sample1.csv");

	askDataField();

	//tree1.LevelOrder(tree1.root);
}
