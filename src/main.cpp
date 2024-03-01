/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 06:53:43 by phudyka           #+#    #+#             */
/*   Updated: 2024/03/01 16:16:18 by phudyka          ###   ########.fr       */
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

int main(void)
{
    try
	{
        globalInstance = new webServ(PORT);
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