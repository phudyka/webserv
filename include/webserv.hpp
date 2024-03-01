/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:56:25 by dtassel           #+#    #+#             */
/*   Updated: 2024/03/01 11:13:08 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# define FD_MAX		1024
# define PORT		30000
# define MAX_EVENT	10

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
#include "../include/client.hpp"

#define RED		"\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE	"\x1b[34m"
#define PURPLE	"\x1b[35m"
#define RESET   "\x1b[0m"


class	webServ
{

public:
    webServ(int port);
    ~webServ();
    void    start();
    void    firstConnection();

private:
    int         _socketServer;
    int         _port;
    std::string	_rootDirectory;
    bool		_isRunning;
    struct sockaddr_in _serverAddr;
	struct	WebServPollfd
	{
		int		fd;
		short	events;
		short	revents;
	};

	// std::vector<Client>			_clients;
	std::vector<struct pollfd>	_pollfds;

	void	newConnection();
    void	closeClientData(int clientSocket);
    void	removeClient(int index);
	void	clientData(size_t index);
	void	logConnection(const std::string& msg, const std::string id);
};

#endif