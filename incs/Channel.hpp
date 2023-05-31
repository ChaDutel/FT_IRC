/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:53:33 by ljohnson          #+#    #+#             */
/*   Updated: 2023/05/25 13:53:58 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <map>

class	Client;

class	Channel
{
	private:
		std::map<int, Client>	operators; // only operators
		std::map<int, Client>	users; //operators and users
		bool					invite_only; //0 = join mode | 1 = invite only mode
		std::string				topic;
		int						user_limit; // -1 = no user limit
};