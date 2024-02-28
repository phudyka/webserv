/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:59:08 by dtassel           #+#    #+#             */
/*   Updated: 2024/02/28 11:43:30 by dtassel          ###   ########.fr       */
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
    // Initialisation du Serveur et lancement de l'ecoute
    this->_socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_socketServer == -1)
        throw std::runtime_error("Error : Fail to create a socket server");
    std::cout << "Creation du socket : " << GREEN << "OK" << RESET << std::endl;
    this->_serverAddr.sin_family = AF_INET;
    this->_serverAddr.sin_addr.s_addr = INADDR_ANY;
    this->_serverAddr.sin_port = htons(this->_port);
    socklen_t sockLen = sizeof(this->_serverAddr);
    int bindReturn = bind(this->_socketServer, (struct sockaddr *)&_serverAddr, sockLen);
    if (bindReturn == -1)
        throw std::runtime_error("Error : Fail to link the socket server");
    int listenReturn = listen(this->_socketServer, 5);
    if (listenReturn == -1)
        throw std::runtime_error("Error : Fail to listen connection");
    this->_isRunning = true;
    std::cout << "Ecoute sur le port : " << GREEN << this->_port << RESET << std::endl;
}

void    webServ::handleConnection()
{
    // Boucle d'attente de connexion, puis instruction.
    // Voir pour utiliser poll() ici avec un objet client pour chaque client.
    while (this->_isRunning)
    {
        std::cout << "En attente de connexion .." << std::endl;
        int clientSocket;
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        clientSocket = accept(this->_socketServer, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == -1)
        {
            throw std::runtime_error("Error : Failed to accept the connection");
            continue;
        }
        std::cout << "Connexion du client : " << GREEN << inet_ntoa(clientAddr.sin_addr) << RESET << std::endl;
        send(clientSocket, "Rentre ton pseudo : ", 21, 0);
        char buff[2048];
        int len = recv(clientSocket, buff, sizeof(buff), 0);
        buff[len] = '\0';
        std::string message = "Bienvenue sur webserv ";
        message = message + buff;
        send(clientSocket, message.c_str(), message.size(), 0);

        close(clientSocket);
    }
        close(_socketServer);
}