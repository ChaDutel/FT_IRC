/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:36:07 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 11:36:30 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <utils.hpp>

template<typename T>
T	print_msg(char const* style, char const* color, std::string const& message, T const val)
{
	std::cout << style << color;
	std::cout << message;
	std::cout << RESET << std::endl;
	return (val);
}

template<typename T>
T	print_msg(std::string const& message, T const val)
{
	std::cout << message << std::endl;
	return (val);
}