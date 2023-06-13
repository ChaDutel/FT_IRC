/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:03:21 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 15:40:50 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Channel.hpp>
#include <Client.hpp>
#include <utils.hpp>

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
		server.client_handler();
	}
	catch (std::exception& e) {print_msg(BOLD, RED, e.what());}
	return (0);
}