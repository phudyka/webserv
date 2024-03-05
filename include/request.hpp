/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 09:57:20 by dtassel           #+#    #+#             */
/*   Updated: 2024/03/05 10:08:40 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "webserv.hpp"

// METHODES
#define GET			1
#define POST		2
#define DELETE		3

// ERROR CODE
# define E200		200 // Success
# define E301		301
# define E302		302
# define E400		400
# define E401		401
# define E403		403
# define E404		404
# define E500		500
# define E502		502
# define E503		503
# define E504		504

class Request
{
public:
	Request(int socket, const std::string &clientIP, const std::string &request);
	Request(const Request& src);
	Request& operator=(const Request& src);
	~Request();
	void	handleRequest();
	int		parseRequest();
	void	generateResponse();
	int		analyzeGET();
	int		analyzePOST();
	void	removeSpace(std::string &src);
	int		extractLength(std::string src);
	int		responseGet();
	int		responseError();
	void	sendResponseToClient();
private:
	int _statusCode;
	int _socketClient;
	std::string _clientIP;
	std::string _requestClient;
	std::string _responseClient;

	std::string _url;
	int			_contentLength;
};

#endif