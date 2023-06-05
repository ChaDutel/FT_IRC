/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:27 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/05 15:42:39 by ljohnson         ###   ########lyon.fr   */
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
