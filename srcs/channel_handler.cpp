/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_handler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:56:50 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/06/29 12:02:50 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Channel.hpp>
#include <Client.hpp>

/* ************************************************************************** */
/* TOPIC */
/* ************************************************************************** */
void	Server::cmd_topic(std::string& client_msg, int const client_fd)
{
	std::vector<std::string>	msg = split_str_to_vector(client_msg, ' ');
	if (!check_existence_ptr(msg[1], this->channels))
		throw ChannelDoesNotExistException();
	if (!check_existence(this->clients[client_fd].get_name(), this->channels[msg[1]].get_clients_map()))
		throw ClientIsNotInChannelException();

	if (msg.size() < 2)
		throw NotEnoughParamException();
	else if (msg.size() > 2)
	{
		if (msg[2].empty())
			throw WrongSyntaxException();
		for (unsigned int i = 3; i < msg.size(); i++)
			msg[2] += " " + msg[i];
		if (this->channels[msg[1]].get_topic_rights())
		{
			if (!check_existence(this->clients[client_fd].get_name(), this->channels[msg[1]].get_operators_map()))
				throw ClientIsNotOperatorException();
		}
		if (msg[2][0] == ':')
			msg[2].erase(0, 1);
		this->channels[msg[1]].set_topic(msg[2]);
	}
	else
	{
		std::string	final_msg = "332 " + this->clients[client_fd].get_name() + " " + msg[1] + " :" + this->channels[msg[1]].get_topic() + "\r\n";
		send(client_fd, final_msg.c_str(), final_msg.size(), 0);
	}
	msg.clear();
}

/* ************************************************************************** */
/* INVITE */
/* ************************************************************************** */
void	Server::cmd_invite(std::string& client_msg, int const client_fd)
{
	std::vector<std::string>	msg = split_str_to_vector(client_msg, ' ');
	if (msg.size() != 3)
		throw NotEnoughParamException();
	if (msg[1] == msg[2])
		return ;

	if (!check_existence_ptr(msg[2], this->channels))
		throw ChannelDoesNotExistException();
	if (!check_existence(this->clients[client_fd].get_name(), this->channels[msg[2]].get_clients_map()))
		throw ClientIsNotInChannelException();
	if (!check_existence(this->clients[client_fd].get_name(), this->channels[msg[2]].get_operators_map()))
		throw ClientIsNotOperatorException();
	if (!check_existence_ptr(msg[1], this->clients))
		throw ClientDoesNotExistException();
	if (check_existence(msg[1], this->channels[msg[2]].get_clients_map()))
		throw ClientAlreadyInMapException();
	if (this->channels[msg[2]].is_invited(msg[1]))
		throw ClientAlreadyInvitedException();
	this->channels[msg[2]].add_invitation(msg[1]);
	std::string	final_msg = ":" + this->clients[client_fd].get_name() + "!" + this->clients[client_fd].get_username() + "@" + this->name + " INVITE " + msg[1] + " :" + msg[2] + "\r\n";
	send(client_fd, final_msg.c_str(), final_msg.size(), 0);
}

/* ************************************************************************** */
/* KICK */
/* ************************************************************************** */
void	Channel::kick_client(Client const& client, std::vector<std::string> const& vec_msg, Client const& target)
{
	if (!check_existence(client.get_name(), this->operators))
		throw ClientIsNotOperatorException();
	if (!check_existence(vec_msg[2], this->clients))
		throw ClientIsNotInChannelException();
	if (check_existence(vec_msg[2], this->operators))
		throw CannotKickOperatorException();
	this->remove_client(target);
	std::string	final_msg = ":" + client.get_name() + "!" + client.get_username() + "@ircserv KICK " + vec_msg[1] + " " + vec_msg[2] + "\r\n";
	send(target.get_client_fd(), final_msg.c_str(), final_msg.size(), 0);
}

void	Server::cmd_kick(std::string& client_msg, int const client_fd)
{
	std::vector<std::string>	msg = split_str_to_vector(client_msg, ' ');
	if (msg.size() < 3)
		throw NotEnoughParamException();
	else if (msg.size() > 3)
		throw TooManyParamException();

	if (!check_existence_ptr(msg[1], this->channels))
		throw ChannelDoesNotExistException();
	this->channels[msg[1]].kick_client(this->clients[client_fd], msg, this->clients[get_client_fd_by_name(msg[2], this->clients)]);
}

/* ************************************************************************** */
/* MODE */
/* ************************************************************************** */
std::string	find_bools_on(Channel chan)
{
	std::string	bools_on;
	if (chan.get_invite_only() == true)
		bools_on += "+i";
	else
		bools_on += "-i";
	if (chan.get_topic_rights() == true)
		bools_on += " +t";
	else
		bools_on += " -t";
	if (chan.get_need_pass() == true)
		bools_on += " +k";
	else
		bools_on += " -k";
	if (chan.get_user_limit() != -1)
		bools_on += " +l";
	else
		bools_on += " -l";
	return (bools_on);
}

void	Server::cmd_mode(std::string& client_msg, int const client_fd)
{
	std::vector<std::string>	msg = split_str_to_vector(client_msg, ' ');
	bool	sign = true;
	if (msg.size() > 4)
		throw TooManyParamException();
	if (!check_existence_ptr(msg[1], this->channels))
		throw ChannelDoesNotExistException();
	if (msg.size() < 3)
	{
		std::string	bools_on = ":" + this->name + " 324 " + this->clients[client_fd].get_name() + " " + msg[1] +  " current channel mods: " + find_bools_on(this->channels[msg[1]]) + "\r\n";
		send(client_fd, bools_on.c_str(), bools_on.size(), 0);
		return ;
	}
	if (msg.size() >= 3 && msg[2].size() > 2)
		throw TooManyParamException();
	if (!check_existence(this->clients[client_fd].get_name(), this->channels[msg[1]].get_operators_map()))
		throw ClientIsNotOperatorException();
	if (msg[2].size() == 2)
	{
		if (msg[2][0] == '-')
			sign = false;
		else if (msg[2][0] == '+')
			sign = true;
		else
			throw WrongSyntaxException();
	}
	int	idx = msg[2].size() - 1;
	switch (msg[2][idx])
	{
		case 'i':
		{
			if (sign == false)
				this->channels[msg[1]].set_invite_only(false);
			else
				this->channels[msg[1]].set_invite_only(true);
			break;
		}
		case 't':
		{
			if (sign == false)
				this->channels[msg[1]].set_topic_rights(false);
			else
				this->channels[msg[1]].set_topic_rights(true);
			break;
		}
		case 'k':
		{
			if (sign == false)
				this->channels[msg[1]].set_need_pass(false);
			else
			{
				if (msg.size() == 4)
				{
					this->channels[msg[1]].set_pass(msg[3]);
					this->channels[msg[1]].set_need_pass(true);
				}
				else
					throw NotEnoughParamException();
			}
			break;
		}
		case 'o':
		{
			if (msg.size() != 4)
				throw NotEnoughParamException();
			if (sign == false)
			{
				if (this->clients[client_fd].get_name() == msg[3])
					throw CannotRemoveOperatorException();
				else if (!check_existence(msg[3], this->channels[msg[1]].get_operators_map()))
					throw CannotRemoveOperatorException();
				else
					this->channels[msg[1]].remove_operator(this->clients[get_client_fd_by_name(msg[3], this->clients)]);
			}
			else
			{
				if (!check_existence(msg[3], this->channels[msg[1]].get_clients_map()))
					throw ClientIsNotInChannelException();
				if (!check_existence(msg[3], this->channels[msg[1]].get_operators_map()))
					this->channels[msg[1]].add_operator(this->clients[get_client_fd_by_name(msg[3], this->clients)]);
				else
					throw ClientAlreadyInMapException();
			}
			break;
		}
		case 'l':
		{
			if (sign == false)
				this->channels[msg[1]].set_user_limit(-1);
			else if (sign == true && msg.size() != 4)
				throw NotEnoughParamException();
			else
			{
				for (unsigned int i = 0; i < msg[3].size(); i++)
				{
					if (!is_digit(msg[3][i]))
						throw WrongSyntaxException();
				}
				this->channels[msg[1]].set_user_limit(std::strtol(msg[3].c_str(), NULL, 10));
			}
			break;
		}
		default :
			throw WrongSyntaxException();
	}
	std::string	final_msg = ":" + this->name + " " + client_msg + "\r\n";
	send(client_fd, final_msg.c_str(), final_msg.size(), 0);
}

