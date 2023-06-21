/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:37:07 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/20 16:29:46 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <Client.hpp>
#include <utils.hpp>
#include <Exceptions.hpp>

class Channel
{
	private:
	// attributes
		std::string	name;

		std::map<int, Client>	operators;
		std::map<int, Client>	clients;

	public:
	// constructors & destructors
		Channel();
		Channel(Channel const& src);
		virtual ~Channel();

	// setters
		void	set_name(std::string const name);

	// getters
		std::string const&				get_name() const;
		std::map<int, Client> const&	get_clients_map() const;
		std::map<int, Client> const&	get_operators_map() const;

	// operator overload
		Channel&	operator=(Channel const& rhs);

	// member functions
		void	send_message(std::string const& msg);

		void	add_operator(Client const& client);
		void	add_client(Client const& client);
		void	remove_operator(Client const& client);
		void	remove_client(Client const& client);
};