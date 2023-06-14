/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:12:02 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/14 14:56:58 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>

class	GenericException 			: public std::exception {public: virtual char const*	what() const throw();};

// User Input
class	UserInputException			: public std::exception {public: virtual char const*	what() const throw();};
class	NotEnoughArgumentException	: public UserInputException {public: virtual char const*	what() const throw();};
class	InvalidArgumentException	: public UserInputException {public: virtual char const*	what() const throw();};
class	InvalidPortException		: public UserInputException {public: virtual char const*	what() const throw();};

// System Call
class	SystemCallException			: public std::exception {public: virtual char const*	what() const throw();};
class	SocketFailException			: public SystemCallException {public: virtual char const*	what() const throw();};
class	SetSockOptFailException		: public SystemCallException {public: virtual char const*	what() const throw();};
class	BindFailException			: public SystemCallException {public: virtual char const*	what() const throw();};
class	ListenFailException			: public SystemCallException {public: virtual char const*	what() const throw();};
class	RecvFailException			: public SystemCallException {public: virtual char const*	what() const throw();};
class	SelectFailException			: public SystemCallException {public: virtual char const*	what() const throw();};
class	AcceptFailException			: public SystemCallException {public: virtual char const*	what() const throw();};

// Signal
class	SigIntException				: public std::exception {public: virtual char const*	what() const throw();};

// Code
class	InvalidAuthIdException		: public std::exception {public: virtual char const*	what() const throw();};

// Client Input
class	ClientInputException		: public std::exception {public: virtual char const*	what() const throw();};
class	WrongSyntaxException		: public ClientInputException {public: virtual char const*	what() const throw();};
class	WrongNicknameException		: public ClientInputException {public: virtual char const*	what() const throw();};
class	ClientHasQuitException		: public ClientInputException {public: virtual char const*	what() const throw();};
class	NicknameTakenException		: public ClientInputException {public: virtual char const*	what() const throw();};