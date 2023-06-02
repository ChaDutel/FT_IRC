/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Debug.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:10:51 by ljohnson          #+#    #+#             */
/*   Updated: 2023/05/24 13:49:41 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>
#include <sys/time.h>
#include <map>

//colors
#define BLACK		"\033[30m"
#define RED			"\033[31m"
#define GREEN		"\033[32m"
#define YELLOW		"\033[33m"
#define BLUE		"\033[34m"
#define PURPLE		"\033[35m"
#define CYAN		"\033[36m"
#define WHITE		"\033[37m"

//styles
#define BOLD		"\033[1m"
#define FAINT		"\033[2m"
#define ITALIC		"\033[3m"
#define UNDERLINE	"\033[4m"

#define ERASE		"\033[2K\r"
#define RESET		"\033[0m"

//debug
#define FILE		__FILE__
#define LINE		__LINE__
#define FUNC		__PRETTY_FUNCTION__
#define CALL		__builtin_FUNCTION()

/* ************************************************************************** */
/* FT_PRINT_MSG FUNCTION OVERLOADS */
/* ************************************************************************** */
class	Debug
{
	private:
		static unsigned int							level;
		static u_int64_t							time;

		static u_int64_t							bp_time;
		static unsigned int							bp_count;
		static std::map<unsigned int, u_int64_t>	bp_map_time;
		static std::map<unsigned int, std::string>	bp_map_info;

	public:
		static void	start(unsigned int level) throw();

	/* ************************************************************************** */
	/* INFORMATION MODULE */
	/* ************************************************************************** */
		static void	detail(std::string const& file, int const& line, std::string const& function) throw();

		template<typename T1, typename T2, typename T3, typename T4>
		static void	info(T1 t1, T2 t2, T3 t3, T4 t4, std::string const& str = CALL) throw();

		static void	print_msg(std::string const& message) throw();
		static void	print_msg(char const* style, char const* color, std::string const& message) throw();

		template<typename T>
		static T	print_msg(std::string const& message, T const val) throw();

		template<typename T>
		static T	print_msg(char const* style, char const* color, std::string const& message, T const val) throw();
	/* ************************************************************************** */
	/* TIME MODULE */
	/* ************************************************************************** */
		static void	start_time() throw();
		static void	display_milestone(std::string const& str = CALL) throw();
		static void	end_time() throw();
		
	/* ************************************************************************** */
	/* BREAKPOINT MODULE */
	/* ************************************************************************** */
		static void			bp_start() throw();
		static void			bp_end() throw();
		static void			bp(std::string const& str = CALL) throw();

		static void			display_bp_map() throw();
		static unsigned int	get_bp_count() throw();
		static u_int64_t	get_bp_time(unsigned int idx);
		static std::string	get_bp_info(unsigned int idx);
};

#include <Debug.tpp>