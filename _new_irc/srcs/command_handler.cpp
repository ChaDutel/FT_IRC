/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:12 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 14:32:58 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Channel.hpp>
#include <Client.hpp>

void	Server::command_handler(std::string client_msg, int client_fd)
{
	std::string	server_msg;
	size_t		sp_idx = client_msg.find(' ', 0);

	if (sp_idx == std::string::npos)
		sp_idx = client_msg.size() - 1;
	
	if (client_msg.substr(0, sp_idx + 1) == "QUIT")
	{
		this->clients[client_fd].set_quit(true);
		server_msg = "woof"; //CF QUIT server_msg in notes below
		send(client_fd, server_msg.c_str(), server_msg.size(), 0);
		return ;
	}
	if (this->clients[client_fd].is_authentified())
	{
		
	}
	else
	{
		if ()
	}
}

/*
notes:
QUIT server_msg = :<client.nickname>!<client.username>@<server.name> QUIT :<client.nickname> has disconnected\r\n

NUMRPL

Nickname taken
server_msg = 433 <client.nickname> <existing_nickname> :Nickname is taken\r\n

Unknown Command
server_msg = 421 <client.nickname> <unknown command> :Unknown command\r\n
*/