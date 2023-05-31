/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:18:40 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/05/31 15:13:48 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

			// for (i = 1; i < MAX_CONNECTIONS; i++)
			// {
			// 	if (all_connections[i] < 0)
			// 		continue;
			// 	if (FD_ISSET(all_connections[i], &read_fd_set))
			// 	{
			// 		char buffer[DATA_BUFFER];
			// 		int bytes_received = recv(all_connections[i], buffer, DATA_BUFFER, 0);
			// 		if (bytes_received > 0)
			// 		{
			// 			buffer[bytes_received] = '\0';
			// 			std::string message(buffer);

			// 			// Check if the message starts with the /nick command
			// 			if (message.substr(0, 5) == "/nick")
			// 			{
			// 				std::string new_nickname = message.substr(6); // Extract the new nickname

			// 				// Remove the newline character from the new_nickname if present
			// 				size_t newline_pos = new_nickname.find('\n');
			// 				if (newline_pos != std::string::npos)
			// 				{
			// 					new_nickname = new_nickname.substr(0, newline_pos);
			// 				}

			// 				// Debug output to check the extracted new_nickname
			// 				std::cout << "New nickname: " << new_nickname << std::endl;

			// 				// Update the nickname for the corresponding client
			// 				// (you'll need to implement a data structure to store nicknames for each client)
			// 			}
			// 			else
			// 			{
			// 				std::cout << "Received data: " << buffer << std::endl;
			// 			}
			// 		}
			// 		else
			// 		{
			// 			std::cout << "Client disconnected" << std::endl;
			// 			close(all_connections[i]);
			// 			all_connections[i] = -1;
			// 		}
			// 	}
			// }


		// for (i = 1; i < MAX_CONNECTIONS; i++)
		// {
		// 	if (all_connections[i] < 0)
		// 		continue;
		// 	if (FD_ISSET(all_connections[i], &read_fd_set))
		// 	{
		// 		char buffer[DATA_BUFFER];
		// 		int bytes_received = recv(all_connections[i], buffer, DATA_BUFFER, 0);
		// 		if (bytes_received > 0)
		// 		{
		// 			buffer[bytes_received] = '\0';
		// 			std::string message(buffer);

		// 			// Check if the message starts with the /nick command
		// 			if (message.substr(0, 5) == "/nick")
		// 			{
		// 				// Receive the newline character
		// 				char newline_buffer[2];
		// 				int newline_received = recv(all_connections[i], newline_buffer, 1, 0);
		// 				if (newline_received > 0)
		// 				{
		// 					newline_buffer[newline_received] = '\0';
		// 					std::string newline_str(newline_buffer);

		// 					// Check if the received character is a newline character
		// 					if (newline_str == "\n")
		// 					{
		// 						std::string new_nickname = message.substr(6); // Extract the new nickname

		// 						// Debug output to check the extracted new_nickname
		// 						std::cout << "New nickname: " << new_nickname << std::endl;

		// 						// Update the nickname for the corresponding client
		// 						// (you'll need to implement a data structure to store nicknames for each client)
		// 					}
		// 				}
		// 			}
		// 			else
		// 			{
		// 				std::cout << "Received data: " << buffer << std::endl;
		// 			}
		// 		}
		// 		else
		// 		{
		// 			std::cout << "Client disconnected" << std::endl;
		// 			close(all_connections[i]);
		// 			all_connections[i] = -1;
		// 		}
		// 	}
		// }


			// for (i = 1; i < MAX_CONNECTIONS; i++)
            // {
			// 	if (all_connections[i] < 0)
			// 		continue;
			// 	if (FD_ISSET(all_connections[i], &copy))
			// 	{

			// 		char buffer[DATA_BUFFER];
			// 		int bytes_received = recv(all_connections[i], buffer, DATA_BUFFER, 0);
			// 		if (bytes_received > 0)
			// 		{
			// 			buffer[bytes_received] = '\0';
						// std::string message(buffer);

						// std::cout << "DEBUG message: " << message << std::endl;

						// // Check if the message starts with the /nick command
						// if (message.substr(0, 5) == "/nick")
						// {
						// 	std::string new_nickname = message.substr(6); // Extract the new nickname
						// 	// Update the nickname for the corresponding client
						// 	// (you'll need to implement a data structure to store nicknames for each client)
						// 	std::cout << new_nickname << std::endl;
						// }
						// else
						// {
						// 	std::cout << "Received data: " << buffer << std::endl;
						// }
			// 		}
			// 		else
			// 		{
			// 			std::cout << "Client disconnected" << std::endl;
			// 			close(all_connections[i]);
			// 			all_connections[i] = -1;
			// 		}
					
			// 		// char buffer[DATA_BUFFER];
			// 		// int bytes_received = recv(all_connections[i], buffer, DATA_BUFFER, 0);
			// 		// if (bytes_received > 0)
			// 		// {
			// 			// 	buffer[bytes_received] = '\0';
			// 			// 	std::cout << "Received data: " << buffer << std::endl;
			// 			// 	send(new_fd, "Welcome\n", 8, 0);
			// 		// }
			// 		// else
			// 		// {
			// 		// 	std::cout << "Client disconnected" << std::endl;
			// 		// 	close(all_connections[i]);
			// 		// 	all_connections[i] = -1;
			// 		// }
			// 	}
			// }

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#define DATA_BUFFER 4096
#define MAX_CONNECTIONS 10


// void sendCommand(const std::string& server, const std::string& channel, const std::string& nick, const std::string& command, const std::string& params)
// {
//     std::stringstream message;
//     message << command << " " << params << "\r\n";
//     std::cout << "Sending: " << message.str() << std::endl;
//     // Implement the logic to send the message to the server.
// }

// void handlePing(const std::string& server, const std::string& channel, const std::string& nick, const std::string& message)
void handlePing(int server, const std::string& message)
{
    std::string params = message;
    std::string command = "PONG " + params;
	send(server, command.c_str(), command.size(), 0);
	// (void)server;
	std::cout << "shoudl have send pong\n";
    // sendCommand(server,nick, command, params);
}


void	findCommand(std::string message, char *buffer, int new_fd)
{
	static std::string username;
	static std::string nickName;
	if (message.substr(0, 4) == "PASS")
	{
		std::string newPass = message.substr(5);
		std::cout << "New pass is " << newPass.c_str(); //<< std::endl;
	}
	else if (message.substr(0, 4) == "NICK")
	{
		nickName = message.substr(5); // Extract the new nickname
		nickName.erase(nickName.length() -2, nickName.length());
		// std::string nickName = message.substr(5); // Extract the new nickname
		// Update the nickname for the corresponding client
		// (you'll need to implement a data structure to store nicknames for each client)
		std::cout << "New Nickname is " << nickName.c_str(); //<< std::endl;
	}
	else if (message.substr(0, 4) == "USER")
	{
		username = message.substr(5);
		username.erase(username.length() -2, username.length());
		// std::string username = message.substr(5);
		std::string	ret = ":irc.project.com 001 " + nickName + " :Welcome " + nickName + " to the Internet Relay Network!\r\n";
		std::cout << ret << std::endl;
		std::cout << "-" << nickName << "-" << std::endl;
		// std::string	ret = ":irc.project.com 001 cdutel-l :Welcome cdutel-l to the Internet Relay Network!\r\n";
		// std::string	ret = ":irc.project.com 001 " + username + " :Welcome to the Internet Relay Network!\r\n";
		send(new_fd, ret.c_str(), ret.size(), 0);
	}
	else if (message.substr(0, 3) == "MSG") // /msg <nickname> <message> 
	{
		// std::string new_msg = message.substr(6);
		// std::cout << "New msg is " << new_msg.c_str();

		// send(nickname, "message\n", message.size(), 0);
	}
	else if (message.substr(0, 4) == "JOIN")
	{
		std::cout << "BOUH" << std::endl;
		// std::cout << getUSer()/getNick() << " comes to the " << getChannelName() << " channel" << std::endl;
	}
	else if (message.substr(0, 4) == "PART")
	{
		// std::cout << getUSer()/getNick() << " quit the" << getChannelName() << " channel" << std::endl;
	}
	else  if (message.substr(0, 4) == "PING")
	{
		std::string pongMessage = message.substr(5);
		handlePing(new_fd, pongMessage);
		// handlePing(server, channel, nick, pongMessage);
	}
	else
	{
		std::cout << "Received data: " << buffer << std::endl;
		// send(new_fd, "Welcome to the Internet Relay Network <nick>!<user>@<host>", 60, 0);
	}
	// (void)new_fd;
	/* if ((isPass && isNick) == true && isWelcome == false)
	{
		send(new_fd, "Welcome\n", 8, 0);
		isWelcome = true;
	} */
}

void handle_client_connections(int server_fd)
{
	fd_set read_fd_set;
	struct sockaddr_in new_addr;
	int new_fd;
	int ret_val;
	int i;
	socklen_t addrlen;

	// Declare and initialize the all_connections array
	int all_connections[MAX_CONNECTIONS];
	for (i = 0; i < MAX_CONNECTIONS; i++)
		all_connections[i] = -1;

	// Add the server socket to the all_connections array
	all_connections[0] = server_fd;


	FD_ZERO(&read_fd_set);
	FD_SET(server_fd, &read_fd_set);

	
	while (1)
	{
		fd_set copy = read_fd_set;
		for (i = 0; i < MAX_CONNECTIONS; i++)
		{
			if (all_connections[i] >= 0)
				FD_SET(all_connections[i], &copy);
		}
		ret_val = select(FD_SETSIZE, &copy, NULL, NULL, NULL);
		if (ret_val >= 0)
		{
			if (FD_ISSET(server_fd, &copy)) // Check if server socket is ready to accept new connections
			{
				addrlen = sizeof(new_addr);
				new_fd = accept(server_fd, (struct sockaddr *)&new_addr, &addrlen);
				if (new_fd >= 0)
				{
					for (i = 0; i < MAX_CONNECTIONS; i++)
					{
						if (all_connections[i] < 0)
						{
							all_connections[i] = new_fd;
							break;
						}
					}
				}
				
			}

			for (i = 1; i < MAX_CONNECTIONS; i++)
			{
				if (all_connections[i] < 0)
					continue;
				if (FD_ISSET(all_connections[i], &copy))
				{
					char buffer[DATA_BUFFER];
					int bytes_received = recv(all_connections[i], buffer, DATA_BUFFER, 0);
					if (bytes_received > 0)
					{
						buffer[bytes_received] = '\0';
						std::string message(buffer);

						// Check if the message starts with the /nick command
						findCommand(message, buffer, new_fd);

						// if (message.substr(0, 5) == "/nick")
						// {
						// 	std::string new_nickname = message.substr(6); // Extract the new nickname
						// 	// Update the nickname for the corresponding client
						// 	// (you'll need to implement a data structure to store nicknames for each client)
						// 	std::cout << "New Nickname is " << new_nickname.c_str(); //<< std::endl;
						// 	// dprintf(, "%s", new_nickname);
						// }
						// else
						// {
						// 	std::cout << "Received data: " << buffer << std::endl;
						// }
						
						// send(new_fd, "Welcome\n", 8, 0);
					}
					else
					{
						std::cout << "Client disconnected" << std::endl;
						close(all_connections[i]);
						all_connections[i] = -1;
					}
				}
			}

		}
	}
}
			// for (i = 1; i < MAX_CONNECTIONS; i++)
			// {
			// 	if (all_connections[i] < 0)
			// 		continue;
			// 	if (FD_ISSET(all_connections[i], &copy))
			// 	{
			// 		char buffer[DATA_BUFFER];
			// 		int bytes_received = recv(all_connections[i], buffer, DATA_BUFFER, 0);
			// 		if (bytes_received > 0)
			// 		{
			// 			buffer[bytes_received] = '\0';
			// 			std::cout << "Received data: " << buffer << std::endl;
			// 			if (buffer == "nick")
			// 				dprintf("%s", buffer);
			// 			send(new_fd, "Welcome\n", 8, 0);
			// 		}
			// 		else
			// 		{
			// 			std::cout << "Client disconnected" << std::endl;
			// 			close(all_connections[i]);
			// 			all_connections[i] = -1;
			// 		}
			// 	}
			// }

int create_tcp_server_socket()
{
	int 				fd;
	struct sockaddr_in saddr;
	int					Optval;

	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == -1)
	{
		std::cerr << "ERROR : Socket failed" << std::endl;
		return (-1);
	}
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &Optval, sizeof(Optval)) < 0)
		return (-1);
        // throw(std::runtime_error("Error: socket option attribution failed"));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6667);
	saddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(fd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in)) != 0)
	{
		std::cerr << "ERROR : Bind failed" << std::endl;
		close(fd);
		return (-1);
	}

	if (listen(fd, SOMAXCONN) == -1) // if (listen(listenSocket, nbclient) == -1)
	{
		std::cerr << "ERROR : Can't listen";
		close(fd);
		return (-1);
	}
	return (fd);
}

int main()
{
	int server_fd = create_tcp_server_socket();
	if (server_fd == -1)
		return (0);
	int new_socket = server_fd;

	// while (1)
	// {
	//     handle_client_connections(new_socket);
	// }
	//    ------   I don't see a diff that there is a infinit while() or just call handle_client_connections(new_socket) once
	handle_client_connections(new_socket);
}
