/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:18:23 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/26 18:50:01 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <exception>
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

/* ************************************************************************** */
/* Class */
/* ************************************************************************** */
class Bot
{
	private:
	
	public:
		Bot();
		Bot(char const* port, char const* password);
		Bot(Bot const& src);
		virtual ~Bot();

		Bot&	operator=(Bot const& rhs);
};

/* ************************************************************************** */
/* Exceptions */
/* ************************************************************************** */
class	SigIntException					: public std::exception {public: virtual char const*	what() const throw();};
class	NotEnoughArgumentException		: public std::exception {public: virtual char const*	what() const throw();};
class	InvalidArgumentException		: public std::exception {public: virtual char const*	what() const throw();};
class	InvalidPortException			: public std::exception {public: virtual char const*	what() const throw();};

/* ************************************************************************** */
/* main.cpp */
/* ************************************************************************** */
void	signal_handler(int sig_id);
void	check_user_input(int ac, char** av);

/* ************************************************************************** */
/* Bot.cpp */
/* ************************************************************************** */
void	print_msg(std::string const& message);
void	print_msg(char const* style, char const* color, std::string const& message);
#include <Bot.tpp>