/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:32:19 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/11 16:25:00 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
#define TEST_HPP

#include <string>

using  std::string;

void	print_text(string text, bool nl = true);
string	title_generate(string title, int level);

template<class T>
void print_container(T & cont, int type);

template<class FT_C, class STD_C>
void test_insert(FT_C ft_c, STD_C std_c);

template<class T>
void ft_cout_endl(const T&  msg);

template<class I>
void print_it(I it);

void enter_prompt(void);

#endif
