/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:37:53 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/20 16:34:29 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Channel.hpp>

/* ************************************************************************** */
/* Constructors & Destructors */
/* ************************************************************************** */
// public
Channel::Channel() : name("unknown_channel_name") {}

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

/* ************************************************************************** */
/* Getters */
/* ************************************************************************** */
std::string const&				Channel::get_name() const {return (this->name);}
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

void	Channel::add_operator(Client const& client)		{add_client_to_map(client, this->operators);}
void	Channel::add_client(Client const& client)		{add_client_to_map(client, this->clients);}
void	Channel::remove_operator(Client const& client)	{remove_client_from_map(client, this->operators);}
void	Channel::remove_client(Client const& client)	{remove_client_from_map(client, this->clients);}