/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:22:14 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 13:42:38 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// C++ includes
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <cerrno>

// C includes
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

// custom includes
#include <defines.hpp>
#include <utils.hpp>

// declarations
class	Client;
class	Channel;

class	Server
{
	private:
	// attributes
		std::string				name; // server name
		std::string				password; // password given as av[2]
		int						server_fd; // server fd

		std::map<int, Client>	clients; // all users connected and authentified
		std::map<int, Channel>	channels; // all channels created on server

		struct sockaddr_in		server_addr_in;
		fd_set					default_fdset;

	// constructors & destructors
		Server();

	public:
	// attributes

	//constructors & destructors
		Server(char const* port, std::string const password);
		Server(Server const& src);
		virtual ~Server();
	
	// setters
		void	set_name(std::string const name);
		void	set_password(std::string const password);

	// getters
		std::string const&				get_name() const;
		std::string const&				get_password() const;
		int	const&						get_server_fd() const;
		std::map<int, Client> const&	get_client_map() const;
		std::map<int, Channel> const&	get_channel_map() const;
		struct sockaddr_in const&		get_server_addr_in() const;

	// operator overload
		Server&	operator=(Server const& rhs);

	// member functions
		void	recv_loop(fd_set& tmp_fdset);
		void	accept_handler(fd_set& tmp_fdset);
		void	client_handler();
};

#include <Server.tpp>

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

struct sigaction
{
	void		(*sa_handler)(int);
	void		(*sa_sigaction)(int, siginfo_t *, void *);
	sigset_t	sa_mask;
	int			sa_flags;
	void		(*sa_restorer)(void);
};
*/
