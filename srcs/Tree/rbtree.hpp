 
#pragma once
#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>

using std::cout;
using std::string;
using std::endl;
using std::setw;

class RBTree {
private:
	struct Node {
		int data;
		Node* left;
		Node* right;
		Node* parent;
		bool red;

		Node() {
			data = 0;
			left = NULL;
			right = NULL;
			parent = NULL;
			red = true;
		}

		Node(const int & data) {
			this->data = data;
			left = NULL;
			right = NULL;
			parent = NULL;
			red = true;
		}
	};

	Node* _root;
	Node* _end;
	const int _SPACECOUNT;


	Node* _createNode(const int & data)
	{
		Node* node = new Node(data);
		return node;
	}

	void _setRoot( Node* node )
	{
		_root = node;
		if (_root)
		{
			_end->left = _root;
			_root->parent = _end;
		}
	}

	void _insertRight( Node* parent, Node* child)
	{
		if (!parent || !child)
			return;

		parent->right = child;
		child->parent = parent;
	}

	void _insertLeft( Node* parent, Node* child)
	{
		if (!parent || !child)
			return;

		parent->left = child;
		child->parent = parent;
	}

	void _transplant( Node* src, Node* dst)
	{
		if (!src || !dst)
			return;
		if (dst->parent->left == dst)
			dst->parent->left = src;
		else
			dst->parent->right = src;
		src->parent = dst->parent;
		 
		delete dst;
	}

	Node* _insert( Node* root, Node* node )
	{
		if (!_root || _root == _end) {
			_setRoot(node);
		}
		else if (node->data < root->data)
		{
			if (!root->left)
			{
				_insertLeft(root, node);
			}
			else
			{
				return _insert(root->left, node);
			}
		}
		else if (node->data > root->data)
		{
			if (!root->right)
			{
				_insertRight(root, node);
			}
			else
			{
				return _insert(root->right, node);
			}
		}
		return node;
	}

	Node* _insertFix( Node* root )
	{
		
	}

public:
	RBTree(): _SPACECOUNT(5)
	{
		_end = _createNode(0);
		_root = _end;
	}

	~RBTree()
	{
		delete _end;
	}

	Node* insert( const int & data )
	{
		Node* node = _createNode(data);
		return _insert(_root, node);	
	}

	void deleteNode( const int & data )
	{
		Node* node = findNode(_root, data);
		
		if (node)
		{
			cout << "deleteNode found node with value " << data << endl;
		}

	}

	Node* findNode(Node* root, const int & data ) {
		if (!root)
			return root;
		if (root->data == data)
			return root;
		if (root->data < data)
			return findNode(root->right, data);
		else
			return findNode(root->left, data);
	}

	Node* next( Node* node )
	{
		if (!node)
		{
			return node;
		}
		if (node->right)
		{
			return node->right;
		}
		if (node->parent == _end || node == _end)
		{
			return _end;
		}

		return node->parent;
	}

	Node* inorderPre( Node* root )
	{
		if (!root)
			return root;
		return max(root->left);

	}

	Node* inorderSucc( Node* root )
	{
		if (!root)
			return root;
		return min(root->right);
	}

	Node* min( Node* root)
	{
		if (root && root->left)
		{
			return root->left;
		}
		return root;
	}

	Node* max( Node* root)
	{
		if (root && root->right)
		{
			return root->right;
		}
		return root;
	}

	void printTree()
	{
		int i = 0;
		while (i <= _getHeight(_root, 0))
		{
			printLevel(i);
			i++;
			cout << endl;
		}
	}
		
	void printLevel(int n)
	{
		Node* temp = _root;
		int depth = pow(2, _getHeight(_root, 0) -n+2);

		cout << setw(depth) << "";
		displayLevel(temp, n, depth);
	}
		
	void displayLevel(Node* node, int level, int depth)
	{
		int disp = 2 * depth;
		if (level == 0)
		{
			if (node == NULL)
			{

				cout << " x ";
				cout << setw(disp - 3) << "";
				return;
			}
			else 
			{
				int result = ((node->data <= 1) ? 1 : log10(node->data) + 1);
				if (node->red)
					cout << "\033[1;31m";
				else
					cout << "\033[1;37m";
				cout << " " << node->data << " ";
				cout << setw(disp - result-2) << "";
				cout << "\033[0m";
			}
		}
		else
		{
			if (node == NULL&& level >= 1)
			{
				displayLevel(NULL, level - 1, depth);
				displayLevel(NULL, level - 1, depth);
			}
			else
			{
				displayLevel(node->left, level - 1, depth);
				displayLevel(node->right, level - 1, depth);
			}
		}
	}

	// void printTree() {
	// 	string* lines;
	// 	int height = 0;
	// 	int length = 0;

	// 	height = _getHeight(_root, 0);
	// 	length = _getLength(_root);
	// 	cout << "length: " << length << endl << "height: " << height << endl;
	// 	lines = new string[height * 2];

	// 	// _fillPrintLines(_root, lines);

	// }

	// int _getLength(Node* root) {
	// 	Node* mover = _root;
	// 	int length = 0;

	// 	while (mover && mover->left) {
	// 		length++;
	// 		mover = mover->left;
	// 	}
	// 	mover = root;
	// 	while (mover && mover->right) {
	// 		length++;
	// 		mover = mover->right;
	// 	}
	// 	return length;
	// }

	int _getHeight(const Node* root, int height) {
		int distance = 0;
		int leftH = 0;
		int rightH = 0;

		if (!root) {
			return height;
		} 
		else {
			leftH = _getHeight(root->left, height + 1);
			rightH = _getHeight(root->right, height + 1);
			if (leftH < rightH || leftH == rightH) {
				return leftH;
			} 
			else {
				return rightH;
			}
		}
	}

	// void printTree(Node* root) {
	// 	_printTreeUtil(root, 0)
	// }

	// void _printTreeUtil(Node* root, int length) {
	// 	if (!root)
	// 		return;
	
	// 	// Increase distance between levels
	// 	length += _SPACECOUNT;
	
	// 	// Process right child first
	// 	_printTreeUtil(root->right, length);
	
	// 	// Print current node after space
	// 	// count
	// 	cout << endl;
	// 	for (int i = _SPACECOUNT; i < _SPACECOUNT; i++)
	// 		cout << " ";
	// 	cout << root->data << "\n";
	
	// 	// Process left child
	// 	_printTreeUtil(root->left, space);
	// }
};

#endif