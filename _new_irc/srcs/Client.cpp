/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:44:37 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 14:38:11 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>

/* ************************************************************************** */
/* Constructors & Destructors */
/* ************************************************************************** */
// public
Client::Client() : username("default_client_username"), nickname("default_client_nickname"), password("default_client_password") {}

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
			this->authentification[0] = auth; break;
		case 1:
			this->authentification[1] = auth; break;
		case 2:
			this->authentification[2] = auth; break;
		default:
			throw InvalidAuthenficationIdException(); break; //ToDo
	}
}

/* ************************************************************************** */
/* Getters */
/* ************************************************************************** */
std::string const&	Client::get_username() const				{return (this->username);}
std::string const&	Client::get_nickname() const				{return (this->nickname);}
std::string const&	Client::get_password() const				{return (this->password);}
int	const&			Client::get_client_fd() const				{return (this->client_fd);}
struct sockaddr_in const&	Client::get_client_addr_in() const	{return (this->client_addr_in);}
bool const&			Client::get_quit() const					{return (this->quit);}

bool const&			Client::get_auth(int const id) const
{
	switch (id)
	{
		case 0:
			return (this->authentification[0]);
		case 1:
			return (this->authentification[1]);
		case 2:
			return (this->authentification[2]);
		default:
			throw InvalidAuthenficationIdException(); return (false); //ToDo
	}
}

/* ************************************************************************** */
/* Operator Overloads */
/* ************************************************************************** */
Client&	Client::operator=(Client const& rhs)
{
	this->username = rhs.get_username();
	this->nickname = rhs.get_nickname();
	this->password = rhs.get_password();
	this->client_fd = rhs.get_client_fd();
	this->quit = rhs.get_quit();
	this->authentification[0] = rhs.get_auth(0);
	this->authentification[1] = rhs.get_auth(1);
	this->authentification[2] = rhs.get_auth(2);
}

/* ************************************************************************** */
/* Member Functions */
/* ************************************************************************** */
bool	Client::is_authentified() const {return (this->authentification[0] && this->authentification[1] && this->authentification[2]);}