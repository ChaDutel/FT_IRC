/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:26:33 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/09 15:11:06 by ljohnson         ###   ########lyon.fr   */
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

void				Channel::set_invite_only(bool mod) {this->invite_only = mod;}
void				Channel::set_user_limit(int limit) {this->user_limit = limit;}
void				Channel::set_topic(std::string const& topic) {this->topic = topic;}

bool				Channel::get_invite_only() const {return (this->invite_only);}
std::string const&	Channel::get_topic() const {return (this->topic);}
int					Channel::get_user_limit() const {return (this->user_limit);}

void	Channel::add_operator(int fd, Client const& client)
{
	if (this->is_in_map(fd, this->operators))
		throw UserAlreadyOperatorException();
	this->operators[fd] = client;
	this->add_user(fd, client);
}

void	Channel::add_user(int fd, Client const& client)
{
	if (this->is_in_map(fd, this->users))
		throw UserAlreadyInChannelException();
	this->users[fd] = client;
}

void	Channel::kick_user(int fd)
{
	if (this->is_in_map(fd, this->users))
	{
		if (this->is_in_map(fd, this->operators))
			throw CannotKickOperatorException();
		this->users.erase(fd);
	}
}

void	Channel::remove_operator(int fd)
{
	if (this->is_in_map(fd, this->operators))
		this->operators.erase(fd);
	else
		throw UserIsNotOperatorException();
}

bool	Channel::is_in_map(int fd, std::map<int, Client> clientmap) const
{
	for (std::map<int, Client>::iterator it = clientmap.begin(); it != clientmap.end(); it++)
	{
		if (fd == it->first)
			return (true);
	}
	return (false);
}

void	Channel::send_message(std::string const& message)
{
	for (std::map<int, Client>::iterator it = this->users.begin(); it != this->users.end(); it++)
		send(it->first, message.c_str(), message.size(), 0);
}