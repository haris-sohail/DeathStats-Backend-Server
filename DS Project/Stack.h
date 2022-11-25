#pragma once
#include"Node.h"
#include<iostream>
using namespace std;

template <class T>
class stack
{
public:
	node<T>* head;

public:

	stack()
	{
		head = NULL;
	}

	void push(const T val)
	{
		node<T>* newnode = new node<T>(val);

		newnode->next = head;
		head = newnode;
	}

	T Peek()
	{
		return head->val;
	}

	void display()
	{
		node <T>* current = head;
		while (current)
		{
			cout << current->val << " ";
			current = current->next;
		}
	}

	int getTop()
	{
		return head->val;
	}

	T pop()
	{
		if (!isEmpty())
		{
			T data;

			node <T>* temp = head;

			head = head->next;

			data = temp->val;

			delete temp;

			return data;
		}
		else
		{
			cout << "Stack is empty" << endl;
			return 0;
		}

	}

	int sizeofstack()
	{
		int size = 0;
		if (!isEmpty())
		{
			node<T>* current = head;

			while (current)
			{
				size++;
				current = current->next;
			}

			return size;
		}
		return 0;
	}

	bool isEmpty()
	{
		if (head == NULL)
		{
			return true;
		}
		return false;
	}



	~stack()
	{
		node <T>* currentnode = head;
		node <T>* temp;
		while (currentnode)
		{
			temp = currentnode;
			currentnode = currentnode->next;
			delete temp;
		}

		head = NULL;
	}
};
