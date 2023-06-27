/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:18:32 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/27 18:37:22 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Bot.hpp>

fd_set	default_fdset;
/* ************************************************************************** */
/* Constructors & Destructor */
/* ************************************************************************** */
//private
Bot::Bot() : name("subwoofer_mk1"), username("Woofer_the_first"), password("unknown_password"), bot_fd(-1)
{
	
}

//public
Bot::Bot(char const* port, char const* password) : name("subwoofer_mk1"), username("Woofer_the_first"), password(password)
{
	int					optval = 1;
	struct sockaddr_in	saddrin;

	this->bot_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->bot_fd == -1)
		throw SocketFailException();
	if (setsockopt(this->bot_fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) == -1)
		throw SetSockOptFailException();
	FD_ZERO(&default_fdset);
	FD_SET(this->bot_fd, &default_fdset);
	saddrin.sin_family = AF_INET;
	saddrin.sin_port = htons(std::strtol(port, NULL, 10));
	saddrin.sin_addr.s_addr = INADDR_ANY;
	if (connect(this->bot_fd, (struct sockaddr*)&saddrin, sizeof(sockaddr_in)) == -1)
		throw ConnectFailException();
}

//public
Bot::Bot(Bot const& src)
{
	*this = src;
}

//public
Bot::~Bot()
{
	if (this->bot_fd > 0)
		close(this->bot_fd);
	this->clients.clear();
}

/* ************************************************************************** */
/* Operator Overload */
/* ************************************************************************** */
Bot&	Bot::operator=(Bot const& rhs)
{
	this->name = rhs.name;
	this->username = rhs.username;
	this->password = rhs.password;
	this->bot_fd = rhs.bot_fd;
	return (*this);
}

/* ************************************************************************** */
/* Member functions */
/* ************************************************************************** */
std::string	woof_creator(unsigned int const size)
{
	std::string	woof = "W";

	for (unsigned int i = 1; i < (size - 1); i++)
		woof += "o";
	woof += "f ";
	return (woof);
}

std::string	woof_translator(std::vector<std::string> const& msg)
{
	std::string	final_msg;

	for (unsigned int i = 3; i < msg.size(); i++)
	{
		if (msg[i].empty())
			continue ;
		if (msg[i].size() > 2)
			final_msg += woof_creator(msg[i].size());
		else if (msg[i].size() == 2)
			final_msg += "WOOF ";
		else
			final_msg += "WUF ";
	}
	final_msg += "\r\n";
	return (final_msg);
}

void	Bot::handle_msg(std::string const& client_msg)
{
	std::vector<std::string>	msg = split_str_to_vector(client_msg, ' ');

	if (msg.size() < 4)
		throw MessageNotFoundException();
	std::string	client_nick = msg[0].substr(1, msg[0].find('!', 0) - 1);
	if (client_nick == "ircserv")
		return ;
	std::string	privmsg = "PRIVMSG " + client_nick + " ";
	std::string	final_msg = privmsg + woof_translator(msg);
	send(this->bot_fd, final_msg.c_str(), final_msg.size(), 0);
}

void	Bot::link_to_server()
{
	std::string	msg;

	msg = "NICK " + this->name + "\r\n";
	send(this->bot_fd, msg.c_str(), msg.size(), 0);
	usleep(1000);
	msg = "USER " + this->username + "\r\n";
	send(this->bot_fd, msg.c_str(), msg.size(), 0);
	usleep(1000);
	msg = "PASS " + this->password + "\r\n";
	send(this->bot_fd, msg.c_str(), msg.size(), 0);

	while (42)
	{
		char		buffer[DATA_BUFFER];
		std::memset(&buffer, '\0', DATA_BUFFER);
		int			bytes_recv = DATA_BUFFER;
		std::string	msg;
		try
		{
			while (bytes_recv == DATA_BUFFER)
			{
				bytes_recv = recv(this->bot_fd, buffer, DATA_BUFFER, 0);
				if (bytes_recv == 0)
					return ;
				else if (bytes_recv == -1)
					throw RecvFailException();
				msg += buffer;
			}
			if (msg.size() > DATA_BUFFER)
				throw MessageTooLongException();
			remove_last_char(msg);
			this->handle_msg(msg);
		}
		catch (ClientInputException& e) {print_msg(BOLD, YELLOW, e.what());}
	}
}

/* ************************************************************************** */
/* Exceptions */
/* ************************************************************************** */
//Signal
char const*	SigIntException::what()					const throw() {return ("SIGINT called, Bot stopped.");}

//User input
char const*	UserInputException::what()				const throw() {return ("ERROR: UserInputException placeholder");}
char const*	NotEnoughArgumentException::what()		const throw() {return ("ERROR: Usage is ./subwoofer_mk1 <server_port> <server_password>");}
char const*	InvalidArgumentException::what()		const throw() {return ("ERROR: Invalid argument specified");}
char const*	InvalidPortException::what()			const throw() {return ("ERROR: Invalid server port specified");}

//System call
char const*	SystemCallException::what()				const throw() {return ("ERROR: SystemCallException placeholder");}
char const*	SocketFailException::what()				const throw() {return ("ERROR: Socket Failed");}
char const*	SetSockOptFailException::what()			const throw() {return ("ERROR: SetSockOpt Failed");}
char const*	ConnectFailException::what()			const throw() {return ("ERROR: Connect Failed");}
char const*	RecvFailException::what()				const throw() {return ("ERROR: Recv Failed");}

//Client input
char const*	ClientInputException::what()			const throw() {return ("ERROR: ClientInputException placeholder");}
char const*	MessageTooLongException::what()			const throw() {return ("ERROR: Message received by bot is too long");}
char const*	MessageNotFoundException::what()		const throw() {return ("ERROR: Message not found in PRIVMSG");}

