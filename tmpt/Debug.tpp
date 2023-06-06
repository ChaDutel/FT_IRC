/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Debug.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:12:08 by ljohnson          #+#    #+#             */
/*   Updated: 2023/05/15 14:47:28 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Debug.hpp>

template<typename T>
T	Debug::print_msg(char const* style, char const* color, std::string const& message, T const val) throw()
{
	std::cerr << style << color;
	std::cerr << message;
	std::cerr << RESET << std::endl;
	return (val);
}

template<typename T>
T	Debug::print_msg(std::string const& message, T const val) throw()
{
	std::cerr << message << std::endl;
	return (val);
}

template<typename T1, typename T2, typename T3, typename T4>
void	Debug::info(T1 t1, T2 t2, T3 t3, T4 t4, std::string const& str) throw()
{
	std::cerr << RED << BOLD << "Debug from function: " << str << RESET << std::endl;
	if (Debug::level >= 1)
		std::cerr << "value T1: " << CYAN << BOLD << t1 << RESET << std::endl;
	if (Debug::level >= 2)
		std::cerr << "value T2: " << CYAN << BOLD << t2 << RESET << std::endl;
	if (Debug::level >= 3)
		std::cerr << "value T3: " << CYAN << BOLD << t3 << RESET << std::endl;
	if (Debug::level >= 4)
		std::cerr << "value T4: " << CYAN << BOLD << t4 << RESET << std::endl;
}