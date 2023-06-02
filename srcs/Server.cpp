/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:13:13 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/02 17:49:53 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Client.hpp>
#include <Channel.hpp>

Server::Server()
{
	Debug::print_msg(FAINT, WHITE, " Default Server constructor called");
}

void	Server::handle_client_connections()
{
	fd_set	fdset;
	
}

/* ************************************************************************** */
/* Initialization */
/* ************************************************************************** */
void	Server::set_fd(char const* port)
{
	struct sockaddr_in	saddrin;
	int					optval = 0;

	this->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->fd == -1)
		throw SocketFailException();
	if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) == -1)
		throw SetSockOptFailException();
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(std::strtol(port, NULL, 10));
	saddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(fd, (struct sockaddr *)&saddrin, sizeof(struct sockaddr_in)) == -1)
		throw BindFailException();
	if (listen(fd, SOMAXCONN) == -1)
		throw ListenFailException();
}

Server::Server(char const* port, std::string const password)
{
	Debug::print_msg(FAINT, WHITE, "Server constructor called");
	set_fd(port);
}
/* ************************************************************************** */

Server::~Server()
{
	Debug::print_msg(FAINT, WHITE, "Server destructor called");
	this->users.clear();
	this->channels.clear();
	close(this->fd);
}

/* ************************************************************************** */
/* Getters & Setters */
/* ************************************************************************** */
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