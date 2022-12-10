//In my solituuuuuuuuuuuuuuuude
#include<iostream>
#include"SLinkedList.h"
#include"AVL.h"
#include"AVLString.h"
#include"Util.h"
using namespace std;

int main()
{	
	int choice = displayMenu();
	if (choice == 1)
	{
		createAVL(askDataField());
	}
		
}
