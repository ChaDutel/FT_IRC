/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:51:41 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/02 12:34:36 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <map>

#include <textmods.h>
#include <Debug.hpp>

#define PORT (attention aux cas particuliers)
#define PASSWORD

class	Client;
class	Channel;

class	Server
{
	private:
		std::map<int, Client>	users; // all users connected and authentified to the server
		std::map<int, Channel>	channels; // all channels on server

	public:
		Server();
		virtual ~Server();

		void	set_new_client(int id, Client client);
		void	set_new_channel(int id, Channel channel);
};