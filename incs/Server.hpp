/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:51:41 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/02 16:42:18 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/select.h>
#include <map>

#include <textmods.h>
#include <Debug.hpp>
#include <exceptions.hpp>

class	Client;
class	Channel;

class	Server
{
	private:
	// attributes
		std::map<int, Client>	users; // all users connected and authentified to the server
		std::map<int, Channel>	channels; // all channels on server

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

		// int	get_fd() const;
};