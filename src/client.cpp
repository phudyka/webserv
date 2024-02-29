/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:10:57 by dtassel           #+#    #+#             */
/*   Updated: 2024/02/29 11:10:29 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/client.hpp"

Client::Client(int socket, const std::string &adressIp)
{
	this->_socket = socket;
	this->_adressIp = adressIp;
	this->_isConnected = true;
}

Client::Client(const Client& src)
{
	*this = src;
}

Client& Client::operator=(const Client& src)
{
	if (this != &src)
	{
		this->_socket = src._socket;
		this->_adressIp = src._adressIp;
		this->_isConnected = src._isConnected;
	}
	return *this;
}

Client::~Client()
{
	close(this->_socket);
	std::cout << "Client : " << _adressIp << " disconnected" << std::endl;
}

int Client::getSocket()
{
	return this->_socket;
}

const std::string Client::getAdIP()
{
	return this->_adressIp;
}

bool Client::getState()
{
	return this->_isConnected;
}

void Client::disconnect()
{
	this->_isConnected = false;
}