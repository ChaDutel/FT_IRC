/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:30:29 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 11:08:35 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Channel.hpp>
#include <Client.hpp>

/* ************************************************************************** */
/* Constructors & Destructors */
/* ************************************************************************** */
// private
Server::Server() : name("default_server_name"), password("default_server_password"), server_fd(-1) {}

// public
Server::Server(chat const* port, std::string const password) : name("ircserv"), password(password)
{
	int	optval = 1;

	this->server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->server_fd == -1)
		throw SocketFailException();
	if (set_sockopt(this->server_fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) == -1)
		throw SetSockOptFailException();
	this->server_addr_in.sin_family = AF_INET;
	this->server_addr_in.sin_port = htons(std::strtol(port, NULL, 10));
	this->server_addr_in.sin_addr.s_addr = INADDR_ANY;

	if (bind(this->server_fd, (struct sockaddr*)&(this->server_addr_in), sizeof(struct sockaddr_in)) == -1)
		throw BindFailException();
	if (listen(this->server_fd, SOMAXCONN) == -1)
		throw ListenFailException();
}

// public
Server::Server(Server const& src)
{
	*this = src;
}

// public
Server::~Server()
{
	this->clients.clear();
	this->channels.clear();
	close(this->server_fd);
	FD_CLR(this->server_fd, &(this->default_fdset));
}

/* ************************************************************************** */
/* Setters */
/* ************************************************************************** */
void	Server::set_name(std::string const name) {this->name = name;}
void	Server::set_password(std::string const password) {this->password = password;}

/* ************************************************************************** */
/* Getters */
/* ************************************************************************** */
std::string const&				Server::get_name() const			{return (this->name);}
std::string const&				Server::get_password() const		{return (this->password);}
int	const&						Server::get_server_fd() const		{return (this->server_fd);}
std::map<int, Client> const&	Server::get_client_map() const		{return (this->clients);}
std::map<int, Channel> const&	Server::get_channel_map() const		{return (this->channels);}
struct sockaddr_in const&		Server::get_server_addr_in() const	{return (this->server_addr_in);}

/* ************************************************************************** */
/* Operator Overloads */
/* ************************************************************************** */
Server&	Server::operator=(Server const& rhs)
{
	this->name = rhs.get_name();
	this->password = rhs.get_password();
	this->server_fd = rhs.get_server_fd();
	this->clients = rhs.get_client_map();
	this->channels = rhs.get_channel_map();
	this->server_addr_in = rhs.get_server_addr_in();
}


/* ************************************************************************** */
/* Member Functions */
/* ************************************************************************** */