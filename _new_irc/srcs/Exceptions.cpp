/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:14:30 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/13 11:09:15 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Exceptions.hpp>

char const*	GenericException::what()	const throw() {return ("ERROR: This exception is a placeholder");}

// User input
char const*	NotEnoughArgumentException::what()	const throw() {return ("ERROR: Usage is ./ircserv <port> <password>");}
char const*	InvalidArgumentException::what()	const throw() {return ("ERROR: Invalid argument specified");}
char const*	InvalidPortException::what()		const throw() {return ("ERROR: Invalid port specified");}

// System call
char const*	SocketFailException::what()				const throw() {return ("ERROR: Socket Failed");}
char const*	SetSockOptFailException::what()			const throw() {return ("ERROR: SetSockOpt Failed");}
char const*	BindFailException::what()				const throw() {return ("ERROR: Bind Failed");}
char const*	ListenFailException::what()				const throw() {return ("ERROR: Listen Failed");}

// Signal
char const*	SigIntException::what()					const throw() {return ("SIGINT called, server stopped.");}