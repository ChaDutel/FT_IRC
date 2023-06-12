/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:37:42 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/06/12 16:38:19 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

template<typename T> //T = Client / Channel
bool	check_existence(std::string const& name, std::map<int, T> argmap)
{
	typename std::map<int, T>::iterator	it = argmap.begin();
	while (it != argmap.end())
	{
		if (it->second.get_name() == name)
			return (true);
		it++;
	}
	return (false);
}
