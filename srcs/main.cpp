/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:09:38 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/09 16:40:05 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>
#include <Channel.hpp>
#include <Server.hpp>
#include <csignal>

void	signalHandler(int sig_id)
{
	(void)sig_id;
	throw SigIntException();
}

bool	is_full_numeric(std::string const& arg)
{
	for (size_t i = 0; i < arg.size(); i++)
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (false);
	}
	return (true);
}

void	check_user_input(int ac, char** av)
{
	if (ac != 3)
		throw NotEnoughArgumentException();
	for (int i = 1; i < 3; i++)
	{
		std::string	arg = av[i];

		if (arg.empty() || arg[0] == ' ')
			throw InvalidArgumentException();
		if (i == 1 && !is_full_numeric(arg))
			throw InvalidPortException();
	}
}

int	main(int ac, char** av)
{
	Debug::start(4);
	try
	{
		check_user_input(ac, av);

		Server	server(av[1], av[2]);
		signal(SIGINT, signalHandler);
		server.handle_client_connections();

	}
	catch (std::exception& e) {std::cerr << e.what() << std::endl;}

	return (0);
}
