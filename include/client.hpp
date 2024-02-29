/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:05:47 by dtassel           #+#    #+#             */
/*   Updated: 2024/02/29 09:16:01 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <iostream>

class Client
{
public:
    Client(int socket, const std::string adressIp);
    Client(const Client& src);
    Client& operator=(const Client& src);
    ~Client();
private:
    int         _socket;
    std::string _adressIp;
    bool        _isConnected;
};

#endif