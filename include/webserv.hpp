/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:56:25 by dtassel           #+#    #+#             */
/*   Updated: 2024/02/29 10:59:58 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# define FD_MAX	1024

#include <string>
#include <poll.h>
#include <vector>
#include <netdb.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

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
	struct	pollfd
	{
		int		fd;
		short	events;
		short	revents;
	};
	std::vector<struct pollfd> _pollfds;
	void	handleNewConnection();
    void	closeClientData(int clientSocket);
    void	removeClient(int index);
};


#endif