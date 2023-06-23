/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:37:53 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/23 19:40:01 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Channel.hpp>

/* ************************************************************************** */
/* Constructors & Destructors */
/* ************************************************************************** */
// public
Channel::Channel() : name("unknown_channel_name"), pass("") {}

// public
Channel::Channel(Channel const& src) {*this = src;}

// public
Channel::~Channel()
{
	this->operators.clear();
	this->clients.clear();
}

/* ************************************************************************** */
/* Setters */
/* ************************************************************************** */
void	Channel::set_name(std::string const name) {this->name = name;}
void	Channel::set_pass(std::string const name) {this->name = name;}

/* ************************************************************************** */
/* Getters */
/* ************************************************************************** */
std::string const&				Channel::get_name() const {return (this->name);}
std::string const&				Channel::get_pass() const {return (this->name);}
std::map<int, Client> const&	Channel::get_clients_map() const {return (this->clients);}
std::map<int, Client> const&	Channel::get_operators_map() const {return (this->operators);}

/* ************************************************************************** */
/* Operator Overloads */
/* ************************************************************************** */
Channel&	Channel::operator=(Channel const& rhs)
{
	this->name = rhs.get_name();
	this->operators = rhs.get_operators_map();
	this->clients = rhs.get_clients_map();
	return (*this);
}

/* ************************************************************************** */
/* Member Functions */
/* ************************************************************************** */
void	Channel::send_message(std::string const& msg)
{
	std::map<int, Client>::const_iterator	it = this->clients.begin();

	while (it != this->clients.end())
	{
		send(it->first, msg.c_str(), msg.size(), 0);
		it++;
	}
}

bool	Channel::check_if_need_pass(Channel channel) const
{
	if (channel.get_pass() != "")
		return (true);
	else
		return (false);
}

bool	Channel::check_pass(std::string const& pass, Channel channel) const
{
	if (channel.get_pass() == pass)
		return (true);
	else
		return (false);
}

void	Channel::add_operator(Client const& client)		{add_client_to_map(client, this->operators);}
void	Channel::add_client(Client const& client)		{add_client_to_map(client, this->clients);}
void	Channel::remove_operator(Client const& client)	{remove_client_from_map(client, this->operators);}
void	Channel::remove_client(Client const& client)	{remove_client_from_map(client, this->clients);}
