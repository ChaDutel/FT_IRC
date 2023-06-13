/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:30:29 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 15:44:02 by ljohnson         ###   ########lyon.fr   */
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
Server::Server(char const* port, std::string const password) : name("ircserv"), password(password)
{
	int	optval = 1;

	this->server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->server_fd == -1)
		throw SocketFailException();
	if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) == -1)
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
	close(this->server_fd);
	FD_CLR(this->server_fd, &(this->default_fdset));
	this->clients.clear();
	this->channels.clear();
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
	return (*this);
}

/* ************************************************************************** */
/* Member Functions */
/* ************************************************************************** */
void	Server::recv_loop(fd_set& tmp_fdset)
{
	for (std::map<int, Client>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
	{
		if (FD_ISSET(it->first, &tmp_fdset))
		{
			char	buffer[DATA_BUFFER]; // cette initialisation est pas ouf
			int		bytes_recv = recv(it->first, buffer, DATA_BUFFER, 0);
			if (bytes_recv > 0)
			{
				std::string	msg(buffer, bytes_recv);
				remove_last_char(msg);
				command_handler(msg, it->first);
				if (this->clients[it->first].get_quit())
				{
					std::cout << "Client " << this->clients[it->first].get_nickname() << " disconnected" << std::endl;
					FD_CLR(it->first, &tmp_fdset);
					this->clients.erase(it->first);
					return ;
				}
			}
			else if (bytes_recv == 0)
			{
				//end of file return by recv -> which case ??
				//was client disconnected before, still need it ?
				std::cout << "bytes_recv == 0" << std::endl;
			}
			else
				throw RecvFailException();
		}
	}
}

void	Server::accept_handler(fd_set& tmp_fdset)
{
	if (FD_ISSET(this->server_fd, &tmp_fdset))
	{
		struct sockaddr_in	tmp_addr_in;
		socklen_t	addrlen = sizeof(tmp_addr_in);
		int	new_fd = accept(this->server_fd, (struct sockaddr*)&(tmp_addr_in), &addrlen);

		if (new_fd >= 0)
		{
			Client	tmp_client;

			tmp_client.set_client_fd(new_fd);
			tmp_client.set_client_addr_in(tmp_addr_in);
			tmp_client.set_quit(false);
			this->clients[new_fd] = tmp_client;
			FD_SET(new_fd, &tmp_fdset);
		}
		else
			throw AcceptFailException();
	}
}

void	Server::client_handler()
{
	FD_ZERO(&(this->default_fdset));
	FD_SET(this->server_fd, &(this->default_fdset));

	while (42)
	{
		fd_set	tmp_fdset = this->default_fdset;

		for (std::map<int, Client>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
		{
			if (it->first >= 0)
				FD_SET(it->first, &tmp_fdset);
		}
		if (select(FD_SETSIZE, &tmp_fdset, NULL, NULL, NULL) >= 0)
		{
			accept_handler(tmp_fdset);
			recv_loop(tmp_fdset);
		}
		else
			throw SelectFailException();
	}
}

/*
notes:
Actuellement, les vérifications de fd de client et serveur ne se font qu'avec FD_ISSET dans la fonction handle_client_connections
cependant, même si nous vérifions si le fd existe, nous ne vérifions pas si celui-ci est encore ouvert et valide.
Cela peut mener à des erreurs lors des connexions et déconnexion, comme un client en remplaçant un autre avec son fd, ou une déconnexion non voulue du client ou du serveur.
*/