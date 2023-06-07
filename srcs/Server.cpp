/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:13:13 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/07 12:08:00 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Client.hpp>
#include <Channel.hpp>
#include <cerrno>
#include <string.h>

#define DATA_BUFFER 50

Server::Server()
{
	Debug::print_msg(FAINT, WHITE, " Default Server constructor called");
}

void Server::handlePing(int client, const std::string& message)
{
	std::cout << "shoudl have send pong\n";

	std::string msg = "PONG ircserv :" + message + "\r\n";
	send(client, msg.c_str(), msg.size(), 0);
}

void	Server::find_command(std::string message, int fd)
{
	if (message.substr(0, 4) == "PING")
	{
		std::string pongMessage = message.substr(5);
		handlePing(fd, pongMessage);
	}
	else
		std::cout << "Received message: " << message << std::endl;
}

static void	remove_last_char(std::string &message)
{
	if ((message[message.length() - 1]) == '\n')
		message.erase(message.length() - 1, message.length());
	if ((message[message.length() - 1]) == '\r')
		message.erase(message.length() - 1, message.length());
}

void Server::authentification(fd_set &tmp_fdset, int new_fd)
{
	Client client;
	// verif existence, close fd, map.erase()
	this->users[new_fd] = client;
	FD_SET(new_fd, &tmp_fdset);
	

	for (int i = 0; i < 3; i++)
	{
		char	buffer[DATA_BUFFER];
		int		bytes_recv = recv(new_fd, buffer, DATA_BUFFER, 0);
		if (bytes_recv > 0)
		{
			std::string	message(buffer, bytes_recv);
			remove_last_char(message);
			std::cout << "line is : " <<  message << std::endl;
			if (message.substr(0, 4) == "NICK")
			{
				client.set_nickname(message.substr(5));
				std::cout << "the nick is: '"<< client.get_nickname() << "'" << std::endl;
			}
			else if (message.substr(0, 4) == "USER")
			{
				client.set_username(message.substr(5));
				std::cout << "the username is: '"<< client.get_username() << "'" << std::endl;
				std::string	ret = ":irc.project.com 001 " + client.get_nickname() + " :Welcome " + client.get_nickname() + " to the Internet Relay Network!\r\n";
				send(new_fd, ret.c_str(), ret.size(), 0);
			}
		}
	}
}

void	Server::handle_client_connections()
{
	FD_ZERO(&(this->default_fdset));
	FD_SET(this->fd, &(this->default_fdset));

	while (42)
	{
		fd_set	tmp_fdset = this->default_fdset;

		for (std::map<int, Client>::iterator it = this->users.begin(); it != this->users.end(); it++)
		{
			if (it->first >= 0)
				FD_SET(it->first, &tmp_fdset);
		}
		if (select(FD_SETSIZE, &tmp_fdset, NULL, NULL, NULL) >= 0)
		{
			if (FD_ISSET(this->fd, &tmp_fdset))
			{
				socklen_t	addrlen = sizeof(this->new_addr);
				int new_fd = accept(this->fd, (struct sockaddr *)&(this->new_addr), &addrlen);
				if (new_fd >= 0)
				{
					authentification(tmp_fdset, new_fd);
				}
				else //accept fail
				{
					//ToDo : Close clients & channels FD
					throw AcceptFailException();
				}
			}
			// else                                           //better without
			// {
			// 	//Server quit with connected client | signal ?
			// 	//ToDo: Close clients & channels FD
			// 	throw ServerClosedException();
			// }

			for (std::map<int, Client>::iterator it = this->users.begin(); it != this->users.end(); it++)
			{
				if (FD_ISSET(it->first, &tmp_fdset))
				{
					//recv
					char	buffer[DATA_BUFFER];
					int		bytes_recv = recv(it->first, buffer, DATA_BUFFER, 0);
					if (bytes_recv > 0)
					{
						std::string	message(buffer, bytes_recv);
						remove_last_char(message);
						find_command(message, it->first);
					}
					else
					{
						std::cout << "Client disconnected" << std::endl;
						close(it->first);
						FD_CLR(it->first, &tmp_fdset);
						this->users.erase(it->first);
						break;
					}
				}
			}
		}
		else //Select Fail
		{
			//ToDo: Close clients & channels FD
			throw SelectFailException();
		}
	}
}

/* ************************************************************************** */
/* Initialization */
/* ************************************************************************** */
void	Server::set_fd(char const* port)
{
	int					optval = 1;

	this->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->fd == -1)
		throw SocketFailException();
	if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval)) == -1)
		throw SetSockOptFailException();
	this->saddrin.sin_family = AF_INET;
	this->saddrin.sin_port = htons(std::strtol(port, NULL, 10));
	this->saddrin.sin_addr.s_addr = INADDR_ANY;

	if (bind(fd, (struct sockaddr *)&(this->saddrin), sizeof(struct sockaddr_in)) == -1)
		throw BindFailException();
	if (listen(fd, SOMAXCONN) == -1)
		throw ListenFailException();
}

Server::Server(char const* port, std::string const password) : password(password)
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
	FD_CLR(this->fd, &(this->default_fdset));
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
