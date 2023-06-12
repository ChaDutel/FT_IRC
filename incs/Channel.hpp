/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:53:33 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/12 13:02:41 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <sys/socket.h>

#include <textmods.h>
#include <Debug.hpp>
#include <Exceptions.hpp>

class	Client;

class	Channel
{
	private:
		std::map<int, Client>	operators; // only operators
		std::map<int, Client>	users; //operators and users
		bool					invite_only; //0 = join mode | 1 = invite only mode
		std::string				topic;
		std::string				name;
		int						user_limit; // -1 = no user limit

	public:
		Channel();
		Channel(int const creator_fd, Client const& creator, std::string const &name);
		virtual ~Channel();

		void				set_invite_only(bool mod);
		void				set_user_limit(int limit);
		void				set_topic(std::string const& topic);

		void				add_operator(int fd, Client const& client);
		void				add_user(int fd, Client const& client);
		void				kick_user(int fd);
		void				remove_operator(int fd);
		void				send_message(std::string const& message);

		bool				get_invite_only() const;
		std::string const&	get_topic() const;
		int					get_user_limit() const;
		std::string const&	get_name() const;

		bool				is_in_map(int fd, std::map<int, Client> clientmap) const;
};


/*
ToDo:
Forme canonique
*/
