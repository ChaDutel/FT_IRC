/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_privmsg.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:25:56 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/21 15:55:10 by cdutel-l         ###   ########lyon.fr   */
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

void	Server::privmsg_client_handler(std::string const& client_name, int const client_fd, std::vector<std::string> const& msg)
{
	int	recv_fd = get_client_fd_by_name(client_name, this->clients);
	if (recv_fd == -1)
	{
		// send ClientDoesNotExist to sender
		throw ClientDoesNotExistException();
	}
	std::string	final_msg = ":" + this->clients[client_fd].get_name() + "!" + this->clients[client_fd].get_username();
	final_msg += "@" + this->name + " PRIVMSG " + client_name + " " + msg[2] + "\r\n";
	send(recv_fd, final_msg.c_str(), final_msg.size(), 0);
}

void	Server::privmsg_channel_handler(std::string const& channel_name, int const client_fd, std::vector<std::string> const& msg)
{
	if (!check_existence<std::string, Channel>(channel_name, this->channels))
	{
		// send ChannelDoesNotExist to sender
		throw ChannelDoesNotExistException();
	}
	if (!check_existence<int, Client>(this->clients[client_fd].get_name(), this->channels[channel_name].get_clients_map()))
	{
		// send ClientIsNotInChannel to sender
		throw ClientIsNotInChannelException();
	}
	std::string	final_msg = ":" + this->clients[client_fd].get_name() + "!" + this->clients[client_fd].get_username();
	final_msg += "@" + this->name + " PRIVMSG " + channel_name + " " + msg[2] + "\r\n";
	this->channels[channel_name].send_message(final_msg);
}

//msg[0] = PRIVMSG
//msg[1] = receivers
//msg[2] = message to send
void	Server::cmd_privmsg(std::string& client_msg, int const client_fd)
{
	print_msg(BOLD, BLUE, client_msg);

	std::vector<std::string>	msg = split_client_msg(client_msg, client_fd);
	std::vector<std::string>	receivers = split_args(msg[1]);

	for (unsigned int i = 0; i < receivers.size(); i++)
	{
		try
		{
			int	syntax = check_syntax(receivers[i]);
			if (syntax == 1) // client
				privmsg_client_handler(receivers[i], client_fd, msg);
			else if (syntax == 2) // channel
				privmsg_channel_handler(receivers[i], client_fd, msg);
			else
			{
				// send WrongSyntax with receivers[i] to sender
				throw WrongSyntaxException();
			}
		}
		catch (ClientInputException& e) {print_msg(BOLD, YELLOW, e.what());}
	}
}
