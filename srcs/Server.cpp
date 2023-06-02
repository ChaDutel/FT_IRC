/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:13:13 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/02 12:26:03 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Client.hpp>
#include <Channel.hpp>

Server::Server()
{
	Debug::print_msg(FAINT, WHITE, "Server constructor called");
}

Server::~Server()
{
	Debug::print_msg(FAINT, WHITE, "Server destructor called");
	this->users.clear();
	this->channels.clear();
}

void	Server::set_new_client(int id, Client client)
{
	Debug::detail(FILE, LINE, FUNC);
	(void)id;
	(void)client;
}

void	Server::set_new_channel(int id, Channel channel)
{
	Debug::detail(FILE, LINE, FUNC);
	(void)id;
	(void)channel;
}