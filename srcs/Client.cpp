/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:27 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/02 17:41:48 by ljohnson         ###   ########lyon.fr   */
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

bool			Client::get_auth() const {return (this->authentified);}
std::string&	Client::get_username() const {return (this->username);}
std::string&	Client::get_nickname() const {return (this->nickname);}
