/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:05:47 by dtassel           #+#    #+#             */
/*   Updated: 2024/02/29 11:10:11 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "webserv.hpp"

class Client
{
public:
    Client(int socket, const std::string &adressIp);
    Client(const Client& src);
    Client& operator=(const Client& src);
    ~Client();
    int                 getSocket();
    const std::string   getAdIP();
    bool                getState();
    void                disconnect();
private:
    int         _socket;
    std::string _adressIp;
    bool        _isConnected;
};

#endif