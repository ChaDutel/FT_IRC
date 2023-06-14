/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:44:37 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/14 13:46:49 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>
#include <Exceptions.hpp>

/* ************************************************************************** */
/* Constructors & Destructors */
/* ************************************************************************** */
// public
Client::Client() : username("unknown_username"), nickname("unknown_nickname"), password("unknown_password") {}

// public
Client::Client(Client const& src) {*this = src;}

// public
Client::~Client()
{
	close (this->client_fd);
}

/* ************************************************************************** */
/* Setters */
/* ************************************************************************** */
void	Client::set_username(std::string const username)		{this->username = username;}
void	Client::set_nickname(std::string const nickname)		{this->nickname = nickname;}
void	Client::set_password(std::string const password)		{this->password = password;}
void	Client::set_client_fd(int const fd)						{this->client_fd = fd;}
void	Client::set_client_addr_in(struct sockaddr_in saddr_in)	{this->client_addr_in = saddr_in;}
void	Client::set_quit(bool const quit) {this->quit = quit;}

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
std::string const&	Client::get_username() const				{return (this->username);}
std::string const&	Client::get_name() const				{return (this->nickname);}
std::string const&	Client::get_password() const				{return (this->password);}
int	const&			Client::get_client_fd() const				{return (this->client_fd);}
struct sockaddr_in const&	Client::get_client_addr_in() const	{return (this->client_addr_in);}
bool const&			Client::get_quit() const					{return (this->quit);}

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
	this->quit = rhs.get_quit();
	this->auth[0] = rhs.get_auth(0);
	this->auth[1] = rhs.get_auth(1);
	this->auth[2] = rhs.get_auth(2);
	return (*this);
}

/* ************************************************************************** */
/* Member Functions */
/* ************************************************************************** */
bool	Client::is_authentified() const {return (this->auth[0] && this->auth[1] && this->auth[2]);}