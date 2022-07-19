/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <sfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:32:19 by sfournie          #+#    #+#             */
/*   Updated: 2022/07/19 15:12:00 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
#define TEST_HPP

#include <string>

#define BLACK	"\033[30m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"
#define RESET	"\033[0m"

using  std::string;

void	print_text(string text, bool nl = true);
string	title(string title, int level);
string	title_generate(string title, int level);

template<class T>
void print_container(T & cont, int type);

template<class FT_C, class STD_C>
void test_insert(FT_C ft_c, STD_C std_c);

void test_pair(void);

template<class T>
void ft_cout_endl(const T&  msg);

template<class I>
void print_it(I it);

void enter_prompt(void);

// PAIRS
void test_pair_equal(void);
void test_pair_compare(void);
// END PAIRS

#endif
