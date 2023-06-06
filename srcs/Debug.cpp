/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:13:25 by ljohnson          #+#    #+#             */
/*   Updated: 2023/05/22 12:26:53 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <Debug.hpp>

unsigned int						Debug::level;
u_int64_t							Debug::time;
u_int64_t							Debug::bp_time;
unsigned int						Debug::bp_count;
std::map<unsigned int, u_int64_t>	Debug::bp_map_time;
std::map<unsigned int, std::string>	Debug::bp_map_info;

void	Debug::start(unsigned int level) throw()
{
	Debug::level = level;
	Debug::time = 0;
	Debug::bp_time = 0;
	Debug::bp_count = 0;
}

/* ************************************************************************** */
/* PRINT_MSG MODULE */
/* ************************************************************************** */
void	Debug::print_msg(char const* style, char const* color, std::string const& message) throw()
{
	std::cerr << style << color;
	std::cerr << message;
	std::cerr << RESET << std::endl;
}

void	Debug::print_msg(std::string const& message) throw()
{
	std::cerr << message << std::endl;
}

/* ************************************************************************** */
/* INFORMATION MODULE */
/* ************************************************************************** */
void	Debug::detail(std::string const& file, int const& line, std::string const& function) throw()
{
	std::cerr << "Details from function: " << YELLOW << BOLD;
	std::cerr << function << RESET << std::endl;
	std::cerr << "File: " << YELLOW << BOLD << file << RESET << std::endl;
	std::cerr << "Line: " << YELLOW << BOLD << line << RESET << std::endl;
}

/* ************************************************************************** */
/* TIME MODULE */
/* ************************************************************************** */
void	Debug::start_time() throw()
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	Debug::time = s_time.tv_sec * 1000000 + s_time.tv_usec;
}

void	Debug::end_time() throw()
{
	if (Debug::time == 0)
		return ;

	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	std::cerr << "Time elapsed from start to end: " << CYAN;
	std::cerr << (s_time.tv_sec * 1000000 + s_time.tv_usec) - Debug::time << RESET << std::endl;
}

void	Debug::display_milestone(std::string const& str) throw()
{
	if (Debug::time == 0)
		return ;

	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	std::cerr << "Milestone from function: " << YELLOW << str << RESET << std::endl;
	std::cerr << "Time: " << CYAN << (s_time.tv_sec * 1000000 + s_time.tv_usec) - Debug::time << RESET << std::endl;
}

/* ************************************************************************** */
/* BREAKPOINT MODULE */
/* ************************************************************************** */
void	Debug::bp_start() throw()
{
	struct timeval	s_time;

	Debug::bp_time = s_time.tv_sec * 1000000 + s_time.tv_usec;
	Debug::bp_count = 0;
	Debug::bp_map_time.clear();
	Debug::bp_map_info.clear();
}

void	Debug::bp_end() throw()
{
	Debug::bp_map_time.clear();
	Debug::bp_map_info.clear();
	std::cerr << RED << BOLD << Debug::bp_count << RESET;
	std::cerr << " breakpoints cleared." << std::endl;
	Debug::bp_count = 0;
	Debug::bp_time = 0;
}

void	Debug::bp(std::string const& str) throw()
{
	struct timeval	s_time;

	Debug::bp_map_time[Debug::bp_count] = (s_time.tv_sec * 1000000 + s_time.tv_usec) - Debug::bp_time;
	Debug::bp_map_info[Debug::bp_count] = str;
	std::cerr << "Breakpoint #" << Debug::bp_count << " set at ";
	std::cerr << CYAN << Debug::bp_map_time[Debug::bp_count] << RESET << std::endl;
	std::cerr << "Function: " << YELLOW << BOLD << str << RESET << std::endl;
	Debug::bp_count++;
}

void	Debug::display_bp_map() throw()
{
	std::map<unsigned int, u_int64_t>::iterator		itm = Debug::bp_map_time.begin();
	std::map<unsigned int, std::string>::iterator	iti = Debug::bp_map_info.begin();

	while (itm != Debug::bp_map_time.end() && iti != Debug::bp_map_info.end())
	{
		std::cerr << RED << BOLD << "Breakpoint #" << itm->first << RESET << std::endl;
		std::cerr << "BP time: " << CYAN << Debug::bp_map_time[itm->first] << RESET << std::endl;
		std::cerr << "BP info: " << YELLOW << Debug::bp_map_info[iti->first] << RESET << std::endl;
		std::cerr << std::endl;
		itm++;
		iti++;
	}
}

unsigned int	Debug::get_bp_count() throw() {return (Debug::bp_count);}
u_int64_t		Debug::get_bp_time(unsigned int idx) {return (Debug::bp_map_time[idx]);}
std::string		Debug::get_bp_info(unsigned int idx) {return (Debug::bp_map_info[idx]);}