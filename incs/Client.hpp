/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:52:54 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/06 11:13:28 by cdutel-l         ###   ########lyon.fr   */
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
		std::string	username;
		std::string	nickname;

	public:
		Client();
		virtual ~Client();

		bool				get_auth() const;
		std::string	const&	get_username() const;
		std::string	const&	get_nickname() const;
		void				set_username(std::string const username);
		void				set_nickname(std::string const nickname);
};

/*
ToDo:
Forme canonique
*/
