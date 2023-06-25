/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:37:07 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/25 17:49:30 by cdutel-l         ###   ########lyon.fr   */
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
		std::string	topic;

		std::map<int, Client const*>	operators;
		std::map<int, Client const*>	clients;

		bool	invite_only;
		bool	topic_rights;
		bool	need_pass;
		int		user_limit; //1 = no user limit, > 1 user limit

	public:
	// constructors & destructors
		Channel();
		Channel(Channel const& src);
		virtual ~Channel();

	// setters
		void	set_name(std::string const name);
		void	set_pass(std::string const pass);
		void	set_topic(std::string const topic);
		void	set_invite_only(bool const set);
		void	set_topic_rights(bool const set);
		void	set_need_pass(bool const set);
		void	set_user_limit(int const limit);

	// getters
		std::string const&				get_name() const;
		std::string const&				get_pass() const;
		std::string const&				get_topic() const;
		std::map<int, Client const*> const&	get_clients_map() const;
		std::map<int, Client const*> const&	get_operators_map() const;
		bool const&						get_invite_only() const;
		bool const&						get_topic_rights() const;
		bool const&						get_need_pass() const;
		int const&						get_user_limit() const;

	// operator overload
		Channel&	operator=(Channel const& rhs);

	// member functions
		void		send_message(std::string const& msg, int const client_fd) const;
		bool		check_pass(std::string const& pass) const;
		std::string	list_clients() const;
		void		send_namreply(std::string const& chan_name, Client const& sender);
		void		kick_client(Client const& client, std::vector<std::string> const& vec_msg, Client const& target);

		void	add_operator(Client const& client);
		void	add_client(Client const& client);
		void	remove_operator(Client const& client);
		void	remove_client(Client const& client);
};
