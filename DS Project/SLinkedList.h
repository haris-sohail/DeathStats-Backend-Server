#pragma once
#include<iostream>
#include"Node.h"
using namespace std;

template <class T>
class SLinkedList {

public:

	node<T>* head;


	SLinkedList()
	{
		head = NULL;
	}

	template<class T>
	void insert(T data)
	{
		node<T>* newnode = new node<T>(data);
		newnode->next = NULL;

		if (head == NULL)
		{
			head = newnode;
		}
		else
		{
			node<T>* currentnode = head;
			while (currentnode->next != NULL)
			{
				currentnode = currentnode->next;
			}
			currentnode->next = newnode;
		}
	}

	template<class T>
	void insertAtHead(T data)
	{
		node <T>* newnode = new node<T>(data);
		newnode->next = head;

		head = newnode;
	}

	template<class T>
	void InsertAtIndex(T data, int index)
	{
		node <T>* newnode = new node<T>(data);

		if (index < 0) return;

		// traverse to the index
		node <T>* currentnode = head;
		int currentIndex = 1;

		while (currentnode && currentIndex != index)
		{
			currentnode = currentnode->next;
			currentIndex++;
		}

		if (index > 0 && currentnode == NULL) return; // not found

		if (index == 0) // insert at head
		{
			newnode->next = head;
			head = newnode;
		}
		else
		{
			newnode->next = currentnode->next;
			currentnode->next = newnode;
		}

	}

	template<class T>
	int search(T data)
	{
		// traverse until data is found
		node<T>* currentnode = head;
		int currentIndex = 0;

		while (currentnode && currentnode->data != data)
		{
			currentnode = currentnode->next;
			currentIndex++;
		}
		if (currentnode == NULL) return -1; // not found

		return currentIndex;
	}

	template<class T>
	void update(int index, T data)
	{
		// traverse until the index is found
		int currentIndex = 0;
		node<T>* currentnode = head;

		if (index < 0) return;

		while (currentnode && currentIndex != index)
		{
			currentnode = currentnode->next;
			currentIndex++;
		}

		if (index > 0 && currentnode == NULL) return; // not found

		currentnode->data = data;
	}

	template<class T>
	void remove(T data)
	{
		node<T>* currentnode = head;
		node<T>* previousnode = NULL;
		node<T>* tempnode = new node<T>;

		if (data == head->data) // delete head
		{
			tempnode = head;
			head = head->next;
			delete tempnode;
		}
		else
		{
			// traverse to that index
			while (currentnode && data != currentnode->data)
			{
				previousnode = currentnode;
				currentnode = currentnode->next;
			}
			if (currentnode == NULL) return; // data not found

			tempnode = currentnode;
			previousnode->next = currentnode->next;
			delete tempnode;
		}
	}

	void print()
	{
		node<T>* currentnode = head;
		// traverse thorugh entrire list
		while (currentnode != NULL)
		{
			cout << currentnode->val << " ";
			currentnode = currentnode->next;
		}
		cout << endl;
	}

	template<class T>
	void mergeLists(SLinkedList<T> obj)
	{
		// traverse through the first list
		node<T>* tempList = new node<T>;

		node<T>* currentnode = new node<T>;
		currentnode = head;

		while (currentnode)
		{
			currentnode = currentnode->next;
		}
		currentnode = obj.head;

		while (currentnode)
		{
			currentnode = currentnode->next;
		}

		this->head = tempList;
	}




};