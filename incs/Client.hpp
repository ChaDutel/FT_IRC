/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:52:54 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/05 15:42:46 by ljohnson         ###   ########lyon.fr   */
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
};

/*
ToDo:
Forme canonique
*/