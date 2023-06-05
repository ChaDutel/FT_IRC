/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:13:13 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/05 16:39:11 by ljohnson         ###   ########lyon.fr   */
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

void	Server::handle_client_connections()
{
	fd_set	default_fdset;
	struct	sockaddr_in	new_addr;

	FD_ZERO(&default_fdset);
	FD_SET(this->fd, &default_fdset);

	while (42)
	{
		fd_set	tmp_fdset = default_fdset;

		for (std::map<int, Client>::iterator it = this->users.begin(); it != this->users.end(); it++)
		{
			if (it->first >= 0)
				FD_SET(it->first, &tmp_fdset);
		}
		if (select(FD_SETSIZE, &tmp_fdset, NULL, NULL, NULL) >= 0)
		{
			if (FD_ISSET(this->fd, &tmp_fdset))
			{
				socklen_t	addrlen = sizeof(new_addr);
				int new_fd = accept(this->fd, (struct sockaddr *)&new_addr, &addrlen);
				if (new_fd >= 0)
				{
					Client	tmp;
					// verif existence, close fd, map.erase()
					this->users[new_fd] = tmp;
					FD_SET(new_fd, &tmp_fdset);
					// authentification
				}
				else //accept fail
				{
					//ToDo : Close clients & channels FD
					close(this->fd);
					FD_CLR(this->fd, &default_fdset);
					throw AcceptFailException();
				}
			}
			else
			{
				//Server quit with connected client | signal ?
				//ToDo: Close clients & channels FD
				close(this->fd);
				FD_CLR(this->fd, &default_fdset);
				throw ServerClosedException();
			}

			for (std::map<int, Client>::iterator it = this->users.begin(); it != this->users.end(); it++)
			{
				if (FD_ISSET(it->first, &tmp_fdset))
				{
					//recv
					char	buffer[DATA_BUFFER];
					int		bytes_recv = recv(it->first, buffer, DATA_BUFFER, 0);
					if (bytes_recv > 0)
					{
						std::cout << "Received buffer: " << buffer << std::endl;
						std::string	message(buffer, bytes_recv); //check when DATA_BUFFER is reached
						std::cout << "Received message: " << message << std::endl;
					}
					else
					{
						std::cout << "Client disconnected" << std::endl;
						close(it->first);
						FD_CLR(it->first, &tmp_fdset);
						this->users.erase(it->first);
					}
				}
			}
		}
		else //Select Fail
		{
			//ToDo: Close clients & channels FD
			close(this->fd);
			FD_CLR(this->fd, &default_fdset);
			throw SelectFailException();
		}
	}
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
	saddrin.sin_family = AF_INET;
	saddrin.sin_port = htons(std::strtol(port, NULL, 10));
	saddrin.sin_addr.s_addr = INADDR_ANY;

	if (bind(fd, (struct sockaddr *)&saddrin, sizeof(struct sockaddr_in)) == -1)
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