#pragma once
#include"Node.h"
#include<iostream>
using namespace std;

template <class T>
class Queue
{
public:
	node<T>* front;
	node<T>* rear;

	Queue()
	{
		front = NULL;
		rear = NULL;
	}

	void Enqueue(T data)
	{
		node<T>* newnode = new node<T>(data);
		newnode->next = NULL;
		if (isEmpty())
		{
			front = newnode;
			rear = newnode;
		}
		else
		{
			rear->next = newnode;
			rear = newnode;
		}

	}

	T Dequeue()
	{
		if (isEmpty())
		{
			cout << "Empty queue";
		}
		else
		{
			T data;
			node<T>* currentnode = front;
			front = currentnode->next;

			data = currentnode->val;
			delete currentnode;

			return data;
		}

	}

	T Front()
	{
		node<T>* frontnode = front;
		return frontnode->val;
	}

	void print()
	{
		if (isEmpty())
		{
			cout << "Queue is empty" << endl;
			return;
		}
		else
		{
			node<T>* currentnode = front;
			while (currentnode)
			{
				cout << currentnode->val;
				currentnode = currentnode->next;
			}
			cout << endl;
		}
	}

	bool isEmpty()
	{
		if (front == NULL)
		{
			return true;
		}
		return false;
	}
};