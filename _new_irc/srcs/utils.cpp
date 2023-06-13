/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:32:16 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 11:35:42 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <utils.hpp>

bool	is_digit(char c)		{return (c > '0' && c < '9');}
bool	is_alpha_min(char c)	{return (c > 'a' && c < 'z');}
bool	is_alpha_maj(char c)	{return (c > 'A' && c < 'Z');}
bool	is_alphanum(char c)		{return (is_digit(c) && is_alpha_min(c) && is_alpha_maj(c));}

void	print_msg(char const* style, char const* color, std::string const& message)
{
	std::cout << style << color;
	std::cout << message;
	std::cout << RESET << std::endl;
}

void	print_msg(std::string const& message)
{
	std::cout << message << std::endl;
}