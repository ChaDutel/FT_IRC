/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:33:27 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/08 16:02:01 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>

Client::Client() : authentified(false), quit(false)
{
	for(int i = 0; i < 3; i++)
		auths[i] = false;
	Debug::print_msg(FAINT, WHITE, "Client constructor called");
}

Client::~Client()
{
	Debug::print_msg(FAINT, WHITE, "Client destructor called");
}

bool				Client::get_auth() const {return (this->authentified);}
bool				Client::get_auths(int i) const {return (this->auths[i]);}
bool				Client::get_quit() const {return (this->quit);}
std::string const&	Client::get_username() const {return (this->username);}
std::string const&	Client::get_nickname() const {return (this->nickname);}
std::string const&	Client::get_password_client() const {return (this->password_client);}

void				Client::set_auth(bool const auth) {this->authentified = auth;}
void				Client::set_auths(int i) {this->auths[i] = true;}
void				Client::set_quit(bool const quit) {this->quit = quit;}
void				Client::set_username(std::string const username) {this->username = username;}
void				Client::set_nickname(std::string const nickname) {this->nickname = nickname;}
void				Client::set_password_client(std::string const password_client) {this->password_client = password_client;}
