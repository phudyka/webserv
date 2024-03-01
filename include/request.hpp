/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 09:57:20 by dtassel           #+#    #+#             */
/*   Updated: 2024/03/01 14:32:28 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "webserv.hpp"

class Request
{
public:
	Request(int socket, const std::string &clientIP, const std::string &request);
	Request(const Request& src);
	Request& operator=(const Request& src);
	~Request();
	void	handleRequest();
	int		analyzeRequest();
	int		analyzeGET();
	int		analyzePOST();
	void	removeSpace(std::string &src);
	int		extractLength(std::string src);
	int		responseGet();
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