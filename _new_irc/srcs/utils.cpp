/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:32:16 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/16 16:14:07 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <utils.hpp>

bool	is_digit(char c)		{return (c >= '0' && c <= '9');}
bool	is_alpha_min(char c)	{return (c >= 'a' && c <= 'z');}
bool	is_alpha_maj(char c)	{return (c >= 'A' && c <= 'Z');}
bool	is_alphanum(char c)		{return (is_digit(c) || is_alpha_min(c) || is_alpha_maj(c));}

void	remove_last_char(std::string &message)
{
	if ((message[message.length() - 1]) == '\n')
		message.erase(message.length() - 1, message.length());
	if ((message[message.length() - 1]) == '\r')
		message.erase(message.length() - 1, message.length());
}

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

// if bool = true -> check #
// return -1 if wrong syntax
// return 1 if client
// return 2 if # as first char
int	check_syntax(std::string const& str)
{
	bool	hashtag = false;

	for (int i = 0; str[i]; i++)
	{
		if (i == 0 && str[i] == '#')
		{
			hashtag = true;
			continue ;
		}
		if (!is_alphanum(str[i]) && str[i] != '-' && str[i] != '_')
			return (-1);
	}
	if (hashtag)
		return (2);
	return (1);
}