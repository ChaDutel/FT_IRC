/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:27 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/06 11:14:03 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>

Client::Client() : authentified(false)
{
	Debug::print_msg(FAINT, WHITE, "Client constructor called");
}

Client::~Client()
{
	Debug::print_msg(FAINT, WHITE, "Client destructor called");
}

bool				Client::get_auth() const {return (this->authentified);}
std::string const&	Client::get_username() const {return (this->username);}
std::string const&	Client::get_nickname() const {return (this->nickname);}
void				Client::set_username(std::string const username) {this->username = username;}
void				Client::set_nickname(std::string const nickname) {this->nickname = nickname;}
