/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:30:29 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/26 12:55:36 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Channel.hpp>
#include <Client.hpp>
fd_set	default_fdset;
fd_set	exec_fdset;

/* ************************************************************************** */
/* Constructors & Destructors */
/* ************************************************************************** */
// private
Server::Server() : name("default_server_name"), password("default_server_password"), server_fd(-1) {}

// public
Server::Server(char const* port, std::string const password) : name("ircserv"), password(password)
{
	struct sockaddr_in	server_addr_in;
	int	optval = 1;

	this->server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->server_fd == -1)
		throw SocketFailException();
	if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) == -1)
		throw SetSockOptFailException();
	server_addr_in.sin_family = AF_INET;
	server_addr_in.sin_port = htons(std::strtol(port, NULL, 10));
	server_addr_in.sin_addr.s_addr = INADDR_ANY;

	if (bind(this->server_fd, (struct sockaddr*)&server_addr_in, sizeof(struct sockaddr_in)) == -1)
		throw BindFailException();
	if (listen(this->server_fd, SOMAXCONN) == -1)
		throw ListenFailException();
}

// public
Server::Server(Server const& src) {*this = src;}

// public
Server::~Server()
{
	close(this->server_fd);
	FD_CLR(this->server_fd, &(default_fdset));
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
std::string const&						Server::get_name() const			{return (this->name);}
std::string const&						Server::get_password() const		{return (this->password);}
int	const&								Server::get_server_fd() const		{return (this->server_fd);}
std::map<int, Client> const&			Server::get_client_map() const		{return (this->clients);}
std::map<std::string, Channel> const&	Server::get_channel_map() const		{return (this->channels);}

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
	return (*this);
}

/* ************************************************************************** */
/* QUIT */
/* ************************************************************************** */
void	Server::cmd_quit(int const client_fd)
{
	std::string	server_msg;

	for (std::map<std::string, Channel>::iterator it = this->channels.begin(); it != this->channels.end(); it++)
	{
		if (check_existence(this->clients[client_fd].get_name(), it->second.get_operators_map()))
			it->second.remove_operator(this->clients[client_fd]);
		if (check_existence(this->clients[client_fd].get_name(), it->second.get_clients_map()))
			it->second.remove_client(this->clients[client_fd]);
	}
	server_msg = ":" + this->clients[client_fd].get_name() + "!" + this->clients[client_fd].get_username();
	server_msg += "@" + this->name + " QUIT :" + this->clients[client_fd].get_name() + " has disconnected\r\n";
	send(client_fd, server_msg.c_str(), server_msg.size(), 0);
	std::cout << "Client " << this->clients[client_fd].get_name() << " disconnected" << std::endl;
	FD_CLR(client_fd, &(default_fdset));
	this->clients.erase(client_fd);
	throw ClientHasQuitException();
}

/* ************************************************************************** */
/* Member Functions */
/* ************************************************************************** */
void	Server::recv_loop()
{
	for (std::map<int, Client>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
	{
		if (FD_ISSET(it->first, &(exec_fdset)))
		{
			char    	buffer[DATA_BUFFER];
			std::memset(&buffer, '\0', DATA_BUFFER);
			int			bytes_recv = DATA_BUFFER;
			std::string	msg;
			while (bytes_recv == DATA_BUFFER)
			{
				bytes_recv = recv(it->first, buffer, DATA_BUFFER, 0);
				if (bytes_recv == 0)
					return (cmd_quit(it->first));
				else if (bytes_recv == -1)
					throw RecvFailException();
				msg += buffer;
			}
			if (msg.size() > DATA_BUFFER)
				throw MessageToLongException();
			remove_last_char(msg);
			try {command_handler(msg, it->first);}
			catch (ClientInputException& e) {print_msg(BOLD, YELLOW, e.what()); return ;}
		}
	}
}

void	Server::accept_handler()
{
	if (FD_ISSET(this->server_fd, &(exec_fdset)))
	{
		struct sockaddr_in	tmp_addr_in;
		socklen_t	addrlen = sizeof(tmp_addr_in);
		int	new_fd = accept(this->server_fd, (struct sockaddr*)&(tmp_addr_in), &addrlen);
		if (new_fd >= 0)
		{
			Client	tmp_client;

			this->clients.insert(std::pair<int, Client>(new_fd, tmp_client));
			this->clients[new_fd].set_client_fd(new_fd);
			FD_SET(new_fd, &(default_fdset));
		}
		else
			throw AcceptFailException();
	}
}

void	Server::client_handler()
{
	FD_ZERO(&(default_fdset));
	FD_SET(this->server_fd, &(default_fdset));

	while (42)
	{
		exec_fdset = default_fdset;

		if (select(FD_SETSIZE, &(exec_fdset), NULL, NULL, NULL) >= 0)
		{
			accept_handler();
			try {recv_loop();}
			catch (std::exception& e) {print_msg(BOLD, YELLOW, e.what());}
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
