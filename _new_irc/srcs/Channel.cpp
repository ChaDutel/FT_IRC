/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:37:53 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 15:38:56 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Channel.hpp>

Channel::Channel() {}

Channel::Channel(Channel const& src) {*this = src;}

Channel::~Channel() {}

Channel&	Channel::operator=(Channel const& rhs)
{
	this->name = rhs.name;
	return (*this);
}