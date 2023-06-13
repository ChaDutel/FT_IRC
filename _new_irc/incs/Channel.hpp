/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:37:07 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 15:42:55 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Server.hpp>

class Channel
{
	private:
		std::string	name;

	public:
		Channel();
		Channel(Channel const& src);
		virtual ~Channel();

		Channel&	operator=(Channel const& rhs);
};