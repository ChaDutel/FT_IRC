/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:13:13 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/12 16:41:50 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <Client.hpp>
#include <Channel.hpp>
#include <cerrno>
#include <string.h>

#define DATA_BUFFER 50

//----------------------------------------------------------------- BUILDERS -----------------------------------------------------------------//

Server::Server()
{
	Debug::print_msg(FAINT, WHITE, " Default Server constructor called");
}

/* ************************************************************************** */
/* Initialization */
/* ************************************************************************** */
void	Server::set_fd(char const* port)
{
	int					optval = 1;

	this->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->fd == -1)
		throw SocketFailException();
	if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval)) == -1)
		throw SetSockOptFailException();
	this->saddrin.sin_family = AF_INET;
	this->saddrin.sin_port = htons(std::strtol(port, NULL, 10));
	this->saddrin.sin_addr.s_addr = INADDR_ANY;

	if (bind(fd, (struct sockaddr *)&(this->saddrin), sizeof(struct sockaddr_in)) == -1)
		throw BindFailException();
	if (listen(fd, SOMAXCONN) == -1)
		throw ListenFailException();
}

Server::Server(char const* port, std::string const password) : password(password)
{
	Debug::print_msg(FAINT, WHITE, "Server constructor called");
	set_fd(port);
}
/* ************************************************************************** */

Server::~Server()
{
	Debug::print_msg(FAINT, WHITE, "Server destructor called");
	this->users.clear();
	this->channels.clear();
	close(this->fd);
	FD_CLR(this->fd, &(this->default_fdset));
}

/* ************************************************************************** */
/* Getters & Setters */
/* ************************************************************************** */
void	Server::set_new_client(int id, Client client)
{
	Debug::detail(FILE, LINE, FUNC);
	(void)id;
	(void)client;
}

void	Server::set_new_channel(int id, Channel channel)
{
	Debug::detail(FILE, LINE, FUNC);
	(void)id;
	(void)channel;
}


//----------------------------------------------------------------- FUNCTIONS -----------------------------------------------------------------//

int	get_channel_fd_by_name(std::string tmp, std::map<int, Channel> channel_map)
{
	std::map<int, Channel>::iterator	it = channel_map.begin();
	while (it != channel_map.end())
	{
		if (tmp == channel_map[it->first].get_name())
			return (it->first);
		it++;
	}
	return (-1);
}

//check alphanum - _
// if bool = true -> check #
// return -1 if wrong
// return 1 if client
// return 2 if # as first char
int	check_syntax(std::string const& name)
{
	bool	hashtag = false;
	for (int i = 0; name[i]; i++)
	{
		if (name[0] == '#')
		{
			hashtag = true;
			continue;
		}
		if (!(name[i] <= '9' && name[i] >= '0') && !(name[i] <= 'z' && name[i] >= 'a') && !(name[i] <= 'Z' && name[i] >= 'A') && name[i] != '-' && name[i] != '_')
			return (-1);
	}
	if (hashtag == true)
		return (2);
	return (1);
}

void handle_ping(int client, const std::string& message)
{
	std::cout << "shoudl have send pong\n";

	std::string msg = "PONG ircserv :" + message + "\r\n";
	send(client, msg.c_str(), msg.size(), 0);
}

void Server::authentification(int new_fd, std::string& message)
{
	std::string	err;
	if (message.substr(0, 4) == "NICK" && message.size() > 4)
	{
		std::string	nick_tmp = message.substr(5);
		int			rtn = check_syntax(nick_tmp);
		if (rtn == -1)
			std::cout << "Error nickname : Wrong syntax, only accept alphabet and numbers" << std::endl;
		else if (rtn == 2)
			std::cout << "Error nickname : Can't begin the nickname with #" << std::endl;
		else if (rtn == 1)
		{
			if (check_existence(nick_tmp, this->users) == true)
			{
				if (this->users[new_fd].get_auths(0) == true)
					err = "433 " + this->users[new_fd].get_name() + " " + nick_tmp + ":Nickname is already in use\r\n";
				else
					err = "433 unknown_user " + nick_tmp + " :Nickname is already in use\r\n";
				send(fd, err.c_str(), err.size(), 0);
				return ;
			}
			else
			{
				this->users[fd].set_nickname(nick_tmp);
				std::cout << "the nick is: '"<< this->users[new_fd].get_name() << "'" << std::endl;///////////
				this->users[new_fd].set_auths(0);
			}
		}
	}
	else if (message.substr(0, 4) == "PASS" && message.size() > 4)
	{
		this->users[new_fd].set_password_client(message.substr(5));
		std::cout << "the client password is: '"<< this->users[new_fd].get_password_client() << "'" << std::endl;//////////////
		if (this->users[new_fd].get_password_client() != this->password)
		{
			std::cout << "Error Password : Client Password incorrect, please change your password" << std::endl;
			if (this->users[new_fd].get_auths(0) == false)
				err = "464 unknown_user :Password incorrect\r\n";
			else
				err = "464 " + this->users[new_fd].get_name() + " :Password incorrect\r\n";
			send(new_fd, err.c_str(), err.size(), 0);
		}
		else
			this->users[new_fd].set_auths(1);
	}
	else if (message.substr(0, 4) == "USER" && message.size() > 4)
	{
		if (this->users[new_fd].get_auths(0) == true && this->users[new_fd].get_auths(1) == true)
		{
			this->users[new_fd].set_username(message.substr(5));
			std::cout << "the username is: '"<< this->users[new_fd].get_username() << "'" << std::endl;/////////////
			std::string	ret = ":irc.project.com 001 " + this->users[new_fd].get_name() + " :Welcome " + this->users[new_fd].get_name() + " to the Internet Relay Network!\r\n";
			send(new_fd, ret.c_str(), ret.size(), 0);
			this->users[new_fd].set_auths(2);
		}
		else
		{
			if (this->users[new_fd].get_auths(0) == false)
			{
  				err = "431 unknown_user :No nickname given\r\n";
				send(new_fd, err.c_str(), err.size(), 0);
			}
			std::cout << "Error User : Need to enter a nickname and a password first" << std::endl;
		}
	}
	if (this->users[new_fd].get_auths(0) == true && this->users[new_fd].get_auths(1) && this->users[new_fd].get_auths(2))
		this->users[new_fd].set_auth(true);
}

void	Server::find_command(std::string message, int fd)
{
	std::string	err;
	if (message.substr(0, 4) == "QUIT")
	{	
		this->users[fd].set_quit(true);
		err = ":" + this->users[fd].get_name() + "!" + this->users[fd].get_username() + "@ircserv QUIT :" + this->users[fd].get_name() + "has disconnected\r\n";
		send(fd, err.c_str(), err.size(), 0);
		return ;
	}
	else if (this->users[fd].get_auth() == false)
		authentification(fd, message);
	else
	{
		if (message.substr(0, 4) == "PING" && message.size() > 4)
		{
			std::string pongMessage = message.substr(5);
			handle_ping(fd, pongMessage);
		}
		else if (message.substr(0, 4) == "NICK" && message.size() > 4)
		{
			std::string	nick_tmp = message.substr(5);
			int			rtn = check_syntax(nick_tmp);
			if (rtn == -1)
				std::cout << "Error nickname : Wrong syntax, only accept alphabet and numbers" << std::endl;
			else if (rtn == 2)
				std::cout << "Error nickname : Can't begin the nickname with #" << std::endl;
			else if (rtn == 1)
			{
				if (check_existence(nick_tmp, this->users) == true)
				{
					err = "433 " + this->users[fd].get_name() + " " + nick_tmp + " :Nickname is already in use\r\n";
					send(fd, err.c_str(), err.size(), 0);
					return ;
				}
				else
				{
					this->users[fd].set_nickname(nick_tmp);
					std::cout << "The new nickname is: '"<< this->users[fd].get_name() << "'" << std::endl;///////////
				}
			}
		}
		else if (message.substr(0, 7) == "PRIVMSG" && message.size() > 7)
		{
			std::string	user_to_send;
			std::string	line = message.substr(8);
			// for (int i = 0; line[i] && line[i] != ' '; i++)
			int i = 0;
			while (line[i] && line[i] != ' ')
			{
				user_to_send += line[i];
				i++;
			}
			if (user_to_send.size() == line.size())
			{
				err = this->users[fd].get_name() + " PRIVMSG :Not enough parameters\r\n";
				send(fd, err.c_str(), err.size(), 0);
				std::cout << "Error Private Message : Cannot send private message, miss an argument" << std::endl;
			}
			else
			{
				std::string priv_message = line.substr(i + 1);
				{
					for (unsigned int i = 0; user_to_send[i]; i++)
					{
						size_t j = user_to_send.find(',', i);
						if (j == std::string::npos)
							j = user_to_send.size();
						std::string	tmp_receiver = user_to_send.substr(i, j - i);
						int			rtn = check_syntax(tmp_receiver);
						if (rtn == 1)
						{
							//client
							if (check_existence(tmp_receiver, this->users) == false)
							{
								std::string	final_msg_to_send = this->users[fd].get_name() + " PRIVMSG " + tmp_receiver + " " + priv_message;
								send(fd, final_msg_to_send.c_str(), final_msg_to_send.size(), 0);
							}
							else
								throw GenericException();//err msg client doesn´t exist to client with tmp_receiver
						}
						else if (rtn == 2)
						{
							//channel
							if (check_existence(tmp_receiver, this->channels) == false)
							{
								int	channel_fd = get_channel_fd_by_name(tmp_receiver, this->channels);
								if (channel_fd != -1)
								{
									if (this->channels[channel_fd].is_in_map(fd, this->channels[channel_fd].get_user_map()) == true)
									{
										std::string	final_msg_to_send = ":" + this->users[fd].get_name() + "!" + this->users[fd].get_username() + "@ircsev PRIVMSG " + tmp_receiver + " " + priv_message; // + " :"
										this->channels[channel_fd].send_message(final_msg_to_send);
									}
								}
								else
									throw GenericException();//err msg user is not in channel tmp_receiver
							}
							else
								throw GenericException();//err msg channel doesn´t exist to client with tmp_receiver
						}
						else
							throw GenericException();//err msg to client with tmp_receiver
						i = j;
					}
				}
				std::cout << "User to send is : '" << user_to_send << "' and the private message is '" << priv_message  << "'" << std::endl;
			}
		}
		else
		{
  			err = "421 " + this->users[fd].get_name() + " " + message + " :Unknown command\r\n";
			send(fd, err.c_str(), err.size(), 0);
		}
	}
}

static void	remove_last_char(std::string &message)
{
	if ((message[message.length() - 1]) == '\n')
		message.erase(message.length() - 1, message.length());
	if ((message[message.length() - 1]) == '\r')
		message.erase(message.length() - 1, message.length());
}

void	Server::handle_client_connections()
{
	FD_ZERO(&(this->default_fdset));
	FD_SET(this->fd, &(this->default_fdset));

	while (42)
	{
		fd_set	tmp_fdset = this->default_fdset;

		for (std::map<int, Client>::iterator it = this->users.begin(); it != this->users.end(); it++)
		{
			if (it->first >= 0)
				FD_SET(it->first, &tmp_fdset);
		}
		if (select(FD_SETSIZE, &tmp_fdset, NULL, NULL, NULL) >= 0)
		{
			if (FD_ISSET(this->fd, &tmp_fdset))
			{
				socklen_t	addrlen = sizeof(this->new_addr);
				int new_fd = accept(this->fd, (struct sockaddr *)&(this->new_addr), &addrlen);
				if (new_fd >= 0)
				{
					Client client;
					// verif existence, close fd, map.erase()
					this->users[new_fd] = client;
					FD_SET(new_fd, &tmp_fdset);
				}
				else //accept fail
				{
					//ToDo : Close clients & channels FD
					throw AcceptFailException();
				}
			}
			// else                                           //better without
			// {
			// 	//Server quit with connected client | signal ?
			// 	//ToDo: Close clients & channels FD
			// 	throw ServerClosedException();
			// }
			for (std::map<int, Client>::iterator it = this->users.begin(); it != this->users.end(); it++)
			{
				if (FD_ISSET(it->first, &tmp_fdset))
				{
					//recv
					char	buffer[DATA_BUFFER];
					int		bytes_recv = recv(it->first, buffer, DATA_BUFFER, 0);
					if (bytes_recv > 0 && this->users[it->first].get_quit() == false)
					{
						std::string	message(buffer, bytes_recv);
						remove_last_char(message);
						find_command(message, it->first);
						if (this->users[it->first].get_quit() == true)
						{
							std::cout << "Client disconnected" << std::endl;
							close(it->first);
							FD_CLR(it->first, &tmp_fdset);
							this->users.erase(it->first);
							break;
						}
					}
					else
					{
						std::cout << "Client disconnected" << std::endl;
						close(it->first);
						FD_CLR(it->first, &tmp_fdset);
						this->users.erase(it->first);
						break;
					}
				}
			}
		}
		else //Select Fail
		{
			//ToDo: Close clients & channels FD
			throw SelectFailException();
		}
	}
}
