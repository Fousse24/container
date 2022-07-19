/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:43:29 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/19 17:38:26 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>
#include <string>

using std::string;

template <class Key>
class rb_tree
{
private:
	struct node *root = NULL;
	
protected:
	struct node
	{
		char	color;
		Key		key;
		node	*right = NULL;
		node	*left = NULL;
		node	*parent = NULL;

		node() : color('r') {  };
		node(Key k) : key(k), color('r') {  };
	};

public:
	rb_tree();
	rb_tree( rb_tree const &obj );
	~rb_tree();

	void insert(node * l)
	{
		// YOU'RE HERE
		if (!l)
			return ;
		if (!root)
		{
			l->color = 'r';
			root = l;
		}
		else
		{
			if (l
		}
	}

};

#endif