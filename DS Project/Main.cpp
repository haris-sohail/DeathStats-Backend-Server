//In my solituuuuuuuuuuuuuuuude
#include<iostream>
#include"SLinkedList.h"
#include"AVL.h"
#include"AVLString.h"
#include"Util.h"
#include<cstring>
using namespace std;

int main()
{	
	int choice = displayMenu();
	if (choice == 1) // Create index tree
	{
		int treechoice = askForTree();
		createIndexTree(treechoice, askDataField());
	}
	else if (choice == 2) // Point Search
	{
		if (askForSearchKeyType() == 1) // he key is a number
		{
			askForSearchKey_Num();
		}
		else if (askForSearchKeyType() == 2) // key is a string
		{
			askForSearchKey_string();
		}
		else
		{
			cout << endl << "Invalid key type." << endl;
		}
	}

	
		
}
