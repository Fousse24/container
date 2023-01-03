 
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
	Node* _NIL;

	Node* _createNode(const int & data, bool red)
	{
		Node* node = new Node(data);
		node->left = _NIL;
		node->right = _NIL;
		node->red = red;
		return node;
	}

	void _setRoot( Node* node )
	{
		_root = node;
		if (_root)
		{
			_end->left = _root;
			_root->parent = _end;
			_root->red = false;
		}
	}

	void _deleteRoot(  )
	{
		delete _root;
		_end->left = _NIL;
	}

	void _recolor( Node* node )
	{
		if (isNil(node) || node == _root)
			return;
		node->red = !node->red;
	}

	void _insertRight( Node* parent, Node* child)
	{
		if (isNil(parent) || isNil(child))
			return;

		parent->right = child;
		child->parent = parent;
	}

	void _insertLeft( Node* parent, Node* child)
	{
		if (isNil(parent) || isNil(child))
			return;

		parent->left = child;
		child->parent = parent;
	}

	void _rotateRight( Node* node )
	{
		Node* child;

		child = node->left;
		if (node == _root)
			_setRoot(child);
		else
			_giveParent(node, child);

		node->parent = child;
		node->left = child->right;
		node->left->parent = node;
		child->right = node;
	}

	void _rotateLeft( Node* node )
	{
		Node* child;

		child = node->right;
		if (node == _root)
			_setRoot(child);
		else
			_giveParent(node, child);

		node->parent = child;
		node->right = child->left;
		node->right->parent = node;
		child->left = node;
	}

	// Replace <dst>'s data with <src>'s
	Node* _transplantData( Node* src, Node* dst )
	{
		// TODO delete dst->data somehow
		dst->data = src->data;
		return dst;
	}

	// Orphan <current> and assign its parent to <newChild> (if not NIL)
	void _giveParent( Node* current, Node* newChild )
	{
		if (current->parent->left == current)
			current->parent->left = newChild;
		else if (current->parent->right == current)
			current->parent->right = newChild;
		else
			return;
		
		if (!isNil(newChild))
			newChild->parent = current->parent;
	}


	Node* _insert( Node* root, Node* node )
	{
		if (node->data == root->data)
			return root;
		if (node->data < root->data)
		{
			if (isNil(root->left))
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
			if (isNil(root->right))
			{
				_insertRight(root, node);
			}
			else
			{
				return _insert(root->right, node);
			}
		}
		_rbInsertFix(node);
		return node;
	}

	void _rbInsertFix( Node* node )
	{
		Node* grandP = NULL;
		Node* aunt = NULL;
		Node* save = NULL;

		// Exit if parent is black
		if (isNil(node) || !node->parent->red)
		{
			return ;
		}
	
		if (!isNil(node->parent))
			grandP = node->parent->parent;
		aunt = getSibling(node->parent);
		
		// aunt is nil or black
		if (isNil(aunt) || !aunt->red)
		{
			save = node->parent;
			if (node->parent == grandP->left)
			{
				// left right
				if (node->parent->right == node)
				{
					_rotateLeft(node->parent);
					save = node;
				}
				// left left
				_rotateRight(grandP);
			}
			else
			{
				// right left
				if (node->parent->left == node)
				{
					_rotateRight(node->parent);
					save = node;
				}
				// right right
				_rotateLeft(grandP);
			}
			_recolor(grandP);
			_recolor(save);
		}
		else
		{
			_recolor(node->parent);
			_recolor(aunt);
			if (!isNil(grandP) && grandP != _root)
			{
				_recolor(grandP);
				// Recheck with grand parent as critical node
				_rbInsertFix(grandP);
			}
		}
	_root->red = false;
	}

	void _delete( Node* node )
	{
		Node* replacement = NULL;
		bool wasRed;
		bool doubleBlack = false;

		if (isNil(node))
			return ;
		/* 
		 * 1.	0 child
		 * 2.	2 children
		 * 3.	1 child
		 *  3.1.	left child
		 *  3.2.	right child
		*/
		wasRed = node->red;
		// 0 child
		if (isNil(node->right) && isNil(node->left))
		{
			_giveParent(node, _NIL);
			delete node;
		}
		else
		{ 
			// 2 and 1 child cases 
			if (!isNil(node->left) && !isNil(node->right))
			{
				replacement = inorderSucc(node);
			}
			else
			{
				if (!isNil(node->left))
					replacement = node->left;
				else
					replacement = node->right;
				
			}
			cout << "got successor which is " << replacement->data << " with parent " << replacement->parent->data << endl;
			node = _transplantData(replacement, node);
			_delete(replacement);
		}

		// If deleted node was red, we need to fix the rbtree
		// if (!wasRed)
		// 	_rbDeleteFix();
	}

	Node* _rbDeleteFix( Node* node )
	{
		// Node* replacement = NULL;
		// Node* sibling;
		// bool wasRed;

		// if (isNil(node))
		// 	return;
		// /* 
		//  * 1.	no children
		//  * 2.	2 children
		//  * 3.	1 child
		//  *  3.1.	left child
		//  *  3.2.	right child
		// */
		// wasRed = node->red;
		// replacement = inorderSucc(node);
		// _transplantData(replacement, node);
		// /*
		//  * Case 1: Node is red
		//  */
		// if (node->red)
		// {
		// 	return _delete(replacement);
		// }

		// /*
		//  * Case 2: Node is black
		//  */
		// if (isNil(node->right) && isNil(node->left))
		// {
		// 	sibling = getSibling(node);
		// 	if (!sibling->red)
		// 	{
		// 		if (node->parent->red)
		// 			_recolor(node->parent);
		// 		else
		// 		{

		// 		}
		// 		_recolor(sibling);
		// 	}
		// 	else
		// 	{
		// 		_recolor(node->parent);
		// 		_recolor(sibling);
		// 		if (node->parent->left == node)
		// 			_rotateLeft(node->parent);
		// 		else
		// 			_rotateRight(node->parent);
		// 	}
		// 	_giveParent(node, _NIL);
		// 	delete node;
		// }
		// else
		// { 
		// 	if (!isNil(node->left) && !isNil(node->right))
		// 	{
		// 		replacement = inorderSucc(node);
		// 		node = _transplantData(replacement, node);
		// 	}
		// 	else
		// 	{
		// 		if (!isNil(node->left))
		// 			replacement = node->left;
		// 		else
		// 			replacement = node->right;
		// 	}
		// 	_delete(replacement);
		// }

		// // If deleted node was red, we need to fix the rbtree
		// if (!wasRed)
		// 	_rbDeleteFix();
		return _NIL;
	}

public:
	RBTree()
	{
		_end = _createNode(0, false);
		_NIL = _createNode(0, false);
		_setRoot(_end);
	}

	~RBTree()
	{
		delete _end;
	}

	Node* insert( const int & data )
	{
		Node* node = _createNode(data, true);

		// if tree is empty, new node becomes root
		if (isNil(_root) || _root == _end) {
			_setRoot(node);
			return node;
		}
		return _insert(_root, node);	
	}

	void deleteNode( const int & data )
	{
		Node* node = findNode(_root, data);
		Node* preNode;
		Node* child = NULL;
		
		if (isNil(node))
			return;

		cout << "Found delete node which is " << node->data << " with parent " << node->parent->data << endl;
		_delete(node);
	}

	Node* findNode(Node* root, const int & data ) {
		if (isNil(root))
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
		if (!isNil(node))
		{
			return node;
		}
		if (isNil(node->right))
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
		if (isNil(root))
			return root;
		return max(root->left);

	}

	Node* inorderSucc( Node* root )
	{
		if (isNil(root))
			return root;
		return min(root->right);
	}

	Node* min( Node* root)
	{
		while (!isNil(root) && !isNil(root->left))
		{
			root = root->left;
		}
		return root;
	}

	Node* max( Node* root)
	{
		while (!isNil(root) && !isNil(root->right))
		{
			root = root->right;
		}
		return root;
	}

	Node* getSibling( Node* node )
	{
		if (isNil(node) || isNil(node->parent))
		{
			return _NIL;
		}
		if (node->parent->right == node)
		{
			return node->parent->left;
		}
		return node->parent->right;

	}

	void printTree()
	{
		for (int level = 0; level <= getHeight(_root, 0); level++)
		{
			printLevel(level);
			cout << endl;
		}
		cout << "___" << endl;
	}
		
	void printLevel(int level)
	{
		Node* temp = _root;
		int depth = pow(2, getHeight(_root, 0) - level + 2);

		cout << setw(depth) << "";
		displayLevel(temp, level, depth);
	}
		
	void displayLevel(Node* node, int level, int depth)
	{
		int disp = 2 * depth;
		if (level == 0)
		{
			if (isNil(node))
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
			if (isNil(node) && level >= 1)
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

	int getHeight(const Node* root, int height)
	{
		int leftH = 0;
		int rightH = 0;

		if (isNil(root))
		{
			return height - 1;
		} 
		else {
			leftH = getHeight(root->left, height + 1);
			rightH = getHeight(root->right, height + 1);
			if (leftH > rightH || leftH == rightH) 
			{
				return leftH;
			} 
			else 
			{
				return rightH;
			}
		}
	}

	bool isNil( const Node* node )
	{
		if (node == NULL || node == _NIL || node == _end)
			return true;
		return false;
	}
};

#endif