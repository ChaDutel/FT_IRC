/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:12 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/22 18:43:51 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Channel.hpp>
#include <Client.hpp>

/* ************************************************************************** */
/* USER */
/* ************************************************************************** */
void	Server::cmd_user(std::string& client_msg, int const client_fd)
{
	print_msg(BOLD, BLUE, client_msg);
	std::string	chosen_username = client_msg.substr(5);

	this->clients[client_fd].set_username(chosen_username);
	this->clients[client_fd].set_auth(CLIENT_USER, true);
}

/* ************************************************************************** */
/* PASS */
/* ************************************************************************** */
void	Server::cmd_pass(std::string& client_msg, int const client_fd)
{
	print_msg(BOLD, BLUE, client_msg);
	std::string	chosen_password = client_msg.substr(5);

	if (chosen_password != this->password)
	{
		std::string	server_msg = "464 " + this->clients[client_fd].get_name() + " :Password incorrect\r\n";
		send(client_fd, server_msg.c_str(), server_msg.size(), 0);
		throw IncorrectPassException();
	}
	this->clients[client_fd].set_password(chosen_password);
	this->clients[client_fd].set_auth(CLIENT_PASS, true);
}

/* ************************************************************************** */
/* NICK */
/* ************************************************************************** */
void	Server::cmd_nick(std::string& client_msg, int const client_fd)
{
	print_msg(BOLD, BLUE, client_msg);
	std::string	chosen_nickname = client_msg.substr(5);
	int			validity = check_syntax(chosen_nickname);

	if (validity == -1)
		throw WrongSyntaxException();
	else if (validity == 2)
		throw WrongNicknameException();
	else
	{
		if (check_existence<int, Client>(chosen_nickname, this->clients))
		{
			std::string	server_msg = "433 " + this->clients[client_fd].get_name();
			server_msg += " " + chosen_nickname + " : Nickname is already in use\r\n";
			send(client_fd, server_msg.c_str(), server_msg.size(), 0);
			throw NicknameTakenException();
		}
		this->clients[client_fd].set_nickname(chosen_nickname);
		this->clients[client_fd].set_auth(CLIENT_NICK, true);
	}
}

/* ************************************************************************** */
/* QUIT */
/* ************************************************************************** */
void	Server::cmd_quit(int const client_fd)
{
	std::string	server_msg;

	server_msg = ":" + this->clients[client_fd].get_name() + "!" + this->clients[client_fd].get_username();
	server_msg += "@" + this->name + " QUIT :" + this->clients[client_fd].get_name() + " has disconnected\r\n";
	send(client_fd, server_msg.c_str(), server_msg.size(), 0);
	std::cout << "Client " << this->clients[client_fd].get_name() << " disconnected" << std::endl;
	FD_CLR(client_fd, &(this->default_fdset));
	this->clients.erase(client_fd);
	throw ClientHasQuitException();
}

/* ************************************************************************** */
/* JOIN */
/* ************************************************************************** */
void	Server::cmd_join(std::string& client_msg, int const client_fd)
{
	print_msg(BOLD, BLUE, client_msg);
	std::vector<std::string>	msg = split_str_to_vector(client_msg, ' ');
	if (msg.size() < 2)
	{
		// send NotEnoughParam to sender
		throw NotEnoughParamException(); //ToDo
	}
	std::vector<std::string>	channels = split_str_to_vector(msg[1], ',');
	std::vector<std::string>	pass;
	if (msg.size() == 3)
		pass = split_str_to_vector(msg[2], ',');
	else
	{
		// send TooManyParam to sender
		throw TooManyParamException(); //ToDo
	}

	for (unsigned int i = 0; i < channels.size(); i++)
	{
		try
		{
			if (!check_existence(channels[i], this->channels))
			{
				//ToDo
			}
		}
	}

	for (unsigned int i = 0; i < channels.size(); i++)
	{
		server_msg = ":" + this->clients[client_fd].get_name() + "!" + this-.clients[client_fd].get_username() + "@irc.project.com JOIN " + channels[i] + "\r\n";
		send(client_fd, server_msg.c_str(), server_msg.size(), 0);
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
	print_msg(FAINT, WHITE, client_msg);
	std::string	server_msg;
	
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
}

/*
notes:
QUIT server_msg = :<client.nickname>!<client.username>@<server.name> QUIT :<client.nickname> has disconnected\r\n

NUMRPL

Nickname taken : number - client.nickname - arg - msg
server_msg = 433 <client.nickname> <existing_nickname> :Nickname is taken\r\n

Unknown Command : number - client.nickname - arg - msg
server_msg = 421 <client.nickname> <unknown command> :Unknown command\r\n

Welcome : server_name - number - client.nickname - msg - arg - msg
server_msg = :<server_name> 001 <client.nickname> :Welcome <client.nickname> to the Internet Relay Network!\r\n

Password incorrect : number - client.nickname - msg
server_msg = 464 <client.nickname> :Password incorrect\r\n
*/
