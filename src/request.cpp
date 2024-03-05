/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:01:53 by dtassel           #+#    #+#             */
/*   Updated: 2024/03/05 10:33:38 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/request.hpp"

Request::Request(int socket, const std::string &clientIP, const std::string &request)
{
    this->_socketClient = socket;
    this->_clientIP = clientIP;
    this->_requestClient = request;
    std::cout << "Socket client : " << socket << " Adress ip : " << clientIP << std::endl;
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
    return (*this);
}

Request::~Request() {}

void	Request::removeSpace(std::string &src)
{
    src.erase(0, src.find_first_not_of(" \t\r\n"));
    src.erase(src.find_last_not_of(" \t\r\n") + 1);
}

int	Request::extractLength(std::string src)
{
    int i = 0;

    removeSpace(src);
    while (src[i])
    {
        if (src[i] >= '0' && src[i] <= '9')
            i++;
        else
            return (-1);
    }
    if (i > 0)
    {
        int nb = atoi(src.c_str());
        return (nb);
    }
    return (-1);
}

int Request::analyzeGET() {
    std::istringstream iss(this->_requestClient);
    int countLine = 0; 
    std::string line;

    while(std::getline(iss, line))
    {
        if (countLine == 0 && line.find("GET") != std::string::npos && line.find("HTTP/1.1") != std::string::npos) {
            size_t urlStart = line.find('/') + 1;
            size_t urlEnd = line.find(" HTTP/1.1");
            this->_url = line.substr(urlStart, urlEnd - urlStart);
            if (this->_url.empty())
                this->_url = "html/Webserv.html";
            else
                this->_url = "html/error_404.html";
        }
        countLine++;
    }
    if (countLine == 0)
        return E400;
    return (E200);
}


int Request::responseGET()
{
    std::ifstream file(this->_url.c_str());
    if (!file.is_open()) 
    {
        std::cerr << "Impossible d'ouvrir le fichier HTML" << std::endl;
        return E404;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string htmlContent = buffer.str();

    std::stringstream response;
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-type: text/html\r\n";
    response << "Content-length: " << htmlContent.size() << "\r\n";
    response << "\r\n";
    response << htmlContent;

    this->_responseClient = response.str();

    return E200;
}

void	Request::sendResponseToClient()
{
    send(_socketClient, _responseClient.c_str(), _responseClient.size(), 0);
}

int	Request::analyzePOST()
{
    std::istringstream iss(this->_requestClient);
    std::string line;
    int contentLength = -1;

    while (std::getline(iss, line))
    {
        if (line.find("Content-Length:") != std::string::npos)
        {
            size_t contentLengthPos = line.find(":") + 1;
            std::string lengthStr = line.substr(contentLengthPos);
            bool validLength = true;
            for (size_t i = 0; i < lengthStr.size(); ++i)
            {
                if (!isdigit(lengthStr[i]))
                {
                    validLength = false;
                    break;
                }
            }
            if (validLength)
            {
                contentLength = atoi(lengthStr.c_str());
                break;
            }
            else
                return -1;
        }
    }
    if (contentLength != -1)
        return 2;
    else
        return -1;
}

void	Request::generateResponse()
{
    if (_statusCode == GET)
        responseGET();
    else if (_statusCode == POST)
        responsePost();
    else if (_statusCode == DELETE)
        responseDelete();
    else
        responseError();
}

int Request::parseRequest()
{
    std::istringstream iss(this->_requestClient);
    std::string line;
    std::getline(iss, line);

    if (line.find("GET") != std::string::npos && line.find(" /") != std::string::npos && line.find("HTTP/1.1") != std::string::npos)
        return analyzeGET();
    else if(line.find("POST") != std::string::npos && line.find("HTTP/1.1") != std::string::npos)
        return analyzePOST();
    else
        return E400;
}

void Request::handleRequest()
{
    _statusCode = parseRequest();
    generateResponse();
    sendResponseToClient();
}