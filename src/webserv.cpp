/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:59:08 by dtassel           #+#    #+#             */
/*   Updated: 2024/03/01 09:36:39 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
        throw std::runtime_error("Error: Fail to create a socket server");

    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_addr.s_addr = INADDR_ANY;
    _serverAddr.sin_port = htons(_port);
    socklen_t sockLen = sizeof(_serverAddr);
    int bindReturn = bind(_socketServer, (struct sockaddr *)&_serverAddr, sockLen);
    if (bindReturn == -1)
        throw std::runtime_error("Error: Fail to bind the socket server");

    int listenReturn = listen(_socketServer, 5);
    if (listenReturn == -1)
        throw std::runtime_error("Error: Fail to listen to connections");

    _isRunning = true;
}

void webServ::handleConnection(void)
{
    struct pollfd	newPollfd;

    while (_isRunning)
    {
    	newPollfd.fd = _socketServer;
    	newPollfd.events = POLLIN;
    	_pollfds.push_back(newPollfd);
        std::cout << "Waiting for connection..." << std::endl;
        int clientSocket;
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        clientSocket = accept(_socketServer, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == -1)
        {
            throw std::runtime_error("Error: Failed to accept the connection");
            continue ;
        }
		std::string logClient = "Connection from client: ";
        logConnection(logClient, inet_ntoa(clientAddr.sin_addr));
        send(clientSocket, "Enter username: ", 17, 0);
        char buff[2048];
        int len = recv(clientSocket, buff, sizeof(buff), 0);
        buff[len] = '\0';
        std::string message = "Welcome to webserv ";
        message = message + buff;
        send(clientSocket, message.c_str(), message.size(), 0);
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
    std::cout << "Connection closed." << std::endl;
}