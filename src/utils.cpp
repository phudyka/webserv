/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:19:16 by phudyka           #+#    #+#             */
/*   Updated: 2024/03/01 16:19:33 by phudyka          ###   ########.fr       */
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

void webServ::broadcastShutdown(void)
{
    const char	*shutdown= "[Server is shutting down]";

    for (size_t i = 0; i < _clients->size(); ++i)
		send((*_clients)[i].getSocket(), shutdown, strlen(shutdown), 0);
}

void	webServ::shutDown(void)
{
	broadcastShutdown();
	delete	_clients;
	std::cout << YELLOW << "[Clients datas has been succesfully erased]" << RESET << std::endl;
	close(_socketServer);
	std::cout << YELLOW << "[Server socket has been succesfully closed]" << RESET << std::endl;
}