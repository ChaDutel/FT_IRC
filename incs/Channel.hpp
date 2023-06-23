/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:37:07 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/23 16:03:44 by cdutel-l         ###   ########lyon.fr   */
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
		std::string pass;

		std::map<int, Client>	operators;
		std::map<int, Client>	clients;

	public:
	// constructors & destructors
		Channel();
		Channel(Channel const& src);
		virtual ~Channel();

	// setters
		void	set_name(std::string const name);
		void	set_pass(std::string const name);

	// getters
		std::string const&				get_name() const;
		std::string const&				get_pass() const;
		std::map<int, Client> const&	get_clients_map() const;
		std::map<int, Client> const&	get_operators_map() const;

	// operator overload
		Channel&	operator=(Channel const& rhs);

	// member functions
		void	send_message(std::string const& msg);
		bool	check_if_need_pass(Channel channel) const;
		bool	check_pass(std::string const& pass, Channel channel) const;

		void	add_operator(Client const& client);
		void	add_client(Client const& client);
		void	remove_operator(Client const& client);
		void	remove_client(Client const& client);
};
