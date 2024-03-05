/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:48:41 by phudyka           #+#    #+#             */
/*   Updated: 2024/03/05 10:21:29 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/request.hpp"

int Request::responseError()
{
    std::stringstream	response;
    std::string			errorContent;

    switch (_statusCode)
    {
        case (E301):
            response << RED << "HTTP/1.1 301 Moved Permanently\r\n" << RESET;
            errorContent = "[The requested resource has been permanently moved to a new URL.]";
            break;

        case (E302):
            response << RED << "HTTP/1.1 302 Found\r\n" << RESET;
            errorContent = "[The requested resource has been found, but it has been temporarily moved to another URL. Please try again.]";
            break;

        case (E400):
            response << RED << "HTTP/1.1 400 Bad Request\r\n" << RESET;
            errorContent = "[The client's request is malformed or incorrect.]";
            break;

        case (E401):
            response << RED << "HTTP/1.1 401 Unauthorized\r\n" << RESET;
            errorContent = "[You do not have the necessary permissions to access this resource. Please log in or provide valid credentials.]";
            break;

        case (E403):
            response << RED << "HTTP/1.1 403 Forbidden\r\n" << RESET;
            errorContent = "[Forbidden access. You do not have the required permissions to access this resource.]";
            break;

        case (E404):
            response << RED << "HTTP/1.1 404 Not Found\r\n" << RESET;
            errorContent = "[The page you are looking for could not be found.]";
            break;

        case (E500):
            response << RED << "HTTP/1.1 500 Internal Server Error\r\n" << RESET;
            errorContent = "[An internal server error occurred. Please try again later.]";
            break;

        case (E502):
            response << RED << "HTTP/1.1 502 Bad Gateway\r\n" << RESET;
            errorContent = "[The server is acting as a gateway or proxy and received an invalid response from the upstream server.]";
            break;

        case (E503):
            response << RED << "HTTP/1.1 503 Service Unavailable\r\n" << RESET;
            errorContent = "[The server is not ready to handle the request. Common causes include temporary overload, server maintenance, or planned unavailability.]";
            break;

        case (E504):
            response << RED << "HTTP/1.1 504 Gateway Timeout\r\n" << RESET;
            errorContent = "[The server, acting as a gateway or proxy, did not receive a timely response from the upstream server or any other source needed to fulfill the request.]";
            break;

        default:
            response << RED << "HTTP/1.1 500 Internal Server Error\r\n" << RESET;
            errorContent = "[An internal server error occurred. Please try again later.]";
            break;
    }

    response << ORANGE << "Content-type: text/html\r\n" << RESET;
    response << "Content-length: " << errorContent.size() << "\r\n";
    response << "\r\n";
    response << errorContent;

    this->_responseClient = response.str();
    std::cout << "Error Response: " << this->_responseClient << std::endl;

    return (_statusCode);
}