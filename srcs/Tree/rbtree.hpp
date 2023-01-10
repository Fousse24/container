 
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

/*
 * ATTRIBUTES
 *
 * CONSTRUCTORS
 *
 * PRIVATE FUNCTIONS
 *		_createNode
 *		_setRoot
 *		_deleteRoot
 *		_insertRight
 *		_insertLeft
 *		_rotateRight
 *		_rotateLeft
 *		_unlinkFromParent
 *		_insert
 *		_rbInsertFix
 *		_delete
 *		_rbDeleteFix
 *		_deleteLeaf
 *		_updateSentinel
 *		_transplantData
 *		_recolor
 *		_swapColor
 *		_giveParent
 *		_getFarNiece
 *		_getCloseNiece
 *		_getSibling
 *
 * PUBLIC FUNCTIONS
 *		getRoot
 *		insert
 *		deleteNode
 *		findNode
 *		inorderPre
 *		inorderSucc
 *		isNil
 *		min
 *		max
 *		begin
 *		end
 *		getHeight
 *		printTree
 *		printSuccessor
 *		printPredecessor
 *		printLevel
 *		displayLevel
 */

namespace ft {

template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
class RBTree {

	typedef Allocator	allocator_type;
	typedef Compare		key_compare;

/* ATTRIBUTES */
private:
	allocator_type	_alloc;

public:
	struct Node 
	{
		Key data;
		Node* left;
		Node* right;
		Node* parent;
		bool red;

		Node(Allocator alloc)
		{
			alloc.construct(&data);
			left = NULL;
			right = NULL;
			parent = NULL;
			red = true;
		}

		Node(const Key & data)
		{
			this->data = data;
			left = NULL;
			right = NULL;
			parent = NULL;
			red = true;
		}
	};

private:
	Node*			_root;
	Node*			_end;
	Node*			_NIL;
	Node*			_sentinel;
	key_compare		compare;

/*************************************************/


/* CONSTRUCTORS & DESTRUCTOR */
public:
	RBTree()
	{
		_alloc = allocator_type();
		_end = _createNode(false);
		_NIL = _createNode(false);
		_sentinel = _createNode(false);
		_setRoot(_end);
	}

	~RBTree()
	{
		delete _end;
		delete _NIL;
		delete _sentinel;
		_deleteTree(_root);
	}

/*************************************************/


/* PRIVATE FUNCTIONS */
private:
	Node* _createNode(const Key & data, bool red)
	{
		Node* node = new Node(data);
		node->left = _NIL;
		node->right = _NIL;
		node->red = red;
		return node;
	}

	Node* _createNode(bool red)
	{
		Node* node = new Node(_alloc);
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
		_end->left = _end;
	}

	void _deleteTree(Node* root)
	{
		if (isNil(root))
			return;
		if (!isNil(root->right))
			_deleteTree(root->right);
		if (!isNil(root->left))
			_deleteTree(root->left);
		delete root;
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

	void _unlinkFromParent( Node* node )
	{
		if (isNil(node) || isNil(node->parent))
			return;

		if (node->parent->left == node)
			node->parent->left = _NIL;
		else if (node->parent->right == node)
			node->parent->right = _NIL;

		return;		
	}


	Node* _insert( Node* root, Node* node )
	{
		if (node->data == root->data)
			return root;
		if (compare(node->data, root->data))
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
		else if (!compare(node->data, root->data))
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
		aunt = _getSibling(node->parent);
		
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

	// BST deletion, FIX if deleted node was black
	void _delete( Node* node )
	{
		Node* replacement = _NIL;

		if (isNil(node))
			return ;
 
		if (!isNil(node->right) || !isNil(node->left))
		{
			if (isNil(node->right) || isNil(node->left))
			{
				/* 1 child */
				if (isNil(node->right))
					replacement = node->left;
				else if (isNil(node->left))
					replacement = node->right;
				node = _transplantData(replacement, node);
				return _delete(replacement);
				/**/
			}
			else
			{ 
				/* 2 children */
				replacement = inorderSucc(node);				
				node = _transplantData(replacement, node);
				return _delete(replacement);
				/**/
			}
		}

		/* 0 child */
		// If node to be deleted is red, we need to fix the rbtree
		if (!node->red)
			_rbDeleteFix(node);
		_deleteLeaf(node);
		return ;
		/**/
	}

	void _rbDeleteFix( Node* node )
	{	
		Node* sibling;
		Node* closeNiece;
		Node* farNiece;
		bool doubleBlack = false;

		printTree();
		if (!node->red)
		{
			/* DOUBLE BLACK */
			if (node == _root)
				return;
			
			sibling = _getSibling(node);
			if (!sibling->red)
			{
				if (!sibling->left->red && !sibling->right->red)
				{
					if (node->parent->red)
						_recolor(node->parent);
					else
						doubleBlack = true;

					_recolor(sibling);
					if (doubleBlack)
						return _rbDeleteFix(node->parent);
				}
				else
				{
					closeNiece = _getCloseNiece(node);
					farNiece = _getFarNiece(node);
					if (!farNiece->red && closeNiece->red)
					{
						_swapColor(sibling, closeNiece);
						if (node == node->parent->left)
							_rotateRight(sibling);
						else
							_rotateLeft(sibling);
						sibling = _getSibling(node);
						
					}

					farNiece = _getFarNiece(node);
					if (farNiece->red)
					{
						_swapColor(node->parent, sibling);
						if (node == node->parent->left)
							_rotateLeft(node->parent);
						else
							_rotateRight(node->parent);
						_recolor(farNiece);
					}
				}
			}
			else
			{
				_swapColor(node->parent, sibling);

				if (node == node->parent->left)
					_rotateLeft(node->parent);
				else
					_rotateRight(node->parent);

				return _rbDeleteFix(node);
			}
		}
		return ;
	}

	bool _deleteLeaf(Node* leaf)
	{
		bool wasRed = false;

		if (!isNil(leaf)) 
		{
			wasRed = leaf->red;
			_unlinkFromParent(leaf);
			if (_root == leaf)
				_root = _end;
			delete leaf;
		}
		return wasRed;	
	}

	void _updateSentinel( )
	{
		_sentinel->left = min(_root);
		_sentinel->right = max(_root);
		_sentinel->parent = _end;
	}

	// Replace <dst>'s data with <src>'s
	Node* _transplantData( Node* src, Node* dst )
	{
		// TODO delete dst->data somehow
		dst->data = src->data;
		return dst;
	}

	void _recolor( Node* node )
	{
		if (isNil(node) || node == _root)
			return;
		node->red = !node->red;
	}

	void _swapColor( Node* node1, Node* node2)
	{
		bool tempRed;

		tempRed = node1->red;
		node1->red = node2->red;
		node2->red = tempRed;

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
		
		newChild->parent = current->parent;
	}

	Node* _getFarNiece( Node* node )
	{
		if (isNil(node))
			return _NIL;
		
		if (node == node->parent->left)
			return node->parent->right->right;
		else
			return node->parent->left->left;
	}

	Node* _getCloseNiece( Node* node )
	{
		if (isNil(node))
			return _NIL;
		
		if (node == node->parent->left)
			return node->parent->right->left;
		else
			return node->parent->left->right;
	}

	Node* _getSibling( Node* node )
	{
		// if (isNil(node) || isNil(node->parent))
		// {
		// 	return _NIL;
		// }
		if (node->parent->right == node)
		{
			return node->parent->left;
		}
		return node->parent->right;

	}

/*************************************************/


/* PUBLIC FUNCTIONS */
public:

	Node* getRoot( )
	{
		return _root;
	}

	Node* insert( const Key & data )
	{
		Node* node = _createNode(data, true);

		// if tree is empty, new node becomes root
		if (isNil(_root) || _root == _end) 
		{
			_setRoot(node);
		}
		else
		{
			node = _insert(_root, node);
		}
		_updateSentinel();
		return node;
	}

	void deleteNode( const Key & data )
	{
		Node* node = findNode(_root, data);
		
		if (isNil(node))
			return;

		_delete(node);
		_updateSentinel();
	}

	Node* findNode(Node* root, const Key & data ) {
		if (isNil(root))
			return root;
		if (root->data == data)
			return root;
		if (compare(root->data, data))
			return findNode(root->right, data);
		else
			return findNode(root->left, data);
	}

	// TODO
	Node* inorderPre( Node* node )
	{
		if (isNil(node))
			return node;
		if (!isNil(node->left))
			return max(node->left);
		if (node == _sentinel->left)
			return _end;
		if (node == _end)
			return _sentinel->right;
		else
		{
			// While the node is a left child, keep going.
			while (!isNil(node->parent) && node == node->parent->left)
			{
				node = node->parent;
			}
			return node->parent;
		}
	}

	// TODO
	Node* inorderSucc( Node* node )
	{
		if (isNil(node))
			return node;
		if (!isNil(node->right))
			return min(node->right);
		if (node == _sentinel->right)
			return _end;
		else
		{
			// While the node is a right child, keep going.
			while (!isNil(node->parent) && node == node->parent->right)
			{
				node = node->parent;
			}
			return node->parent;
		}
	}

	bool isNil( const Node* node )
	{
		if (node == NULL || node == _NIL || node == _end)
			return true;
		return false;
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

	Node* begin()
	{
		return _sentinel->left;
	}

	Node* end()
	{
		return _end;
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

	void printTree()
	{
		for (int level = 0; level <= getHeight(_root, 0); level++)
		{
			printLevel(level);
			cout << endl;
		}
		cout << "___" << endl;
	}

	void printSuccessor( Key & data )
	{
		Node* node = findNode(_root, data);

		if (isNil(node))
		{
			cout << "Couldn't find node of data " << data << endl;
		}
		else
		{
			node = inorderSucc(node);
			if (node == _end)
			{
				cout << "Successor is the end" << endl;
			}
			else
			{
				cout << "Successor is node " << node->data << endl;
			}
		}
	}

	void printPredecessor( Key & data )
	{
		Node* node = findNode(_root, data);

		if (isNil(node))
		{
			cout << "Couldn't find node of data " << data << endl;
		}
		else
		{
			node = inorderPre(node);
			if (node == _end)
			{
				cout << "Predecessor is the end" << endl;
			}
			else
			{
				cout << "Predecessor is node " << node->data << endl;
			}
		}
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

	/*************************************************/
};

}
#endif
