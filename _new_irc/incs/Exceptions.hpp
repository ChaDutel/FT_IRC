/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:12:02 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 11:13:49 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>

class	GenericException 			: public std::exception {public: virtual char const*	what() const throw();};

// User input
class	NotEnoughArgumentException	: public std::exception {public: virtual char const*	what() const throw();};
class	InvalidArgumentException	: public std::exception {public: virtual char const*	what() const throw();};
class	InvalidPortException		: public std::exception {public: virtual char const*	what() const throw();};

// System call
class	SocketFailException			: public std::exception {public: virtual char const*	what() const throw();};
class	SetSockOptFailException		: public std::exception {public: virtual char const*	what() const throw();};
class	BindFailException			: public std::exception {public: virtual char const*	what() const throw();};
class	ListenFailException			: public std::exception {public: virtual char const*	what() const throw();};

// Signal
class	SigIntException				: public std::exception {public: virtual char const*	what() const throw();};