/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:52:54 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/02 12:34:30 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

#include <textmods.h>
#include <Debug.hpp>

class	Client
{
	private:
		bool		authentified;
		std::string	username;
		std::string	nickname;

	public:
		Client();
		virtual ~Client();
};