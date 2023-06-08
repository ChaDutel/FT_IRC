/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:13:13 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/08 16:25:37 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Client.hpp>
#include <Channel.hpp>
#include <cerrno>
#include <string.h>

#define DATA_BUFFER 50

//----------------------------------------------------------------- BUILDERS -----------------------------------------------------------------//

Server::Server()
{
	Debug::print_msg(FAINT, WHITE, " Default Server constructor called");
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


//----------------------------------------------------------------- FUNCTIONS -----------------------------------------------------------------//

void handle_ping(int client, const std::string& message)
{
	std::cout << "shoudl have send pong\n";

	std::string msg = "PONG ircserv :" + message + "\r\n";
	send(client, msg.c_str(), msg.size(), 0);
}

void Server::authentification(int new_fd, std::string& message)
{
	if (message.substr(0, 4) == "NICK")
	{
		this->users[new_fd].set_nickname(message.substr(5));
		std::cout << "the nick is: '"<< this->users[new_fd].get_nickname() << "'" << std::endl;///////////
		this->users[new_fd].set_auths(0);
	}
	else if (message.substr(0, 4) == "PASS")
	{
		this->users[new_fd].set_password_client(message.substr(5));
		std::cout << "the client password is: '"<< this->users[new_fd].get_password_client() << "'" << std::endl;//////////////
		if (this->users[new_fd].get_password_client() != this->password)
		{
			std::string	err;
			std::cout << "Client Password incorrect, please change your password" << std::endl;
			if (this->users[new_fd].get_auths(0) == false)
				err = "464 unknown_user :Password incorrect\r\n";
			else
				err = "464 " + this->users[new_fd].get_nickname() + " :Password incorrect\r\n";
			send(new_fd, err.c_str(), err.size(), 0);
		}
		else
			this->users[new_fd].set_auths(1);
	}
	else if (message.substr(0, 4) == "USER")
	{
		this->users[new_fd].set_username(message.substr(5));
		std::cout << "the username is: '"<< this->users[new_fd].get_username() << "'" << std::endl;/////////////
		if (this->users[new_fd].get_auths(0) == true && this->users[new_fd].get_auths(1))
		{
			std::string	ret = ":irc.project.com 001 " + this->users[new_fd].get_nickname() + " :Welcome " + this->users[new_fd].get_nickname() + " to the Internet Relay Network!\r\n";
			send(new_fd, ret.c_str(), ret.size(), 0);
			this->users[new_fd].set_auths(2);
		}
	}
	if (this->users[new_fd].get_auths(0) == true && this->users[new_fd].get_auths(1) && this->users[new_fd].get_auths(2))
		this->users[new_fd].set_auth(true);
}

void	Server::find_command(std::string message, int fd)
{
	if (message.substr(0, 4) == "QUIT")
	{	
		this->users[fd].set_quit(true);
		std::cout << "QUIT understand" << std::endl;
	}
	else if (this->users[fd].get_auth() == false)
		authentification(fd, message);
	else
	{
		if (message.substr(0, 4) == "PING")
		{
			std::string pongMessage = message.substr(5);
			handle_ping(fd, pongMessage);
		}
		else if (message.substr(0, 4) == "NICK")
		{
			this->users[fd].set_nickname(message.substr(5));
			std::cout << "The new nickname is: '"<< this->users[fd].get_nickname() << "'" << std::endl;///////////
		}
		else
			std::cout << "Received message: " << message << std::endl;////////////////
	}
}

static void	remove_last_char(std::string &message)
{
	if ((message[message.length() - 1]) == '\n')
		message.erase(message.length() - 1, message.length());
	if ((message[message.length() - 1]) == '\r')
		message.erase(message.length() - 1, message.length());
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
					Client client;
					// verif existence, close fd, map.erase()
					this->users[new_fd] = client;
					FD_SET(new_fd, &tmp_fdset);
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
					if (bytes_recv > 0 && this->users[it->first].get_quit() == false)
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
