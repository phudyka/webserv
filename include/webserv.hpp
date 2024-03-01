/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:56:25 by dtassel           #+#    #+#             */
/*   Updated: 2024/03/01 14:41:55 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# define FD_MAX		1024
# define PORT		30000
# define MAX_EVENT	10

#include <iostream>
#include <string>
#include <poll.h>
#include <vector>
#include <fcntl.h>
#include <netdb.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "../include/client.hpp"
#include "../include/request.hpp"

#define RED		"\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW	"\x1b[33m"
#define BLUE	"\x1b[34m"
#define PURPLE	"\x1b[35m"
#define RESET   "\x1b[0m"

class	Client;
class	webServ
{

public:
    webServ(int port);
    ~webServ();
    void    start(void);
    void    firstConnection(void);

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

	std::vector<struct pollfd>	_pollfds;
	std::vector<Client> _clients;

	void	newConnection(void);
    void	closeClientData(int clientSocket);
    void	removeClient(size_t index);
	void	clientData(size_t index);
	void	logConnection(const std::string& msg, const std::string id);
};

#endif