/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:32:44 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/22 14:49:46 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstring>
#include <istream>
#include <sstream>

#include <defines.hpp>
#include <Client.hpp>
#include <Exceptions.hpp>

bool	is_digit(char c);
bool	is_alpha_min(char c);
bool	is_alpha_maj(char c);
bool	is_alphanum(char c);

void	remove_last_char(std::string &message);
int		check_syntax(std::string const& str);

template<typename T1, typename T2> //T1 = int / std::string | T2 = Client / Channel
bool	check_existence(std::string const& name, std::map<T1, T2> const& argmap);

void	add_client_to_map(Client const& client, std::map<int, Client>& clientmap);
void	remove_client_from_map(Client const& client, std::map<int, Client>& clientmap);
int		get_client_fd_by_name(std::string const& receiver, std::map<int, Client> const& clients);

std::vector<std::string>	split_str_to_vector(std::string const& str, char const delim);

/* ************************************************************************** */
/* print_msg functions */
/* ************************************************************************** */
void	print_msg(char const* style, char const* color, std::string const& message);
void	print_msg(std::string const& message);
template<typename T>
T	print_msg(char const* style, char const* color, std::string const& message, T const val);
template<typename T>
T	print_msg(std::string const& message, T const val);

#include <utils.tpp>
