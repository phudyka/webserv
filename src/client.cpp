/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:10:57 by dtassel           #+#    #+#             */
/*   Updated: 2024/02/29 09:14:04 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/client.hpp"

Client::Client(int socket, const std::string adressIp)
{
    this->_socket = socket;
    this->_adressIp = adressIp;
    this->_isConnected = true;
}

Client::Client(const Client& src)
{
    // Constructeur de copie
}

Client& Client::operator=(const Client& src)
{
    // Surcharge de l'opérateur d'affectation
    return *this;
}

Client::~Client()
{
    // Destructeur
}