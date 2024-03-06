/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:23:11 by phudyka           #+#    #+#             */
/*   Updated: 2024/03/05 15:50:33 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

static int isConfigFile(const std::string& filename)
{
    return (filename.length() >= 5 && std::strcmp(filename.c_str() + filename.length() - 5, ".conf") == 0);
}

int	parseConfig(const std::string& configFile, ServerConfig& serverConfig)
{
    if (!isConfigFile(configFile))
    {
        std::cerr << RED << "Invalid configuration file: " << configFile << RESET << std::endl;
        return (1);
    }

    FILE* file = fopen(configFile.c_str(), "r");
    if (!file)
    {
        std::cerr << RED << "Error opening configuration file: " << configFile << RESET << std::endl;
        return (1);
    }

    char	buffer[1024];
    while (fgets(buffer, sizeof(buffer), file))
    {
        std::string	key;
        std::string	value;
        if (sscanf(buffer, "%s %s", buffer, buffer) == 2)
        {
            key = buffer;
            value = buffer;
            if (key == "port")
            {
                int	port = std::atoi(value.c_str());
                if (port <= 0 || port > 65535)
                {
                    std::cerr << RED << "Invalid port number in configuration file: " << configFile << RESET << std::endl;
                    fclose(file);
                    return (1);
                }
                serverConfig.port = port;
            }
            else if (key == "host")
                serverConfig.host = value;
            else if (key == "server_name")
                serverConfig.serverNames.push_back(value);
        }
    }
    fclose(file);
    return (0);
}