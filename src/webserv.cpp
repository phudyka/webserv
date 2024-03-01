/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:59:08 by dtassel           #+#    #+#             */
/*   Updated: 2024/03/01 11:13:01 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/client.hpp"
#include "../include/webserv.hpp"

webServ::webServ(int port)
{
    this->_port = port;
    this->_rootDirectory = ".";
    this->_isRunning = false;
}

webServ::~webServ()
{
	
	close(_socketServer);
}

void webServ::start()
{
    _socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (_socketServer == -1)
        throw std::runtime_error(RED "Error: Fail to create a socket server" RESET);

    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_addr.s_addr = INADDR_ANY;
    _serverAddr.sin_port = htons(_port);

    socklen_t	sockLen = sizeof(_serverAddr);

    int	bindReturn = bind(_socketServer, (struct sockaddr*)&_serverAddr, sockLen);
    if (bindReturn == -1)
        throw std::runtime_error(RED "Error: Fail to bind the socket server" RESET);

    int	listenReturn = listen(_socketServer, 5);
    if (listenReturn == -1)
        throw std::runtime_error(RED "Error: Fail to listen to connections" RESET);

    _pollfds.push_back(pollfd());
    _pollfds.back().fd = _socketServer;
    _pollfds.back().events = POLLIN;
    _pollfds.back().revents = 0;

    _isRunning = true;
}

void webServ::firstConnection()
{
	std::cout << GREEN << "Welcome to WebServ" << RESET << std::endl << std::endl;
	std::cout << PURPLE << "Waiting for connection..." << RESET << std::endl;
    while (_isRunning)
    {
       int readyCount = poll(&_pollfds[0], static_cast<nfds_t>(_pollfds.size()), -1);
        if (readyCount == -1)
        {
            if (errno == EINTR)
                continue;
            else
                throw std::runtime_error(RED "Error: poll() failed" RESET);
        }
		std::string message = "Welcome to webserv ";
        if (_pollfds[0].revents & POLLIN)
            newConnection();

        for (size_t i = 1; i < _pollfds.size(); ++i)
        {
            if (_pollfds[i].revents & (POLLIN | POLLHUP))
                clientData(i);
        }
    }
}

void webServ::newConnection(void)
{
    struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    int clientSocket = accept(_socketServer, (struct sockaddr*)&clientAddr, &clientLen);

    if (clientSocket == -1)
    {
        std::cerr << RED << "Error: Fail to accept a new connection" << RESET << std::endl;
        return ;
    }

    struct pollfd newPollfd;
    newPollfd.fd = clientSocket;
    newPollfd.events = POLLIN;
    newPollfd.revents = 0;

    _pollfds.push_back(newPollfd);

	// Client newClient(clientSocket, inet_ntoa(clientAddr.sin_addr));
    // _clients.push_back(newClient);
	
    logConnection("Connection from client: ", inet_ntoa(clientAddr.sin_addr));
	send(clientSocket, "Enter username: ", 17, 0);
}

void webServ::clientData(size_t index)
{
    char buff[2048];
    int len = recv(_pollfds[index].fd, buff, sizeof(buff), 0);

    if (len <= 0)
        removeClient(index);
    else
    {
        buff[len] = '\0';
        std::string message = "\x1b[35mReceived data:\x1b[0m ";
        message += buff;
        std::cout << message << std::endl;
    }
}

void webServ::closeClientData(int clientSocket)
{
    close(clientSocket);
    for (size_t i = 0; i < _pollfds.size(); ++i)
    {
        if (_pollfds[i].fd == clientSocket)
        {
            removeClient(i);
            break ;
        }
    }
}

void webServ::removeClient(int index)
{
    _pollfds.erase(_pollfds.begin() + index);
    std::cout << GREEN << "Connection closed." << RESET << std::endl;
}