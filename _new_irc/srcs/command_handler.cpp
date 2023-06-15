/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:12 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/15 14:47:00 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Channel.hpp>
#include <Client.hpp>

void	Server::cmd_quit(int const client_fd)
{
	std::string	server_msg;

	server_msg = ":" + this->clients[client_fd].get_name() + "!" + this->clients[client_fd].get_username();
	server_msg += "@" + this->name + " QUIT :" + this->clients[client_fd].get_name() + " has disconnected\r\n";
	send(client_fd, server_msg.c_str(), server_msg.size(), 0);
	std::cout << "Client " << this->clients[client_fd].get_name() << " disconnected" << std::endl;
	FD_CLR(client_fd, &(this->exec_fdset));
	this->clients.erase(client_fd);
	throw ClientHasQuitException();
}

void	Server::cmd_nick(std::string& client_msg, int const client_fd)
{
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

void	Server::command_handler(std::string client_msg, int client_fd)
{
	std::string	server_msg;
	
	if (client_msg.substr(0, 4) == "QUIT")
		return (cmd_quit(client_fd));
	if (client_msg.substr(0, 4) == "NICK" && client_msg.size() > 4)
		return (cmd_nick(client_msg, client_fd));
	// else if (this->clients[client_fd].is_authentified())
	// {
	// 	// if (message.substr(0, 4) == "PING" && message.size() > 4)
	// 	// 	return (cmd_ping()); //ToDo
	// 	// if (message.substr(0, 7) == "PRIVMSG" && message.size() > 7)
	// 	// 	return (cmd_privmsg()); //ToDo
	// }
	// else
	// {
	// 	// if (message.substr(0, 4) == "PASS" && message.size() > 4)
	// 	// 	return (cmd_pass()); //ToDo
	// 	// else if (message.substr(0, 4) == "USER" && message.size() > 4)
	// 	// 	return (cmd_user()); //ToDo
	// }
}

/*
notes:
QUIT server_msg = :<client.nickname>!<client.username>@<server.name> QUIT :<client.nickname> has disconnected\r\n

NUMRPL

Nickname taken : number - client.nickname - arg - msg
server_msg = 433 <client.nickname> <existing_nickname> :Nickname is taken\r\n

Unknown Command : number - client.nickname - arg - msg
server_msg = 421 <client.nickname> <unknown command> :Unknown command\r\n
*/