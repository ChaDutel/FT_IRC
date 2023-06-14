/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:32:44 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/14 13:42:56 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

#include <defines.hpp>

bool	is_digit(char c);
bool	is_alpha_min(char c);
bool	is_alpha_maj(char c);
bool	is_alphanum(char c);

void	remove_last_char(std::string &message);
int		check_syntax(std::string const& str);

template<typename T> //T = Client / Channel
bool	check_existence(std::string const& name, std::map<int, T> argmap);

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