/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:43:29 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/20 17:59:44 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>
#include <string>

using std::string;

namespace ft {

template <class Key>
class rb_tree
{
	struct node
	{
		bool	red;
		Key		key;
		node	*right;
		node	*left;
		node	*parent;

		node() : red(true) { init_node(); };
		node(bool color) : red(color) { init_node(); };
		node(Key k) : key(k), red(true) { init_node(); };
		node(Key k, bool color) : key(k), red(color) { init_node(); };

		void init_node()
		{
			right = NULL;
			left = NULL;
			parent = NULL;
		}
	};

public:
	rb_tree() : root(NULL) {  };
	rb_tree( rb_tree const &obj ) { root = obj.root(); }; // to be done
	~rb_tree() {  };

	node * getRoot() { return root; };

	void insert(Key key)
	{
		node	*n = new node(key);
		
		if (!n)
			return ;
		_insert_node(n);
	};

	void print_tree() {
    	_print_from(this->root, "", true);
    }

	void delete_node(const Key & k) // from n, find node with key value 'k' and delete it
	{
		node * n, * save1, * save2;
		bool red_save = false;

		n = _find_node(root, k);
		if (!n)
		{
			std::cerr << "Failed to find a node with a key value of " << k << std::endl;
			return ;
		}

		red_save = n->red;
		save2 = n;
		if (!n->left)
		{
			save1 = n->right;
			_transplant(n, n->right);
		}
		else if ( !n->right )
		{
			save1 = n->left;
			_transplant(n, n->left); 
		}
		else
		{
			save2 = _min(n->right);
			red_save = save2->red;
			save1 = save2->right;
			if (save2->parent == n)
				save1->parent = save2;
			else
			{
				_transplant(save2, save2->right);
				save2->right = n->right;
				save2->right->parent = save2;
			}
			_transplant(n, save2);
			save2->left = n->left;
			save2->left->parent = save2;
			save2->red = n->red;
		}
		
		delete n;
		if (!red_save)
			_delete_fix(save1);
	};

private:

	node * _min(node * node) 
	{
		while (node && node->left)
			node = node->left;
		return node;
	}

	void _transplant(node * dst, node * src) 
	{
		if ( !dst->parent )
			root = src;
		else if (dst == dst->parent->left)
			dst->parent->left = src;
		else
			dst->parent->right = src;
		src->parent = dst->parent;
	
	}
	void _fix_as_gp(node ** n, node ** gp)
	{
		(*gp)->red = true;
		(*gp)->right->red = false;
		(*gp)->left->red = false;
		*n = *gp;
	}

	void _left_rotate(node * n) 
	{
		node * right = n->right;

		n->right = right->left;
		if (right->left != NULL) {
			right->left->parent = n;
		}
		
		right->parent = n->parent;
		if (!n->parent)
		{
			this->root = right;
		} 
		else if (n == n->parent->left) 
		{
			n->parent->left = right;
		} 
		else 
		{
			n->parent->right = right;
		}
		
		right->left = n;
		n->parent = right;
	}

	void _right_rotate(node * n) 
	{
		node * left = n->left;

		n->left = left->right;
		if (left->right != NULL) {
			left->right->parent = n;
		}
		left->parent = n->parent;
		if (!n->parent)
		{
			this->root = left;
		} 
		else if (n == n->parent->right) 
		{
			n->parent->right = left;
		} 
		else 
		{
			n->parent->left = left;
		}
		left->right = n;
		n->parent = left;
	}

	node * _find_node(node * start, const Key & k) // return NULL if not found
	{
		while ( !start )
		{
			if (start->key == k)
				break;
			else if (k < start->key)
				start = start->left;
			else
				start = start->right;
		}
		return start;
	}

	void _insert_node(node * n)
	{
		node	*leaf;
		node	*prev_leaf = NULL;
		
		if (!n)
			return ;
			
		if (!root) //set node as root if there is no root
		{
			n->red = false;
			root = n;
		}
		else 
		{
			leaf = root;
			while (leaf) // traverse to the left or the right until NULL
			{
				prev_leaf = leaf;
				if (n->key > leaf->key)
					leaf = leaf->right;
				else
					leaf = leaf->left;
			}
			n->parent = prev_leaf;
			if (n->key > prev_leaf->key) // place as left or right child
				prev_leaf->right = n;
			else
				prev_leaf->left = n;
		}
		/*if (!n->parent->parent) 
		{
      		return;
    	}*/
		_insert_fix(n);
	};

	void _insert_fix(node * n)
	{
		node * iter;
		
		if (!n || !root)
			return ;
    	while (n->parent->red) 
		{
			n->parent->parent = n->parent->parent;
			if (n->parent->parent && n->parent == n->parent->parent->right) 
			{
				iter = n->parent->parent->left;
				if (iter->red) 
				{
					iter->red = false;
					n->parent->red = false;
					n->parent->parent->red = true;
					n = n->parent->parent;
				} 
				else 
				{
					if (n == n->parent->left) 
					{
						n = n->parent;
						_right_rotate(n);
					}
					n->parent->red = false;
					n->parent->parent->red = true;
					_left_rotate(n->parent->parent);
				}
			} 
			else 
			{
				iter = n->parent->right;
				if (iter->red) 
				{
					iter->red = false;
					n->parent->red = false;
					n->parent->parent->red = true;
					n = n->parent->parent;
				} 
				else 
				{
					if (n == n->parent->right) 
					{
						n = n->parent;
						_left_rotate(n);
					}
					n->parent->red = 0;
					n->parent->parent->red = 1;
					_right_rotate(n->parent->parent);
				}
			}
			if (n == root) 
			{
				break;
			}
    	}
	};

	void _delete_fix(node * n) 
	{
		node * save;
		
		while (n != root && n->red == 0) 
		{
			if (n == n->parent->left) 
			{
				save = n->parent->right;
				if (save->red == 1) 
				{
					save->red = 0;
					n->parent->red = 1;
					_left_rotate(n->parent);
					save = n->parent->right;
				}
				if (save->left->red == 0 && save->right->red == 0) 
				{
					save->red = 1;
					n = n->parent;
				} 
				else 
				{
					if (save->right->red == 0) 
					{
						save->left->red = 0;
						save->red = 1;
						_right_rotate(save);
						save = n->parent->right;
					}
					save->red = n->parent->red;
					n->parent->red = 0;
					save->right->red = 0;
					_left_rotate(n->parent);
					n = root;
				}
			} 
			else 
			{
				save = n->parent->left;
				if (save->red == 1) 
				{
					save->red = 0;
					n->parent->red = 1;
					_right_rotate(n->parent);
					save = n->parent->left;
				}

				if (save->right->red == 0 && save->right->red == 0) 
				{
					save->red = 1;
					n = n->parent;
				} 
				else 
				{
					if (save->left->red == 0) 
					{
						save->right->red = 0;
						save->red = 1;
						_left_rotate(save);
						save = n->parent->left;
					}
					save->red = n->parent->red;
					n->parent->red = 0;
					save->left->red = 0;
					_right_rotate(n->parent);
					n = root;
				}
			}
		}
    	n->red = 0;
	};

	void _print_from(node * root, string indent, bool last) 
	{
		if (!root)
			return ; 
		std::cout << indent;
		if (last) 
		{
			std::cout << "R----";
			indent += "   ";
		}
		else 
		{
			std::cout << "L----";
			indent += "|  ";
		}

		string sColor = root->red ? "RED" : "BLACK";
		std::cout << root->key << "(" << sColor << ")" << std::endl;
		_print_from(root->left, indent, false);
		_print_from(root->right, indent, true);
	};

	node *root;

};



};

#endif