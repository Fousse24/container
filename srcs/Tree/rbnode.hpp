 
#pragma once
#ifndef RBNODE_HPP
#define RBNODE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>


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

template <class Key, class Allocator = std::allocator<Key> >
class RBNode {

	typedef Allocator	allocator_type;

private:
	allocator_type	_alloc;
public:
	Key data;
	RBNode* left;
	RBNode* right;
	RBNode* parent;
	RBNode* sentinel;
	bool red;

	RBNode()
	{
		_alloc.construct(&data);
		left = NULL;
		right = NULL;
		parent = NULL;
		sentinel = NULL;
		red = true;
	}

	RBNode(const Key & data): data(data)
	{
		// this->data = data;
		left = NULL;
		right = NULL;
		parent = NULL;
		sentinel = NULL;
		red = true;
	}

	~RBNode()
	{
		_alloc.destroy(&data);
	}
};
};

#endif