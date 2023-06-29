/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:12 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/29 12:03:40 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

/* ************************************************************************** */
/* USER */
/* ************************************************************************** */
void	Server::cmd_user(std::string& client_msg, int const client_fd)
{
	std::vector<std::string>	split = split_str_to_vector(client_msg, ' ');

	if (split.size() < 2)
		throw WrongSyntaxException();
	if (check_syntax(split[1]) == -1)
		throw WrongSyntaxException();

	this->clients[client_fd].set_username(split[1]);
	this->clients[client_fd].set_auth(CLIENT_USER, true);
}

/* ************************************************************************** */
/* PASS */
/* ************************************************************************** */
void	Server::cmd_pass(std::string& client_msg, int const client_fd)
{
	std::string	chosen_password = client_msg.substr(5);

	if (chosen_password != this->password)
	{
		std::string	server_msg = "464 " + this->clients[client_fd].get_name() + " :Password incorrect\r\n";
		send(client_fd, server_msg.c_str(), server_msg.size(), 0);
		throw IncorrectServerPassException();
	}
	this->clients[client_fd].set_password(chosen_password);
	this->clients[client_fd].set_auth(CLIENT_PASS, true);
}

/* ************************************************************************** */
/* NICK */
/* ************************************************************************** */
void	Server::cmd_nick(std::string& client_msg, int const client_fd)
{
	std::vector<std::string>	split = split_str_to_vector(client_msg, ' ');
	if (split.size() != 2)
		throw WrongSyntaxException();
	int			validity = check_syntax(split[1]);

	if (validity == -1)
		throw WrongSyntaxException();
	else if (validity == 2)
		throw WrongNicknameException();
	else
	{
		std::string	server_msg;
		if (check_existence_ptr(split[1], this->clients))
		{
			server_msg = "433 " + this->clients[client_fd].get_name();
			server_msg += " " + split[1] + " : Nickname is already in use\r\n";
			send(client_fd, server_msg.c_str(), server_msg.size(), 0);
			throw NicknameTakenException();
		}
		if (this->clients[client_fd].is_authentified())
		{
			server_msg = ":" + this->clients[client_fd].get_name() + " NICK " + split[1] + "\r\n";
			send(client_fd, server_msg.c_str(), server_msg.size(), 0);
		}
		this->clients[client_fd].set_nickname(split[1]);
		this->clients[client_fd].set_auth(CLIENT_NICK, true);
	}
}

/* ************************************************************************** */
/* PING */
/* ************************************************************************** */
void	Server::cmd_ping(std::string& client_msg, int const client_fd)
{
	std::string	server_msg;

	server_msg = "PONG " + this->name + " : " + client_msg.substr(5) + "\r\n";
	send(client_fd, server_msg.c_str(), server_msg.size(), 0);
}

void	Server::command_handler(std::string client_msg, int client_fd)
{
	if (client_msg.empty())
		return ;
	std::string	server_msg;
	remove_last_char(client_msg);
	if (client_msg.substr(0, 4) == "QUIT")
		return (cmd_quit(client_fd));
	else if (this->clients[client_fd].is_authentified())
	{
		if (client_msg.substr(0, 4) == "NICK" && client_msg.size() > 4)
			cmd_nick(client_msg, client_fd);
		if (client_msg.substr(0, 4) == "PING" && client_msg.size() > 4)
			cmd_ping(client_msg, client_fd);
		if (client_msg.substr(0, 7) == "PRIVMSG" && client_msg.size() > 7)
			cmd_privmsg(client_msg, client_fd);
		if (client_msg.substr(0, 4) == "JOIN" && client_msg.size() > 4)
			cmd_join(client_msg, client_fd);
		if (client_msg.substr(0, 5) == "TOPIC" && client_msg.size() > 5)
			cmd_topic(client_msg, client_fd);
		if (client_msg.substr(0, 4) == "MODE" && client_msg.size() > 4)
			cmd_mode(client_msg, client_fd);
		if (client_msg.substr(0, 4) == "KICK" && client_msg.size() > 4)
			cmd_kick(client_msg, client_fd);
		if (client_msg.substr(0, 6) == "INVITE" && client_msg.size() > 6)
			cmd_invite(client_msg, client_fd);
	}
	else
	{
		if (client_msg.substr(0, 4) == "NICK" && client_msg.size() > 4)
			cmd_nick(client_msg, client_fd);
		else if (client_msg.substr(0, 4) == "PASS" && client_msg.size() > 4)
			cmd_pass(client_msg, client_fd);
		else if (client_msg.substr(0, 4) == "USER" && client_msg.size() > 4)
			cmd_user(client_msg, client_fd);
		if (this->clients[client_fd].is_authentified())
		{
			std::string	server_msg = ":" + this->name + " 001 " + this->clients[client_fd].get_name();
			server_msg += " :Welcome " + this->clients[client_fd].get_name() + " to the Internet Relay Network\r\n";
			send(client_fd, server_msg.c_str(), server_msg.size(), 0);
		}
	}
	this->clients[client_fd].clear_cmd(client_msg.size() + 2);
}
