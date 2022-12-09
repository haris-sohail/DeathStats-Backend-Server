//#pragma once
//#include"TreeNode.h"
//#include"Stack.h"
//#include"Util.h"
//#include"Queue.h"
//using namespace std;
//
//class AVLString
//{
//public:
//	TreeNode<string>* root;
//
//public:
//	AVLString()
//	{
//		root = NULL;
//	}
//
//	TreeNode<string>*& getRoot()
//	{
//		return root;
//	}
//
//	int getTotalAsciiValue(string toCalculate)
//	{
//		int asciiValue = 0;
//		for (int i = 0; i < toCalculate.length(); i++)
//		{
//			asciiValue += toCalculate[i];
//		}
//
//		return asciiValue;
//	}
//
//	TreeNode<string>* insert(string data, string filename, int line, TreeNode<string>* root)
//	{
//		if (root == NULL)
//		{
//			root = new TreeNode<string>;
//
//			root->val = data;
//			root->file.insert(filename);
//			root->line.insert(line);
//			root->left = NULL;
//			root->right = NULL;
//		}
//		else if (getTotalAsciiValue(data) < getTotalAsciiValue(root->val)) // insertion in left subtree
//		{
//			root->left = insert(data, filename, line, root->left);
//
//			//check imbalancing 
//			if (height(root->left) - height(root->right) == 2)
//			{
//				if (data < root->left->val)
//				{
//					root = RR(root);
//				}
//				else
//				{
//					root = RL(root);
//				}
//			}
//		}
//		else if (getTotalAsciiValue(data) > getTotalAsciiValue(root->val)) // insertion in right subtree
//		{
//			root->right = insert(data, filename, line, root->right);
//
//			// check imbalancing
//			if (height(root->right) - height(root->left) == 2) // right is heavy
//			{
//				if (data > root->right->val)
//				{
//					root = LL(root);
//				}
//				else
//				{
//					root = LR(root);
//				}
//			}
//		}
//
//		root->height = getMax(height(root->left), height(root->right)) + 1;
//
//		return root;
//	}
//
//	int height(TreeNode<string>* root)
//	{
//		// base case: empty tree has a height of 0
//		if (root == nullptr) {
//			return -1;
//		}
//
//		// recur for the left and right subtree and consider maximum depth
//		return 1 + getMax(height(root->left), height(root->right));
//	}
//
//	bool retreive(string data)
//	{
//		TreeNode<string>* current = root;
//		string searchDataItem;
//
//		// tree is not initialized
//		if (root == NULL)
//		{
//			cout << "Tree is undefined" << endl;
//			return false;
//		}
//
//		else
//		{
//			while (current)
//			{
//				if (getTotalAsciiValue(data) < getTotalAsciiValue(current->val))
//				{
//					current = current->left;
//				}
//				else if (getTotalAsciiValue(data) > getTotalAsciiValue(current->val))
//				{
//					current = current->right;
//				}
//				else if (getTotalAsciiValue(data) == getTotalAsciiValue(current->val))
//				{
//					searchDataItem = current->val;
//					return true;
//				}
//			}
//
//			return false;
//		}
//	}
//
//	void preOrder(TreeNode<string>*& root)
//	{
//		if (root == NULL)
//		{
//			return;
//		}
//
//		// root - left - right
//		cout << root->val;
//
//		preOrder(root->left);
//
//		preOrder(root->right);
//	}
//
//	void postOrder(TreeNode<string>*& root)
//	{
//		if (root == NULL)
//		{
//			return;
//		}
//
//		// left - right - root
//
//		preOrder(root->left);
//
//		preOrder(root->right);
//
//		cout << root->val;
//	}
//
//	void InOrder(TreeNode<string>*& root)
//	{
//		if (root == NULL)
//		{
//			return;
//		}
//
//		// left - root - right
//
//		preOrder(root->left);
//
//		cout << root->val;
//
//		preOrder(root->right);
//	}
//
//	void LevelOrder(TreeNode<string>* root)
//	{
//		// enque all children of the front TreeNode on the queue
//		// then deque the front TreeNode
//		TreeNode<string>* current = root;
//		Queue<TreeNode<string>> q;
//		q.Enqueue(*current);
//
//		TreeNode<int>* visit;
//
//		while (!q.isEmpty())
//		{
//			TreeNode<string> visit = q.Dequeue();
//			cout << visit.val << " ";
//
//			if (visit.left != NULL)
//			{
//				//current = current->left;
//				q.Enqueue(*visit.left);
//			}
//
//			if (visit.right != NULL)
//			{
//				//current = current->right;
//				q.Enqueue(*visit.right);
//			}
//
//		}
//
//	}
//
//	string getMin()
//	{
//		TreeNode <string>* current = this->root;
//
//		string val;
//		// we are going to iterate towards the left until we find NULL
//
//		while (current)
//		{
//			val = current->val;
//
//			current = current->left;
//		}
//
//		return val;
//	}
//
//	string getMin(TreeNode<string>*& startFrom)
//	{
//		TreeNode <string>* current = this->root;
//
//		string val;
//		// we are going to iterate towards the left until we find NULL
//
//		while (current)
//		{
//			val = current->val;
//
//			startFrom = current;
//			current = current->left;
//		}
//
//		return val;
//	}
//
//	int getMax(int n1, int n2)
//	{
//		if (n1 > n2) return n1;
//
//		else
//			return n2;
//	}
//
//	TreeNode<string>* LL(TreeNode<string>* K1)
//	{
//		TreeNode<string>* K2;
//		K2 = K1->right;
//
//		K1->right = K2->left;
//		K2->left = K1;
//
//		K1->height = getMax(height(K1->left), height(K1->right)) + 1;
//		K2->height = getMax(height(K2->right), K1->height) + 1;
//		return K2;
//	}
//
//	TreeNode<string>* RR(TreeNode<string>* K1)
//	{
//		TreeNode<string>* K2 = K1->left;
//		K1->left = K2->right;
//		K2->right = K1;
//
//		K1->height = getMax(height(K1->left), height(K1->right)) + 1;
//		K2->height = getMax(height(K2->left), K1->height) + 1;
//		return K2;
//	}
//
//	TreeNode<string>* LR(TreeNode<string>* K1)
//	{
//		K1->right = RR(K1->right);
//
//		return LL(K1);
//	}
//
//	TreeNode<string>* RL(TreeNode<string>* K1)
//	{
//		K1->left = LL(K1->left);
//
//		return RR(K1);
//	}
//
//	TreeNode<string>* balance(TreeNode<string>* root)
//	{
//		if (height(root->left) - height(root->right) == 2) // left tree is heavy
//		{
//			RR(root);
//		}
//		else if (height(root->right) - height(root->left) == 2) // right is heavy
//		{
//			LL(root);
//		}
//	}
//};