/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:14:30 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/21 14:32:04 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Exceptions.hpp>

char const*	GenericException::what()				const throw() {return ("ERROR: GenericException placeholder");}

// User input
char const*	UserInputException::what()				const throw() {return ("ERROR: UserInputException placeholder");}
char const*	NotEnoughArgumentException::what()		const throw() {return ("ERROR: Usage is ./ircserv <port> <password>");}
char const*	InvalidArgumentException::what()		const throw() {return ("ERROR: Invalid argument specified");}
char const*	InvalidPortException::what()			const throw() {return ("ERROR: Invalid port specified");}

// System call
char const*	SystemCallException::what()				const throw() {return ("ERROR: SystemCallException placeholder");}
char const*	SocketFailException::what()				const throw() {return ("ERROR: Socket Failed");}
char const*	SetSockOptFailException::what()			const throw() {return ("ERROR: SetSockOpt Failed");}
char const*	BindFailException::what()				const throw() {return ("ERROR: Bind Failed");}
char const*	ListenFailException::what()				const throw() {return ("ERROR: Listen Failed");}
char const*	RecvFailException::what()				const throw() {return ("ERROR: Recv Failed");}
char const*	SelectFailException::what()				const throw() {return ("ERROR: Select Failed");}
char const*	AcceptFailException::what()				const throw() {return ("ERROR: Accept Failed");}

// Signal
char const*	SigIntException::what()					const throw() {return ("SIGINT called, server stopped.");}

// Code
char const*	InvalidAuthIdException::what()			const throw() {return ("ERROR: Invalid authentification ID given");}

// Client Input
char const*	ClientInputException::what()			const throw() {return ("ERROR: ClientInputException placeholder");}
char const*	WrongSyntaxException::what()			const throw() {return ("ERROR: Wrong syntax in argument specified");}
char const*	WrongNicknameException::what()			const throw() {return ("ERROR: Wrong syntax in nickname specified (You can't use #)");}
char const*	ClientHasQuitException::what()			const throw() {return ("Client has quit");}
char const*	NicknameTakenException::what()			const throw() {return ("ERROR: The nickname specified is already taken");}
char const*	IncorrectPassException::what()			const throw() {return ("ERROR: Client password incorrect");}
char const*	MessageNotFoundException::what()		const throw() {return ("ERROR: Message not found in PRIVMSG");}
char const*	ClientDoesNotExistException::what()		const throw() {return ("ERROR: Client specified does not exist");}
char const*	ChannelDoesNotExistException::what()	const throw() {return ("ERROR: Channel specified does not exist");}
char const*	ClientIsNotInChannelException::what()	const throw() {return ("ERROR: User is not in the specified channel");}
char const*	ClientAlreadyInMapException::what()		const throw() {return ("ERROR: Client is already in specified map");}
char const*	ClientIsNotInMapException::what()		const throw() {return ("ERROR: Client is not in specified map");}
char const*	MessageToLongException::what()			const throw() {return ("ERROR: Message sent is too long");}
