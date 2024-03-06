/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 06:53:43 by phudyka           #+#    #+#             */
/*   Updated: 2024/03/05 15:39:40 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

webServ	*globalInstance = NULL;

static void	signalHandler(int sig)
{
	if (globalInstance)
		globalInstance->shutDown();
	exit (sig);
}

int main(int argc, char **argv)
{
    if (argc == 2)
	{
        ServerConfig	serverConfig;
	
        if (!parseConfig(argv[1], serverConfig))
            return (EXIT_FAILURE);
        try
		{
            globalInstance = new webServ(serverConfig.port);
            signal(SIGINT, signalHandler);

            globalInstance->start();
            globalInstance->firstConnection();
        }
		catch (const std::exception& e)
		{
            std::cerr << e.what() << '\n';
            exit(EXIT_FAILURE);
        }
        delete (globalInstance);
        return (EXIT_SUCCESS);
    }
	else
	{
        std::cout << RED << "Error : [Bad arguments] './webserv + configFile'" << RESET << std::endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_FAILURE);
}