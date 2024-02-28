/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:59:08 by dtassel           #+#    #+#             */
/*   Updated: 2024/02/28 09:44:18 by dtassel          ###   ########.fr       */
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

}

void    webServ::start()
{
    this->_socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_socketServer == -1)
        throw std::runtime_error("Error : Fail to create a socket server");
    this->_serverAddr.sin_family = AF_INET;
    this->_serverAddr.sin_addr.s_addr = INADDR_ANY;
    this->_serverAddr.sin_port = htons(this->_port);
    socklen_t sockLen = sizeof(this->_serverAddr);
    int bindReturn = bind(this->_socketServer, (struct sockaddr *)&_serverAddr, sockLen);
    if (bindReturn == -1)
        throw std::runtime_error("Error : Fail to link the socket server");
    int listenReturn = listen(this->_socketServer, 5);
    if (listenReturn == -1)
        throw std::runtime_error("Error : Fail to listen connexion");
    this->_isRunning = true;
}

void    webServ::handleConnection()
{
    while (this->_isRunning)
    {
        int clientSocket;
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        clientSocket = accept(this->_socketServer, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == -1)
        {
            std::cerr << "Erreur : échec de l'acceptation de la connexion" << std::endl;
            continue;
        }
        std::cout << "Connexion ok : " << std::endl;
        close(clientSocket);
    }
        close(_socketServer);
}