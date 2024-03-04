/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:19:16 by phudyka           #+#    #+#             */
/*   Updated: 2024/03/04 11:23:12 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

void	webServ::logConnection(const std::string& msg, const std::string id)
{
    char		timeStr[20];
	time_t		currentTime = time(NULL);
    struct tm*	localTime = localtime(&currentTime);

    strftime(timeStr, sizeof(timeStr),"[%Y-%m-%d %H:%M] ", localTime);
    std::cout << BLUE << timeStr << RESET << msg << GREEN << id << RESET << std::endl;
}

void	webServ::shutDown(void)
{
	std::cout << std::endl << CYAN << "[Clients datas has been succesfully erased]" << RESET << std::endl;
	close(_socketServer);
	std::cout << CYAN << "[Server socket has been succesfully closed]" << RESET << std::endl;
	std::cout << YELLOW << "[Webserv has been shutdown succesfully]" << RESET << std::endl;
}