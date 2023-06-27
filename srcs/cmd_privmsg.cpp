/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_privmsg.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:25:56 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/27 18:12:47 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Channel.hpp>

/* ************************************************************************** */
/* PRIVMSG */
/* ************************************************************************** */
void	Server::privmsg_client_handler(std::string const& client_name, int const client_fd, std::vector<std::string> const& msg)
{
	int	recv_fd = get_client_fd_by_name(client_name, this->clients);
	if (recv_fd == -1)
		throw ClientDoesNotExistException();
	if (this->clients[recv_fd].is_authentified())
	{
		std::string	final_msg = ":" + this->clients[client_fd].get_name() + "!" + this->clients[client_fd].get_username();
		final_msg += "@" + this->name + " PRIVMSG " + client_name + " " + msg[2] + "\r\n";
		send(recv_fd, final_msg.c_str(), final_msg.size(), 0);
	}
}

void	Server::privmsg_channel_handler(std::string const& channel_name, int const client_fd, std::vector<std::string> const& msg)
{
	if (!check_existence_ptr(channel_name, this->channels))
		throw ChannelDoesNotExistException();
	if (!check_existence(this->clients[client_fd].get_name(), this->channels[channel_name].get_clients_map()))
		throw ClientIsNotInChannelException();
	std::string	final_msg = ":" + this->clients[client_fd].get_name() + "!" + this->clients[client_fd].get_username();
	final_msg += "@" + this->name + " PRIVMSG " + channel_name + " " + msg[2] + "\r\n";
	this->channels[channel_name].send_message(final_msg, client_fd);
}

//msg[0] = PRIVMSG
//msg[1] = receivers
//msg[2] = message to send
void	Server::cmd_privmsg(std::string& client_msg, int const client_fd)
{
	print_msg(BOLD, BLUE, client_msg);

	std::vector<std::string>	msg = split_str_to_vector(client_msg, ' ');
	if (msg.size() < 3)
	{
		std::string	server_msg = this->clients[client_fd].get_name() + " PRIVMSG :Not enough parameters\r\n";
		send(client_fd, server_msg.c_str(), server_msg.size(), 0);
		throw MessageNotFoundException();
	}
	for (unsigned int i = 3; i < msg.size(); i++)
		msg[2] += " " + msg[i];
	std::vector<std::string>	receivers = split_str_to_vector(msg[1], ',');

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
				throw WrongSyntaxException();
		}
		catch (ClientInputException& e) {print_msg(BOLD, YELLOW, e.what());}
	}
	msg.clear();
	receivers.clear();
}
