/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:07:02 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/26 21:17:18 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Bot.hpp>

std::vector<std::string>	split_str_to_vector(std::string const& str, char const delim)
{
	std::vector<std::string>	split;
	std::istringstream			iss(str);
	std::string					tmp;

	while (std::getline(iss, tmp, delim))
	{
		if (!tmp.empty())
			split.push_back(tmp);
	}
	return (split);
}

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


void	print_msg(std::string const& message)
{
	std::cout << message << std::endl;
}

void	print_msg(char const* style, char const* color, std::string const& message)
{
	std::cout << style << color;
	std::cout << message;
	std::cout << RESET << std::endl;
}

void	signal_handler(int sig_id)
{
	(void)sig_id;
	throw SigIntException();
}

void	check_user_input(int ac, char** av)
{
	if (ac != 3)
		throw NotEnoughArgumentException();
	std::string arg = av[1];
	if (arg.empty() || arg[0] == ' ')
		throw InvalidArgumentException();
	for (unsigned int i = 0; arg[i]; i++)
	{
		if (!is_digit(arg[i]))
			throw InvalidPortException();
	}
	arg = av[2];
	if (arg.empty() || arg[0] == ' ')
		throw InvalidArgumentException();
}


int	main(int ac, char** av)
{
	try
	{
		check_user_input(ac, av);

		Bot	bot(av[1], av[2]);
		bot.link_to_server();
		signal(SIGINT, signal_handler);
	}
	catch (std::exception& e) {print_msg(BOLD, RED, e.what());}
	return (0);
}