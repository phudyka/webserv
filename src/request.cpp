/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:01:53 by dtassel           #+#    #+#             */
/*   Updated: 2024/03/01 14:51:42 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/request.hpp"

Request::Request(int socket, const std::string &clientIP, const std::string &request)
{
    this->_socketClient = socket;
    this->_clientIP = clientIP;
    this->_requestClient = request;
}

Request::Request(const Request& src)
{
    *this = src;
}

Request& Request::operator=(const Request& src)
{
    if (this != &src)
    {
        this->_socketClient = src._socketClient;
        this->_clientIP = src._clientIP;
        this->_requestClient = src._requestClient;
    }
    return *this;
}

Request::~Request()
{
    
}

void	Request::removeSpace(std::string &src)
{
    src.erase(0, src.find_first_not_of(" \t\r\n"));
    src.erase(src.find_last_not_of(" \t\r\n") + 1);
}

int		Request::extractLength(std::string src)
{
    int i = 0;
    removeSpace(src);
    while (src[i])
    {
        if (src[i] >= '0' && src[i] <= '9')
            i++;
        else
            return -1;
    }
    if (i > 0)
    {
        int nb = atoi(src.c_str());
        return nb;
    }
    return -1;
}

int		Request::analyzeGET()
{
    std::ifstream iss(this->_requestClient.c_str());

    std::string line;
    std::getline(iss, line);
    int countLine = 1; 
    while(std::getline(iss, line))
    {
        countLine++;
        if (countLine == 2 && line.find("Host:") != std::string::npos)
        {
            size_t afterHost = line.find("Host:") + 6;
            size_t urlStart = line.find(" \t", afterHost);
            if (line.size() != urlStart)
            {
                this->_url = line.substr(urlStart);
                removeSpace(this->_url);
            }
            else
                return -1;
        }
        else if (countLine == 3 && line.find("User-Agent:") != std::string::npos)
        {
            return 1;
        }
        else if (countLine == 4)
            break;
    }
    return -1;
}

int Request::analyzePOST()
{
    std::ifstream iss(this->_requestClient.c_str());

    std::string line;
    std::getline(iss, line);
    int countLine = 1;
    while (std::getline(iss, line))
    {
        countLine++;
        if (countLine == 2 && line.find("Host:") != std::string::npos)
            continue;
        else if (countLine == 3 && line.find("User-Agent:") != std::string::npos)
        {
            continue;
        }
        else if (countLine == 4 && line.find("Content-type:") != std::string::npos)
            continue;
        else if (countLine == 5 && line.find("Content-length:") != std::string::npos)
        {
            size_t  afterHost = line.find("Content-length:") + 16;
            size_t  lengthStart = line.find(" \t", afterHost);
            if (line.size() != lengthStart)
            {
                this->_contentLength = extractLength(line.substr(lengthStart));
                if (this->_contentLength == -1)
                    return -1;
            }
            else
                return -1;
        }
        else if (countLine == 6)
            return 2;
    }
    return -1;
}

int    Request::analyzeRequest()
{
    int ret = -1;
    std::ifstream   iss(this->_requestClient.c_str());

    std::string line;
    std::getline(iss, line);
    if (line.find("GET") != std::string::npos && line.find("HTTP/1.1"))
    {
        ret = analyzeGET();
    }
    else if(line.find("POST") != std::string::npos && line.find("HTTP/1.1"))
    {
        ret = analyzePOST();
    }
    return ret;
}

int	Request::responseGet()
{
    std::ifstream file(this->_url.c_str());
    if (!file.is_open())
    {
        std::cerr << "Impossible d'ouvrir le fichier html" << std::endl;
        return -1;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string htmlContent = buffer.str();

    std::stringstream response;
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-type : text/html\r\n";
    response << "Content-length" << htmlContent.size() << "\r\n";
    response << htmlContent;

    this->_responseClient = response.str();
    return 200;
}

void	Request::sendResponseToClient()
{
    send(_socketClient, _responseClient.c_str(), _responseClient.size(), 0);
}

void Request::handleRequest() {
    int retCode = 0;

    retCode = analyzeRequest();
    switch (retCode)
    {
        case 1:
            retCode = responseGet();
            break;
        case 2:

            break;
        default:
            retCode = 400;
            break;
    }

    switch (retCode)
    {
        case 200:
            sendResponseToClient();
            break;
        case 404:
            break;
        case 400:
            break;
        default:
            break;
    }
}
