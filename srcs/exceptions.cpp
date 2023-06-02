/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:49:42 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/02 15:53:10 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <exceptions.hpp>

char const*	SocketFailException::what()		const throw() {return ("ERROR: Socket Failed");}
char const*	SetSockOptFailException::what()	const throw() {return ("ERROR: SetSockOpt Failed");}
char const*	BindFailException::what()		const throw() {return ("ERROR: Bind Failed");}
char const*	ListenFailException::what()		const throw() {return ("ERROR: Listen Failed");}