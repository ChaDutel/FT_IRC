/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:36:07 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/19 18:55:17 by ljohnson         ###   ########lyon.fr   */
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

template<typename T> //T = Client / Channel
bool	check_existence(std::string const& name, std::map<int, T> const& argmap)
{
	typename std::map<int, T>::const_iterator	it = argmap.begin();
	while (it != argmap.end())
	{
		if (it->second.get_name() == name)
			return (true);
		it++;
	}
	return (false);
}
