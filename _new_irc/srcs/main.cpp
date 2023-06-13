/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:03:21 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 11:09:30 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Channel.hpp>
#include <Client.hpp>

bool	is_digit(char c)		{return (c > '0' && c < '9');}
bool	is_alpha_min(char c)	{return (c > 'a' && c < 'z');}
bool	is_alpha_maj(char c)	{return (c > 'A' && c < 'Z');}
bool	is_alphanum(char c)		{return (is_digit(c) && is_alpha_min(c) && is_alpha_maj(c));}

void	signal_handler(int sig_id)
{
	(void)sig_id;
	throw SigIntException();
}

void	check_user_input(int ac, char** av)
{
	std::string	arg;

	if (ac != 3)
		throw NotEnoughArgumentException();
	arg = av[1];
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

		Server	server(av[1], av[2]);
		signal(SIGINT, signal_handler);
	}
	catch (std::exception& e) {std::cerr << e.what() << std::endl;}
	return (0);
}