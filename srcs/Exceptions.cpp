/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:49:42 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/09 16:40:27 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Exceptions.hpp>

char const*	SocketFailException::what()				const throw() {return ("ERROR: Socket Failed");}
char const*	SetSockOptFailException::what()			const throw() {return ("ERROR: SetSockOpt Failed");}
char const*	BindFailException::what()				const throw() {return ("ERROR: Bind Failed");}
char const*	ListenFailException::what()				const throw() {return ("ERROR: Listen Failed");}
char const*	ServerClosedException::what()			const throw() {return ("ERROR: Server closed");}
char const*	SelectFailException::what()				const throw() {return ("ERROR: Select Failed");}
char const*	AcceptFailException::what()				const throw() {return ("ERROR: Accept Failed");}
char const*	SigIntException::what()					const throw() {return ("SIGINT called, server stopped.");}
char const*	UserAlreadyOperatorException::what()	const throw() {return ("ERROR: User already Operator in this channel");}
char const*	UserAlreadyInChannelException::what()	const throw() {return ("ERROR: User is already in channel");}
char const*	CannotKickOperatorException::what()		const throw() {return ("ERROR: Cannot kick an operator");}
char const*	UserIsNotOperatorException::what()		const throw() {return ("ERROR: User is not operator in this channel")};
char const*	UserLimitReachedException::what()		const throw() {return ("ERROR: User limit reached in this channel")};
char const*	NotEnoughArgumentException::what()	const throw() {return ("ERROR: Usage is ./ircserv <port> <password>");}
char const*	InvalidArgumentException::what()	const throw() {return ("ERROR: Invalid argument given");}
char const*	InvalidPortException::what()		const throw() {return ("ERROR: Invalid Port given");}
