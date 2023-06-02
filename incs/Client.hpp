/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:52:54 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/02 16:37:59 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

#include <textmods.h>
#include <Debug.hpp>
#include <exceptions.hpp>

class	Client
{
	private:
		bool		authentified;
		std::string	username;
		std::string	nickname;

	public:
		Client();
		virtual ~Client();

		bool			get_auth() const;
		std::string&	get_username() const;
		std::string&	get_nickname() const;
};