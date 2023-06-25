/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:22:14 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/25 16:45:09 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// C++ includes
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <vector>
#include <cerrno>
#include <cstring>

// C includes
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

// custom includes
#include <defines.hpp>
#include <utils.hpp>
#include <Exceptions.hpp>

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

		std::map<int, Client>			clients; // all users connected and authentified fd/class
		std::map<std::string, Channel>	channels; // all channels created on server name/class

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
		std::string const&						get_name() const;
		std::string const&						get_password() const;
		int	const&								get_server_fd() const;
		std::map<int, Client> const&			get_client_map() const;
		std::map<std::string, Channel> const&	get_channel_map() const;

	// operator overload
		Server&	operator=(Server const& rhs);

	// member functions
		// Server.cpp
		void		recv_loop();
		void		accept_handler();
		void		client_handler();
		Channel*	find_channel(std::string const& name, std::map<std::string, Channel> channels);

		// command_handler.cpp
		void	command_handler(std::string client_msg, int client_fd);

		//commands
		void	cmd_quit(int const client_fd);
		void	cmd_nick(std::string& client_msg, int const client_fd);
		void	cmd_pass(std::string& client_msg, int const client_fd);
		void	cmd_user(std::string& client_msg, int const client_fd);
		void	cmd_ping(std::string& client_msg, int const client_fd);
		void	cmd_join(std::string& client_msg, int const client_fd);
		void	cmd_topic(std::string& client_msg, int const client_fd);
		void	cmd_mode(std::string& client_msg, int const client_fd);
		void	cmd_kick(std::string& client_msg, int const client_fd);

		void	privmsg_client_handler(std::string const& client_name, int const client_fd, std::vector<std::string> const& msg);
		void	privmsg_channel_handler(std::string const& channel_name, int const client_fd, std::vector<std::string> const& msg);
		void	cmd_privmsg(std::string& client_msg, int const client_fd);
};

#include <Server.tpp>
