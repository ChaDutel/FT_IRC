/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:37:53 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/28 12:17:57 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Channel.hpp>

/* ************************************************************************** */
/* Constructors & Destructors */
/* ************************************************************************** */
// public
Channel::Channel() : name("unknown_channel_name"), pass("unknown_channel_pass"), topic("undefined_topic")
{
	this->invite_only = false;
	this->topic_rights = true;
	this->need_pass = false;
	this->user_limit = -1;
}

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
void	Channel::set_pass(std::string const pass) {this->pass = pass;}
void	Channel::set_topic(std::string const topic) {this->topic = topic;}
void	Channel::set_invite_only(bool const set) {this->invite_only = set;}
void	Channel::set_topic_rights(bool const set) {this->topic_rights = set;}
void	Channel::set_need_pass(bool const set) {this->need_pass = set;}
void	Channel::set_user_limit(int const limit) {this->user_limit = limit;}

/* ************************************************************************** */
/* Getters */
/* ************************************************************************** */
std::string const&					Channel::get_name() const {return (this->name);}
std::string const&					Channel::get_pass() const {return (this->pass);}
std::string const&					Channel::get_topic() const {return (this->topic);}
std::map<int, Client const*> const&	Channel::get_clients_map() const {return (this->clients);}
std::map<int, Client const*> const&	Channel::get_operators_map() const {return (this->operators);}
std::vector<std::string> const&		Channel::get_invitations() const {return (this->invitations);}
bool const&							Channel::get_invite_only() const {return (this->invite_only);}
bool const&							Channel::get_topic_rights() const {return (this->topic_rights);}
bool const&							Channel::get_need_pass() const {return (this->need_pass);}
int const&							Channel::get_user_limit() const {return (this->user_limit);}
int									Channel::get_nb_clients() const {return (this->clients.size());}
int									Channel::get_nb_invitations() const {return (this->invitations.size());}

/* ************************************************************************** */
/* Operator Overloads */
/* ************************************************************************** */
Channel&	Channel::operator=(Channel const& rhs)
{
	this->name = rhs.get_name();
	this->operators = rhs.get_operators_map();
	this->clients = rhs.get_clients_map();
	this->pass = rhs.get_pass();
	this->topic = rhs.get_topic();
	this->invitations = rhs.get_invitations();
	this->invite_only = rhs.get_invite_only();
	this->topic_rights = rhs.get_topic_rights();
	this->need_pass = rhs.get_need_pass();
	this->user_limit = rhs.get_user_limit();
	return (*this);
}

/* ************************************************************************** */
/* Member Functions */
/* ************************************************************************** */
void	Channel::send_message(std::string const& msg, int const client_fd) const
{
	std::map<int, Client const*>::const_iterator	it = this->clients.begin();

	while (it != this->clients.end())
	{
		if (it->first != client_fd)
			send(it->first, msg.c_str(), msg.size(), 0);
		it++;
	}
}

bool	Channel::check_pass(std::string const& pass) const	{return (this->pass == pass);}

std::string	Channel::list_clients() const
{
	std::map<int, Client const*>::const_iterator	it = this->clients.begin();
	std::string	str;

	while (it != this->clients.end())
	{
		str += "@" + it->second->get_name();
		it++;
		if (it != this->clients.end())
			str += " ";
	}
	return (str);
}

void	Channel::add_operator(Client const& client)		{add_client_to_map(client, this->operators);}
void	Channel::add_client(Client const& client)		{add_client_to_map(client, this->clients);}
void	Channel::remove_operator(Client const& client)	{remove_client_from_map(client, this->operators);}
void	Channel::remove_client(Client const& client)	{remove_client_from_map(client, this->clients);}
void	Channel::add_invitation(std::string const name) {this->invitations.push_back(name);}

void	Channel::remove_invitation(std::string const name)
{
	for (std::vector<std::string>::iterator it = this->invitations.begin(); it != this->invitations.end(); it++)
	{
		if (name == *it)
		{
			this->invitations.erase(it);
			break ;
		}
	}
}

void	Channel::send_namreply(std::string const& chan_name, Client const& sender)
{
	std::string	tmp = chan_name;
	std::string	server_msg;

	tmp.erase(0, 1);
	for (std::map<int, Client const*>::const_iterator it = this->clients.begin(); it != this->clients.end(); it++)
	{
		server_msg = "353 " + sender.get_name() + " = " + tmp + " :" + sender.get_name() + "{ " + it->second->get_name() + "}\r\n";
		send(sender.get_client_fd(), server_msg.c_str(), server_msg.size(), 0);
	}
}

bool	Channel::is_invited(std::string const& target_name)
{
	for (unsigned int i = 0; i < this->invitations.size(); i++)
	{
		if (this->invitations[i] == target_name)
			return (true);
	}
	return (false);
}
