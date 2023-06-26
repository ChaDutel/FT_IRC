/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:18:32 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/26 18:50:39 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Bot.hpp>

Bot::Bot()
{
	
}

Bot::Bot(char const* port, char const* password)
{
	int	optval = 1;
	
}

Bot::Bot(Bot const& src)
{
	*this = src;
}

Bot::~Bot()
{
	
}

Bot&	Bot::operator=(Bot const& rhs)
{
	return (*this);
}

char const*	SigIntException::what()					const throw() {return ("SIGINT called, Bot stopped.");}
char const*	NotEnoughArgumentException::what()		const throw() {return ("ERROR: Usage is ./subwoofer_mk1 <server_port> <server_password>");}
char const*	InvalidArgumentException::what()		const throw() {return ("ERROR: Invalid argument specified");}
char const*	InvalidPortException::what()			const throw() {return ("ERROR: Invalid server port specified");}