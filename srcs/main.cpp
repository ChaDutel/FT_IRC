/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:09:38 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/05 16:08:32 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>
#include <Channel.hpp>
#include <Server.hpp>

#include <Server.hpp>
#include <Client.hpp>
#include <Channel.hpp>

int	main(int ac, char** av)
{
	Debug::start(4);
	if (ac != 3 || !av[1][0] || !av[2][0])
		return (1);

	try
	{
		Server	server(av[1], av[2]);
		server.handle_client_connections();

	}
	catch (std::exception& e) {std::cerr << e.what() << std::endl;}

	return (0);
}