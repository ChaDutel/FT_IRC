/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:07:02 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/26 18:29:34 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Bot.hpp>

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
		signal(SIGINT, signal_handler);
	}
	signal(SIGINT, signal_handler);
	return (0);
}