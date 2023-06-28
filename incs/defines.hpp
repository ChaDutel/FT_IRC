/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:02:03 by ljohnson          #+#    #+#             */
/*   Updated: 2023/06/28 16:49:04 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// Colors
#define BLACK	"\033[30m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define PURPLE	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"

// Text
#define ERASE		"\033[2K\r"
#define RESET		"\033[0m"
#define BOLD		"\033[1m"
#define FAINT		"\033[2m"
#define ITALIC		"\033[3m"
#define UNDERLINE	"\033[4m"

// Code
#define DATA_BUFFER 1024
#define CLIENT_USER 0
#define CLIENT_NICK 1
#define CLIENT_PASS 2
