/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:26:33 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/12 16:46:10 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Channel.hpp>
#include <Client.hpp>

Channel::Channel() : invite_only(false), user_limit(-1), name("no_name_channel")
{
	Debug::print_msg(FAINT, WHITE, "Channel constructor called");
}

Channel::Channel(int const creator_fd, Client const& creator, std::string const &name) : invite_only(false), user_limit(-1), name(name)
{
	Debug::print_msg(FAINT, WHITE, "Channel creator constructor called");
	this->add_operator(creator_fd, creator);
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

bool							Channel::get_invite_only() const {return (this->invite_only);}
std::string const&				Channel::get_topic() const {return (this->topic);}
int								Channel::get_user_limit() const {return (this->user_limit);}
std::string const&				Channel::get_name() const {return (this->name);}
std::map<int, Client> const&	Channel::get_user_map() const {return (this->users);}
std::map<int, Client> const&	Channel::get_operator_map() const {return (this->operators);}

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
	if (this->user_limit != -1 && static_cast<int>(this->users.size()) == this->user_limit)
		throw UserLimitReachedException();
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
