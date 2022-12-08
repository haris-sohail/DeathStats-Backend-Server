#pragma once
template <class T>
class TreeNode
{
public:
	T val;
	TreeNode* left;
	TreeNode* right;

	string nodeFileName; // stores the filename in which node is stored
	SLinkedList<string> file;
	SLinkedList<int> line;

	int height;

	TreeNode()
	{
		val = 0;
		left = NULL;
		right = NULL;
	}

	TreeNode(T d, TreeNode* leftVal, TreeNode* rightVal)
	{
		val = d;
		left = leftVal;
		this->right = rightVal;
	}

	TreeNode(T d)
	{
		val = d;
	}

	void setval(T d)
	{
		val = d;
	}

	void setNext(TreeNode* n)
	{
		next = n;
	}

	T getval()
	{
		return val;
	}

	TreeNode* getNext()
	{
		return next;
	}

};