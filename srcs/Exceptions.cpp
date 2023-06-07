/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:49:42 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/07 15:48:13 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Exceptions.hpp>

char const*	SocketFailException::what()		const throw() {return ("ERROR: Socket Failed");}
char const*	SetSockOptFailException::what()	const throw() {return ("ERROR: SetSockOpt Failed");}
char const*	BindFailException::what()		const throw() {return ("ERROR: Bind Failed");}
char const*	ListenFailException::what()		const throw() {return ("ERROR: Listen Failed");}
char const*	ServerClosedException::what()	const throw() {return ("ERROR: Server closed");}
char const*	SelectFailException::what()		const throw() {return ("ERROR: Select Failed");}
char const*	AcceptFailException::what()		const throw() {return ("ERROR: Accept Failed");}
char const*	SigIntException::what()			const throw() {return ("SIGINT called, server stopped.");}