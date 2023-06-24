/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:32:16 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/24 18:32:24 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <utils.hpp>

bool	is_digit(char c)		{return (c >= '0' && c <= '9');}
bool	is_alpha_min(char c)	{return (c >= 'a' && c <= 'z');}
bool	is_alpha_maj(char c)	{return (c >= 'A' && c <= 'Z');}
bool	is_alphanum(char c)		{return (is_digit(c) || is_alpha_min(c) || is_alpha_maj(c));}

void	remove_last_char(std::string &message)
{
	if ((message[message.length() - 1]) == '\n')
		message.erase(message.length() - 1, message.length());
	if ((message[message.length() - 1]) == '\r')
		message.erase(message.length() - 1, message.length());
}

void	print_msg(char const* style, char const* color, std::string const& message)
{
	std::cout << style << color;
	std::cout << message;
	std::cout << RESET << std::endl;
}

void	print_msg(std::string const& message)
{
	std::cout << message << std::endl;
}

// if bool = true -> check #
// return -1 if wrong syntax
// return 1 if client
// return 2 if # as first char
int	check_syntax(std::string const& str)
{
	bool	hashtag = false;

	for (int i = 0; str[i]; i++)
	{
		if (i == 0 && str[i] == '#')
		{
			hashtag = true;
			continue ;
		}
		if (!is_alphanum(str[i]) && str[i] != '-' && str[i] != '_')
			return (-1);
	}
	if (hashtag)
		return (2);
	return (1);
}

void	add_client_to_map(Client const& client, std::map<int, Client>& clientmap)
{
	if (check_existence(client.get_name(), clientmap))
		throw ClientAlreadyInMapException();

	clientmap[client.get_client_fd()] = client;
}

void	remove_client_from_map(Client const& client, std::map<int, Client>& clientmap)
{
	if (!check_existence(client.get_name(), clientmap))
		throw ClientIsNotInMapException();

	clientmap.erase(client.get_client_fd());
}

std::vector<std::string>	split_str_to_vector(std::string const& str, char const delim)
{
	std::vector<std::string>	split;
	std::istringstream			iss(str);
	std::string					tmp;

	while (std::getline(iss, tmp, delim))
	{
		if (!tmp.empty())
			split.push_back(tmp);
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

/* ToDo :
Commencer à réfléchir à la création des channels et leur ajout dans le serveur
Commencer à réfléchir à MODE pour les channels
Attention au mot de passe incorrect / invite_only / user_limit etc
	MODE va définir ces conditions
la gestion des invitations est à réfléchir
*/
