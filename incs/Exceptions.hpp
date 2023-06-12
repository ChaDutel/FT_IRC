/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:48:51 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/09 16:38:35 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>

class	SocketFailException				: public std::exception {public: virtual char const*	what() const throw();};
class	SetSockOptFailException			: public std::exception {public: virtual char const*	what() const throw();};
class	BindFailException				: public std::exception {public: virtual char const*	what() const throw();};
class	ListenFailException				: public std::exception {public: virtual char const*	what() const throw();};
class	ServerClosedException			: public std::exception {public: virtual char const*	what() const throw();};
class	SelectFailException				: public std::exception {public: virtual char const*	what() const throw();};
class	AcceptFailException				: public std::exception {public: virtual char const*	what() const throw();};
class	SigIntException					: public std::exception {public: virtual char const*	what() const throw();};
class	UserAlreadyOperatorException	: public std::exception {public: virtual char const*	what() const throw();};
class	UserAlreadyInChannelException	: public std::exception {public: virtual char const*	what() const throw();};
class	CannotKickOperatorException		: public std::exception {public: virtual char const*	what() const throw();};
class	UserIsNotOperatorException		: public std::exception {public: virtual char const*	what() const throw();};
class	UserLimitReachedException		: public std::exception {public: virtual char const*	what() const throw();};
class	NotEnoughArgumentException	: public std::exception {public: virtual char const*	what() const throw();};
class	InvalidArgumentException	: public std::exception {public: virtual char const*	what() const throw();};
class	InvalidPortException		: public std::exception {public: virtual char const*	what() const throw();};