/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:18:23 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/26 21:56:19 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>
#include <map>
#include <vector>
#include <sstream>
#include <cstring>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

// Colors
#define BLACK	"\033[30m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define PURPLE	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"

// Text
#define ERASE		"\033[2K\r"
#define RESET		"\033[0m"
#define BOLD		"\033[1m"
#define FAINT		"\033[2m"
#define ITALIC		"\033[3m"
#define UNDERLINE	"\033[4m"

#define DATA_BUFFER 1024

/* ************************************************************************** */
/* Class */
/* ************************************************************************** */
class Bot
{
	private:
		std::string					name;
		std::string					username;
		std::string					password;
		int							bot_fd;
		std::map<int, std::string>	clients;

		Bot();

	public:
		Bot(char const* port, char const* password);
		Bot(Bot const& src);
		virtual ~Bot();

		Bot&	operator=(Bot const& rhs);

		void	link_to_server();
		void	handle_msg(std::string const& msg);
};

/* ************************************************************************** */
/* Exceptions */
/* ************************************************************************** */
//Signal
class	SigIntException					: public std::exception {public: virtual char const*	what() const throw();};

//User input
class	UserInputException				: public std::exception {public: virtual char const*	what() const throw();};
class	NotEnoughArgumentException		: public UserInputException {public: virtual char const*	what() const throw();};
class	InvalidArgumentException		: public UserInputException {public: virtual char const*	what() const throw();};
class	InvalidPortException			: public UserInputException {public: virtual char const*	what() const throw();};

//System call
class	SystemCallException				: public std::exception {public: virtual char const*	what() const throw();};
class	SocketFailException				: public SystemCallException {public: virtual char const*	what() const throw();};
class	SetSockOptFailException			: public SystemCallException {public: virtual char const*	what() const throw();};
class	ConnectFailException			: public SystemCallException {public: virtual char const*	what() const throw();};
class	RecvFailException				: public SystemCallException {public: virtual char const*	what() const throw();};

//Client input
class	ClientInputException			: public std::exception {public: virtual char const*	what() const throw();};
class	MessageTooLongException			: public ClientInputException {public: virtual char const*	what() const throw();};
class	MessageNotFoundException		: public ClientInputException {public: virtual char const*	what() const throw();};

/* ************************************************************************** */
/* main.cpp */
/* ************************************************************************** */
std::vector<std::string>	split_str_to_vector(std::string const& str, char const delim);
bool	is_digit(char c);
bool	is_alpha_min(char c);
bool	is_alpha_maj(char c);
bool	is_alphanum(char c);
void	remove_last_char(std::string &message);
void	print_msg(std::string const& message);
void	print_msg(char const* style, char const* color, std::string const& message);
void	signal_handler(int sig_id);
void	check_user_input(int ac, char** av);

/* ************************************************************************** */
/* Bot.cpp */
/* ************************************************************************** */
std::string	woof_creator(unsigned int const size);
std::string	woof_translator(std::vector<std::string> const& msg);
#include <Bot.tpp>