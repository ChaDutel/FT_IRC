/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:44:37 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/28 16:52:39 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>
#include <Exceptions.hpp>
#include <defines.hpp>
#include <utils.hpp>

/* ************************************************************************** */
/* Constructors & Destructors */
/* ************************************************************************** */
// public
Client::Client() : username("unknown_username"), nickname("unknown_nickname"), password("unknown_password"), client_fd(-1), end_msg(false)
{
	this->auth[0] = false;
	this->auth[1] = false;
	this->auth[2] = false;
}

// public
Client::Client(Client const& src) {*this = src;}

// public
Client::~Client() {}

/* ************************************************************************** */
/* Setters */
/* ************************************************************************** */
void	Client::set_msg(std::string const msg)					{this->msg += msg;}
void	Client::set_username(std::string const username)		{this->username = username;}
void	Client::set_nickname(std::string const nickname)		{this->nickname = nickname;}
void	Client::set_password(std::string const password)		{this->password = password;}
void	Client::set_client_fd(int const fd)						{this->client_fd = fd;}
void	Client::set_end_msg(bool const end_msg)					{this->end_msg = end_msg;}

void	Client::set_auth(int const id, bool const auth)
{
	switch (id)
	{
		case 0:
			this->auth[0] = auth; break;
		case 1:
			this->auth[1] = auth; break;
		case 2:
			this->auth[2] = auth; break;
		default:
			throw InvalidAuthIdException(); break;
	}
}


/* ************************************************************************** */
/* Getters */
/* ************************************************************************** */
std::string const&	Client::get_msg() const				{return (this->msg);}
std::string const&	Client::get_username() const		{return (this->username);}
std::string const&	Client::get_name() const			{return (this->nickname);}
std::string const&	Client::get_password() const		{return (this->password);}
int	const&			Client::get_client_fd() const		{return (this->client_fd);}
bool const&			Client::get_end_msg() const			{return (this->end_msg);}

bool const&			Client::get_auth(int const id) const
{
	switch (id)
	{
		case 0:
			return (this->auth[0]);
		case 1:
			return (this->auth[1]);
		case 2:
			return (this->auth[2]);
		default:
			throw InvalidAuthIdException();
	}
}

/* ************************************************************************** */
/* Operator Overloads */
/* ************************************************************************** */
Client&	Client::operator=(Client const& rhs)
{
	this->username = rhs.get_username();
	this->nickname = rhs.get_name();
	this->password = rhs.get_password();
	this->client_fd = rhs.get_client_fd();
	this->auth[0] = rhs.get_auth(0);
	this->auth[1] = rhs.get_auth(1);
	this->auth[2] = rhs.get_auth(2);
	this->end_msg = rhs.get_end_msg();
	return (*this);
}

/* ************************************************************************** */
/* Member Functions */
/* ************************************************************************** */
bool	Client::is_authentified() const {return (this->auth[0] && this->auth[1] && this->auth[2]);}
void	Client::clear_buffer() {this->msg.clear();}

void	Client::clear_cmd(int const size)
{
	if (!msg.empty())
		this->msg.erase(0, size);
}
