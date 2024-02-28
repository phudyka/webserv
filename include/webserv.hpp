/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:56:25 by dtassel           #+#    #+#             */
/*   Updated: 2024/02/28 11:28:34 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"

class webServ
{
public:
    webServ(int port);
    ~webServ();
    void    start();
    void    handleConnection();
private:
    int         _socketServer;
    int         _port;
    std::string _rootDirectory;
    bool        _isRunning;
    struct sockaddr_in _serverAddr;
};

#endif