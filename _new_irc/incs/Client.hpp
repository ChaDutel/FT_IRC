/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:39:15 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/20 15:15:51 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Client
{
	private:
	// attributes
		std::string	username;
		std::string	nickname;
		std::string	password;
		int			client_fd;
		bool		auth[3]; //0 = username, 1 = nickname, 2 = password

	public:
	//constructors & destructors
		Client();
		Client(Client const& src);
		virtual ~Client();

	// setters
		void	set_username(std::string const username);
		void	set_nickname(std::string const nickname);
		void	set_password(std::string const password);
		void	set_client_fd(int const fd);
		void	set_auth(int const id, bool const auth);

	// getters
		std::string const&			get_username() const;
		std::string const&			get_name() const;
		std::string const&			get_password() const;
		int	const&					get_client_fd() const;
		bool const&					get_auth(int const id) const;

	// operator overload
		Client&	operator=(Client const& rhs);

	// member functions
		bool	is_authentified() const;
};