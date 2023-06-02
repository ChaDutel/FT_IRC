/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:53:33 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/02 15:54:18 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <map>

#include <textmods.h>
#include <Debug.hpp>
#include <exceptions.hpp>

class	Client;

class	Channel
{
	private:
		std::map<int, Client>	operators; // only operators
		std::map<int, Client>	users; //operators and users
		bool					invite_only; //0 = join mode | 1 = invite only mode
		std::string				topic;
		int						user_limit; // -1 = no user limit

	public:
		Channel();
		virtual ~Channel();

		void			set_invite_only(bool mod);
		void			set_user_limit(int limit);
		void			set_topic(std::string const& topic);

		bool			get_invite_only() const;
		std::string&	get_topic() const;
		int				get_user_limit() const;
};