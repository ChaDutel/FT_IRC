//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:38:22 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/06/24 18:31:39 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Channel.hpp>
#include <utils.hpp>

/* ************************************************************************** */
/* JOIN */
/* ************************************************************************** */
void	Server::cmd_join(std::string& client_msg, int const client_fd)
{
	print_msg(BOLD, BLUE, client_msg);
	std::vector<std::string>	msg = split_str_to_vector(client_msg, ' ');
	if (msg.size() < 2)
		throw NotEnoughParamException();
	std::vector<std::string>	vec_chan = split_str_to_vector(msg[1], ',');
	std::vector<std::string>	vec_pass;
	if (msg.size() == 3)
		vec_pass = split_str_to_vector(msg[2], ',');
	else if (msg.size() > 3)
		throw TooManyParamException();
	
	if (vec_pass.size() > vec_chan.size())
		throw TooManyPassException();

	std::string server_msg;
	for (unsigned int i = 0; i < vec_chan.size(); i++)
	{
		try
		{
			if (check_syntax(vec_chan[i]) != 2)
				throw WrongSyntaxException();
			if (!check_existence_ptr(vec_chan[i], this->channels))
			{
				Channel	channel_tmp;

				this->channels.insert(std::pair<std::string, Channel>(vec_chan[i], channel_tmp));
				this->channels[vec_chan[i]].add_operator(this->clients[client_fd]);
				this->channels[vec_chan[i]].add_client(this->clients[client_fd]);
				this->channels[vec_chan[i]].set_name(vec_chan[i]);
				if (i < vec_pass.size())
				{
					this->channels[vec_chan[i]].set_pass(vec_pass[i]);
					this->channels[vec_chan[i]].set_need_pass(true);
				}
				server_msg = ":" + this->clients[client_fd].get_name() + "!" + this->clients[client_fd].get_username() + "@" + this->name + " JOIN " + ":" +  vec_chan[i] + "\r\n";
				send(client_fd, server_msg.c_str(), server_msg.size(), 0);
			}
			else
			{
				if (this->channels[vec_chan[i]].get_need_pass())
				{
					if (i < vec_pass.size())
					{
						if (!this->channels[vec_chan[i]].check_pass(vec_pass[i]))
							throw IncorrectChannelPassException();
					}
					else
						throw NeedPassException();
				}
				if (this->channels[vec_chan[i]].get_user_limit() != -1)
				{
					if (this->channels[vec_chan[i]].get_user_limit() <= this->channels[vec_chan[i]].get_nb_clients())
						throw ReachUserLimitException();
				}
				if (this->channels[vec_chan[i]].get_invite_only())
				{
					if (!this->channels[vec_chan[i]].is_invited(this->clients[client_fd].get_name()))
						throw ClientIsNotInvitedException();
					this->channels[vec_chan[i]].remove_invitation(this->clients[client_fd].get_name());
				}
				this->channels[vec_chan[i]].add_client(this->clients[client_fd]);
				server_msg = ":" + this->clients[client_fd].get_name() + "!" + this->clients[client_fd].get_username() + "@" + this->name + " JOIN " + vec_chan[i] + "\r\n";
				send(client_fd, server_msg.c_str(), server_msg.size(), 0);
				
				this->channels[vec_chan[i]].send_namreply(vec_chan[i], this->clients[client_fd]);
				
				server_msg = "366 " + this->clients[client_fd].get_name() + " " + vec_chan[i] + " :End of /NAMES list\r\n";
				send(client_fd, server_msg.c_str(), server_msg.size(), 0);
			}
		}
		catch (ClientInputException& e) {print_msg(BOLD, YELLOW, e.what());}
	}
}
