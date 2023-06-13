/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:44:37 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 11:49:49 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>

Client::Client() : username("default_client_username"), nickname("default_client_nickname"), password("default_client_password") {}

Client::Client(Client const& src) {*this = src;}

Client::~Client() {}

Client&	Client::operator=(Client const& rhs)
{
	this->username = rhs.get_username();
	this->nickname = rhs.get_nickname();
	this->password = rhs.get_password();
}

void	Client::set_username(std::string const username) {this->username = username;}
void	Client::set_nickname(std::string const nickname) {this->nickname = nickname;}
void	Client::set_password(std::string const password) {this->password = password;}

std::string const&	Client::get_username() const {return (this->username);}
std::string const&	Client::get_nickname() const {return (this->nickname);}
std::string const&	Client::get_password() const {return (this->password);}