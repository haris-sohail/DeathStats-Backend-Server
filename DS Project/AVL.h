#pragma once
#include"TreeNode.h"
#include"Stack.h"
#include"Queue.h"
template <class T>
class AVL
{
public:
	TreeNode<T>* root;

public:
	AVL()
	{
		root = NULL;
	}

	TreeNode<T>*& getRoot()
	{
		return root;
	}

	TreeNode<T>* insert(T data, TreeNode<T>* root)
	{
		if (root == NULL)
		{
			root = new TreeNode<T>;
			root->val = data;
			root->left = NULL;
			root->right = NULL;
		}
		else if (data < root->val) // insertion in left subtree
		{
			root->left = insert(data, root->left);

			//check imbalancing 
			if (height(root->left) - height(root->right) == 2)
			{
				if (data < root->left->val)
				{
					root = RR(root);
				}
				else
				{
					root = RL(root);
				}
			}
		}
		else if (data > root->val) // insertion in right subtree
		{
			root->right = insert(data, root->right);

			// check imbalancing
			if (height(root->right) - height(root->left) == 2) // right is heavy
			{
				if (data > root->right->val)
				{
					root = LL(root);
				}
				else
				{
					root = LR(root);
				}
			}
		}

		root->height = getMax(height(root->left), height(root->right)) + 1;

		return root;
	}

	int height(TreeNode<T>* root)
	{
		// base case: empty tree has a height of 0
		if (root == nullptr) {
			return -1;
		}

		// recur for the left and right subtree and consider maximum depth
		return 1 + getMax(height(root->left), height(root->right));
	}

	bool retreive(T data)
	{
		TreeNode<T>* current = root;
		T searchDataItem;

		// tree is not initialized
		if (root == NULL)
		{
			cout << "Tree is undefined" << endl;
			return false;
		}

		else
		{
			while (current)
			{
				if (data < current->val)
				{
					current = current->left;
				}
				else if (data > current->val)
				{
					current = current->right;
				}
				else if (data == current->val)
				{
					searchDataItem = current->val;
					return true;
				}
			}

			return false;
		}
	}

	void preOrder(TreeNode<T>*& root)
	{
		if (root == NULL)
		{
			return;
		}

		// root - left - right
		cout << root->val;

		preOrder(root->left);

		preOrder(root->right);
	}

	void postOrder(TreeNode<T>*& root)
	{
		if (root == NULL)
		{
			return;
		}

		// left - right - root

		preOrder(root->left);

		preOrder(root->right);

		cout << root->val;
	}

	void InOrder(TreeNode<T>*& root)
	{
		if (root == NULL)
		{
			return;
		}

		// left - root - right

		preOrder(root->left);

		cout << root->val;

		preOrder(root->right);
	}

	void LevelOrder(TreeNode<T>* root)
	{
		// enque all children of the front TreeNode on the queue
		// then deque the front TreeNode
		TreeNode<T>* current = root;
		Queue<TreeNode<T>> q;
		q.Enqueue(*current);

		TreeNode<int>* visit;

		while (!q.isEmpty())
		{
			TreeNode<T> visit = q.Dequeue();
			cout << visit.val << " ";

			if (visit.left != NULL)
			{
				//current = current->left;
				q.Enqueue(*visit.left);
			}

			if (visit.right != NULL)
			{
				//current = current->right;
				q.Enqueue(*visit.right);
			}

		}

	}

	T getMin()
	{
		TreeNode <T>* current = this->root;

		T val;
		// we are going to iterate towards the left until we find NULL

		while (current)
		{
			val = current->val;

			current = current->left;
		}

		return val;
	}

	T getMin(TreeNode<T>*& startFrom)
	{
		TreeNode <T>* current = this->root;

		T val;
		// we are going to iterate towards the left until we find NULL

		while (current)
		{
			val = current->val;

			startFrom = current;
			current = current->left;
		}

		return val;
	}	

	int getMax(int n1, int n2)
	{
		if (n1 > n2) return n1;

		else
			return n2;
	}

	TreeNode<T>* LL(TreeNode<T>* K1)
	{
		TreeNode<T>* K2;
		K2 = K1->right;

		K1->right = K2->left;
		K2->left = K1;

		K1->height = getMax(height(K1->left), height(K1->right)) + 1;
		K2->height = getMax(height(K2->right), K1->height) + 1;
		return K2;
	}

	TreeNode<T>* RR(TreeNode<T>* K1)
	{
		TreeNode<T>* K2 = K1->left;
		K1->left = K2->right;
		K2->right = K1;

		K1->height = getMax(height(K1->left), height(K1->right)) + 1;
		K2->height = getMax(height(K2->left), K1->height) + 1;
		return K2;
	}

	TreeNode<T>* LR(TreeNode<T>* K1)
	{
		K1->right = LL(K1->right);

		return RR(K1);
	}

	TreeNode<T>* RL(TreeNode<T>* K1)
	{
		K1->left = RR(K1->left);

		return LL(K1);
	}

	TreeNode<T>* balance(TreeNode<T>* root)
	{
		if (height(root->left) - height(root->right) == 2) // left tree is heavy
		{
			RR(root);
		}
		else if (height(root->right) - height(root->left) == 2) // right is heavy
		{
			LL(root);
		}
	}

};