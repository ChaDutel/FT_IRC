/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:51:41 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/06 11:20:31 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <map>

#include <textmods.h>
#include <Debug.hpp>
#include <Exceptions.hpp>

class	Client;
class	Channel;

class	Server
{
	private:
	// attributes
		std::map<int, Client>	users; // all users connected and authentified to the server
		std::map<int, Channel>	channels; // all channels on server
		std::string				password;

	// constructors & destructors
		Server();

	public:
	// attributes
		int						fd;
	
	// constructors & destructors
		Server(char const* port, std::string const password);
		virtual ~Server();

	// setters
		void	set_fd(char const* port);
		void	set_new_client(int id, Client client);
		void	set_new_channel(int id, Channel channel);

	// member functions
		void	handle_client_connections();
		void	authentification(fd_set &tmp_fdset, fd_set &default_fdset, int new_fd);
		// int	get_fd() const;
};


/*
ToDo:
Forme canonique
*/

/*
struct sockaddr
{
	unsigned short	sa_family;
	char			sa_data[14];
};

struct sockaddr_in
{
	short int			sin_family;
	unsigned short int	sin_port;
	struct in_addr		sin_addr;
	unsigned char		sin_zero[8];
};

struct in_addr
{
	unsigned long	s_addr;
};

typedef struct fd_set
{
	u_int	fd_count;
	SOCKET	fd_array[FD_SETSIZE];
} fd_set;
*/
