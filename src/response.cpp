/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:48:41 by phudyka           #+#    #+#             */
/*   Updated: 2024/03/05 10:49:05 by phudyka          ###   ########.fr       */
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
            errorContent = "<html><head><title>301 Moved Permanently</title></head><body><h1>301 Moved Permanently</h1><p>The requested resource has been permanently moved to a new URL.</p></body></html>";
            break ;
        case (E302):
            response << RED << "HTTP/1.1 302 Found\r\n" << RESET;
            errorContent = "<html><head><title>302 Found</title></head><body><h1>302 Found</h1><p>The requested resource has been found, but it has been temporarily moved to another URL. Please try again.</p></body></html>";
            break ;
        case (E400):
            response << RED << "HTTP/1.1 400 Bad Request\r\n" << RESET;
            errorContent = "<html><head><title>400 Bad Request</title></head><body><h1>400 Bad Request</h1><p>The client's request is malformed or incorrect.</p></body></html>";
            break ;
        case (E401):
            response << RED << "HTTP/1.1 401 Unauthorized\r\n" << RESET;
            errorContent = "<html><head><title>401 Unauthorized</title></head><body><h1>401 Unauthorized</h1><p>You do not have the necessary permissions to access this resource. Please log in or provide valid credentials.</p></body></html>";
            break ;
        case (E403):
            response << RED << "HTTP/1.1 403 Forbidden\r\n" << RESET;
            errorContent = "<html><head><title>403 Forbidden</title></head><body><h1>403 Forbidden</h1><p>Forbidden access. You do not have the required permissions to access this resource.</p></body></html>";
            break ;
        case (E404):
            response << RED << "HTTP/1.1 404 Not Found\r\n" << RESET;
            errorContent = "<html><head><title>404 Not Found</title></head><body><h1>404 Not Found</h1><p>The page you are looking for could not be found.</p></body></html>";
            break ;
        case (E500):
            response << RED << "HTTP/1.1 500 Internal Server Error\r\n" << RESET;
            errorContent = "<html><head><title>500 Internal Server Error</title></head><body><h1>500 Internal Server Error</h1><p>An internal server error occurred. Please try again later.</p></body></html>";
            break ;
        case (E502):
            response << RED << "HTTP/1.1 502 Bad Gateway\r\n" << RESET;
            errorContent = "<html><head><title>502 Bad Gateway</title></head><body><h1>502 Bad Gateway</h1><p>The server is acting as a gateway or proxy and received an invalid response from the upstream server.</p></body></html>";
            break ;
        case (E503):
            response << RED << "HTTP/1.1 503 Service Unavailable\r\n" << RESET;
            errorContent = "<html><head><title>503 Service Unavailable</title></head><body><h1>503 Service Unavailable</h1><p>The server is not ready to handle the request. Common causes include temporary overload, server maintenance, or planned unavailability.</p></body></html>";
            break ;
        case (E504):
            response << RED << "HTTP/1.1 504 Gateway Timeout\r\n" << RESET;
            errorContent = "<html><head><title>504 Gateway Timeout</title></head><body><h1>504 Gateway Timeout</h1><p>The server, acting as a gateway or proxy, did not receive a timely response from the upstream server or any other source needed to fulfill the request.</p></body></html>";
            break ;
        default:
            response << RED << "HTTP/1.1 500 Internal Server Error\r\n" << RESET;
            errorContent = "<html><head><title>500 Internal Server Error</title></head><body><h1>500 Internal Server Error</h1><p>An internal server error occurred. Please try again later.</p></body></html>";
            break ;
    }
    
    response << "Content-type: text/html\r\n";
    response << "Content-length: " << errorContent.size() << "\r\n";
    response << "\r\n";
    response << errorContent;

    this->_responseClient = response.str();
    std::cout << this->_responseClient << std::endl;

    return (_statusCode);
}