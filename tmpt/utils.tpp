/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:36:07 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/25 17:56:20 by cdutel-l         ###   ########lyon.fr   */
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

template<typename T1, typename T2> //T1 = int / std::string | T2 = Client / Channel
bool	check_existence(std::string const& name, std::map<T1, T2> const& argmap)
{
	typename std::map<T1, T2>::const_iterator	it = argmap.begin();
	while (it != argmap.end())
	{
		if (it->second->get_name() == name)
			return (true);
		it++;
	}
	return (false);
}

template<typename T1, typename T2> //T1 = int / std::string | T2 = Client / Channel
bool	check_existence_ptr(std::string const& name, std::map<T1, T2> const& argmap)
{
	typename std::map<T1, T2>::const_iterator	it = argmap.begin();
	while (it != argmap.end())
	{
		if (it->second.get_name() == name)
			return (true);
		it++;
	}
	return (false);
}

