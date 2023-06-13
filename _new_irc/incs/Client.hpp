/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:39:15 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 11:46:58 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

class Client
{
	private:
	// attributes
		std::string	username;
		std::string	nickname;
		std::string	password;

	// constructors & destructors
	public:
	// attributes

	//constructors & destructors
		Client();
		Client(Client const& src);
		virtual ~Client();

	// setters
		void	set_username(std::string const username);
		void	set_nickname(std::string const nickname);
		void	set_password(std::string const password);

	// getters
		std::string const&	get_username() const;
		std::string const&	get_nickname() const;
		std::string const&	get_password() const;

	// operator overload
		Client&	operator=(Client const& rhs);

	// member functions
};