 
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

	bool _isNil( const Node* node )
	{
		if (node == NULL || node == _NIL || node == _end)
			return true;
		return false;
	}

	void _recolor( Node* node )
	{
		if (_isNil(node))
			return;
		node->red = !node->red;
	}

	void _insertRight( Node* parent, Node* child)
	{
		if (_isNil(parent) || _isNil(child))
			return;

		parent->right = child;
		child->parent = parent;
	}

	void _insertLeft( Node* parent, Node* child)
	{
		if (_isNil(parent) || _isNil(child))
			return;

		parent->left = child;
		child->parent = parent;
	}

	void _rotateRight( Node* node )
	{
		Node* parent;
		Node* child;

		parent = node->parent;
		child = node->left;

		if (node == _root)
			_setRoot(child);
		else if (!_isNil(parent) && parent->right == node)
			parent->right = child;
		else if (!_isNil(parent))
			parent->left = child;

		child->parent = node->parent;
		node->parent = child;
		node->left = child->right;
		child->right = node;
	}

	void _rotateLeft( Node* node )
	{
		Node* parent;
		Node* child;

		parent = node->parent;
		child = node->right;

		if (node == _root)
			_setRoot(child);
		else if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;

		child->parent = node->parent;
		node->parent = child;
		node->right = child->left;
		child->left = node;
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
		if (node->data == root->data)
			return root;
		if (node->data < root->data)
		{
			if (_isNil(root->left))
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
			if (_isNil(root->right))
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

		if (_isNil(node) || !node->parent->red)
		{
			return ;
		}
	
		if (!_isNil(node->parent))
			grandP = node->parent->parent;
		aunt = getSibling(node->parent);
		
		// aunt is black or nil
		if (_isNil(aunt) || !aunt->red)
		{
			save = node->parent;
			// left left and left right
			if (node->parent == grandP->left)
			{
				if (node->parent->right == node)
				{
					_rotateLeft(node->parent);
					save = node;
				}
				_rotateRight(grandP);
			}
			else // right right and right left
			{
				if (node->parent->left == node)
				{
					_rotateRight(node->parent);
					save = node;
				}
				_rotateLeft(grandP);
			}
			_recolor(grandP);
			_recolor(save);
		}
		else
		{
			_recolor(node->parent);
			_recolor(aunt);
			if (grandP != _root)
			{
				_recolor(grandP);
				if (!_isNil(grandP) && grandP != _root)	
					_rbInsertFix(grandP);
			}
		}
	_root->red = false;
	}

public:
	RBTree()
	{
		_end = _createNode(0, false);
		_NIL = _createNode(0, false);
		_root = _end;
	}

	~RBTree()
	{
		delete _end;
	}

	Node* insert( const int & data )
	{
		Node* node = _createNode(data, true);

		// if tree is empty, new node becomes root
		if (_isNil(_root) || _root == _end) {
			_setRoot(node);
			return node;
		}
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
		if (_isNil(root))
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
		if (!_isNil(node))
		{
			return node;
		}
		if (_isNil(node->right))
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
		if (_isNil(root))
			return root;
		return max(root->left);

	}

	Node* inorderSucc( Node* root )
	{
		if (_isNil(root))
			return root;
		return min(root->right);
	}

	Node* min( Node* root)
	{
		if (!_isNil(root) && !_isNil(root->left))
		{
			return root->left;
		}
		return root;
	}

	Node* max( Node* root)
	{
		if (!_isNil(root) && !_isNil(root->right))
		{
			return root->right;
		}
		return root;
	}

	Node* getSibling( Node* node )
	{
		if (_isNil(node) || _isNil(node->parent))
		{
			return NULL;
		}
		if (node->parent->right == node)
		{
			return node->parent->left;
		}
		return node->parent->right;

	}

	void printTree()
	{
		for (int level = 0; level <= _getHeight(_root, 0); level++)
		{
			printLevel(level);
			cout << endl;
		}
		cout << "___" << endl;
	}
		
	void printLevel(int level)
	{
		Node* temp = _root;
		int depth = pow(2, _getHeight(_root, 0) - level + 2);

		cout << setw(depth) << "";
		displayLevel(temp, level, depth);
	}
		
	void displayLevel(Node* node, int level, int depth)
	{
		int disp = 2 * depth;
		if (level == 0)
		{
			if (_isNil(node))
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
			if (_isNil(node) && level >= 1)
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

	int _getHeight(const Node* root, int height)
	{
		int leftH = 0;
		int rightH = 0;

		if (_isNil(root))
		{
			return height - 1;
		} 
		else {
			leftH = _getHeight(root->left, height + 1);
			rightH = _getHeight(root->right, height + 1);
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
};

#endif