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
	int dataField = 0;
	if (choice == 1) // Create index tree
	{
		int treechoice = askForTree();
		dataField = askDataField();
		createIndexTree(treechoice, dataField);
	}
	else if (choice == 2) // Point Search
	{
		dataField = askDataFieldSearch();

		if (dataField >= 3 && dataField <= 5) // the key is a string
		{
			pointSearchStrings(askForSearchKey_string(), dataField);
		}
		else // key is a number
		{
			pointSearchNumbers<double>(askForSearchKey_Num(), dataField);
		}
	}

	
		
}
