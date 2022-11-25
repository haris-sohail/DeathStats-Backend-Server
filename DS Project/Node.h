#pragma once
#include<iostream>
using namespace std;

template <class T>
class node
{
public:
	T val;
	node* next;

	node()
	{
		next = NULL;
	}

	node(T d, node* n)
	{
		val = d;
		next = n;
	}

	node(T d)
	{
		val = d;
	}

	void setval(T d)
	{
		val = d;
	}

	void setNext(node* n)
	{
		next = n;
	}

	T getval()
	{
		return val;
	}

	node* getNext()
	{
		return next;
	}

};
