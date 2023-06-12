/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:52:54 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/12 13:04:05 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

#include <textmods.h>
#include <Debug.hpp>
#include <Exceptions.hpp>

class	Client
{
	private:
		bool		authentified;
		bool		auths[3];
		bool		quit;
		std::string	username;
		std::string	nickname;
		std::string	password_client;

	public:
		Client();
		virtual ~Client();

		bool				get_auth() const;
		bool				get_auths(int i) const;
		bool				get_quit() const;
		std::string	const&	get_username() const;
		std::string	const&	get_name() const;
		std::string	const&	get_password_client() const;

		void				set_auth(bool const auth);
		void				set_auths(int i);
		void				set_quit(bool const quit);
		void				set_username(std::string const username);
		void				set_nickname(std::string const nickname);
		void				set_password_client(std::string const password_client);
};

/*
ToDo:
Forme canonique
*/
