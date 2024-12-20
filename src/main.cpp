/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:28:41 by alli              #+#    #+#             */
/*   Updated: 2024/12/17 13:39:25 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Launching.hpp"
#include "ParseConfig.hpp"

int main(int argc, char **argv)
{
	std::string configFile = "test.conf";

    try {
		if (argc == 2)
		{
			ParseConfig::splitConfigElements(configFile);
		}
    	Launching webserv;
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
