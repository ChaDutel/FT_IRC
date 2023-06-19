/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:12 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/19 19:28:11 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Channel.hpp>
#include <Client.hpp>

/* ************************************************************************** */
/* PRIVMSG */
/* ************************************************************************** */
std::vector<std::string>	Server::split_client_msg(std::string const& client_msg, int const client_fd)
{
	std::vector<std::string>	split;
	int							found = -1;

	split.push_back(client_msg.substr(0, 7));
	found = client_msg.find(' ', 8);
	if (found == static_cast<int>(std::string::npos) || found == static_cast<int>(client_msg.size() - 1))
	{
		std::string	server_msg = this->clients[client_fd].get_name() + " PRIVMSG :Not enough parameters\r\n";
		send(client_fd, server_msg.c_str(), server_msg.size(), 0);
		throw MessageNotFoundException();
	}
	split.push_back(client_msg.substr(8, found - 8));
	split.push_back(client_msg.substr(found + 1, std::string::npos));
	return (split);
}

std::vector<std::string>	split_receivers(std::string const& receivers)
{
	std::vector<std::string>	split;
	int	head = 0;
	int	tail = 0;

	while (tail != static_cast<int>(std::string::npos) || receivers[tail])
	{
		head = receivers.find(',', tail);
		if (head == static_cast<int>(std::string::npos))
			break ;
		split.push_back(receivers.substr(tail, (head - tail)));
		tail = head + 1;
	}
	split.push_back(receivers.substr(tail, std::string::npos));

	for (std::vector<std::string>::iterator it = split.begin(); it != split.end(); it++)
	{
		if (it->empty())
		{
			split.erase(it);
			it = split.begin();
		}
	}
	return (split);
}

int	get_client_fd_by_name(std::string const& receiver, std::map<int, Client> const& clients)
{
	std::map<int, Client>::const_iterator	it = clients.begin();
	while (it != clients.end())
	{
		if (receiver == it->second.get_name())
			return (it->first);
		it++;
	}
	return (-1);
}

//msg[0] = PRIVMSG
//msg[1] = receivers
//msg[2] = message to send
void	Server::cmd_privmsg(std::string& client_msg, int const client_fd)
{
	print_msg(BOLD, BLUE, client_msg);

	std::vector<std::string>	msg = split_client_msg(client_msg, client_fd);
	std::vector<std::string>	receivers = split_receivers(msg[1]);

	for (unsigned int i = 0; i < receivers.size(); i++)
	{
		try
		{
			int	syntax = check_syntax(receivers[i]);
			if (syntax == 1) // client
			{
				int	recv_fd = get_client_fd_by_name(receivers[i], this->clients);
				if (client_fd == -1)
				{
					// send ReceiverDoesNotExist to sender
					throw ClientDoesNotExistException();
				}
				std::string	final_msg = this->clients[client_fd].get_name() + " PRIVMSG " + receivers[i] + " " + msg[2] + "\r\n";
				send(recv_fd, final_msg.c_str(), final_msg.size(), 0);
			}
			else if (syntax == 2) // channel
			{
				if (!check_existence(receivers[i], this->channels))
				{
					// send ChannelDoesNotExist to sender
					throw ChannelDoesNotExistException();
				}
				if (/*check if sender is in client_map of channel*/)
				{
					// send UnserIsNotInChannel to sender
					throw UserIsNotInChannelException();
				}
				std::string	final_msg = ":" + this->clients[client_fd].get_name() + "!" + this->clients[client_fd].get_username();
				final_msg += "@" + this->name + " PRIVMSG " + receivers[i] + " " + msg[2] + "\r\n";
				this->channels[receivers[i]].send_message(final_msg);
			}
			// send WrongSyntax with receivers[i] to sender
			throw WrongSyntaxException();
		}
		catch (ClientInputException& e) {print_msg(BOLD, YELLOW, e.what());}
	}
}

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
		if (check_existence(chosen_nickname, this->clients))
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
			cmd_privmsg(client_msg, client_fd); //ToDo
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