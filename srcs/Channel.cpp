/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:26:33 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/02 12:32:08 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Channel.hpp>
#include <Client.hpp>

Channel::Channel() : invite_only(false), user_limit(-1)
{
	Debug::print_msg(FAINT, WHITE, "Channel constructor called");
}

Channel::~Channel()
{
	Debug::print_msg(FAINT, WHITE, "Channel destructor called");
	this->operators.clear();
	this->users.clear();
}

void			Channel::set_invite_only(bool mod) {this->invite_only = mod;}
void			Channel::set_user_limit(int limit) {this->user_limit = limit;}
void			Channel::set_topic(std::string const& topic) {this->topic = topic;}

bool			Channel::get_invite_only() const {return (this->invite_only);}
std::string&	Channel::get_topic() const {return (this->topic);}
int				Channel::get_user_limit() const {return (this->user_limit);}