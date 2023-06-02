/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:48:51 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/02 15:54:10 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>

class	SocketFailException			: public std::exception {public: virtual char const*	what() const throw();};
class	SetSockOptFailException		: public std::exception {public: virtual char const*	what() const throw();};
class	BindFailException			: public std::exception {public: virtual char const*	what() const throw();};
class	ListenFailException			: public std::exception {public: virtual char const*	what() const throw();};