/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:28:41 by alli              #+#    #+#             */
/*   Updated: 2025/01/03 10:00:36 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Launching.hpp"
#include "ParseConfig.hpp"

// int main(int argc, char **argv)
// {
// 	std::string configFile = "test.conf";

//     try {
// 		if (argc == 2)
// 		{
// 			ParseConfig::splitConfigElements(configFile);
// 		}
//     	Launching webserv;
//     }
//     catch(std::exception& e)
//     {
//         std::cout << e.what() << std::endl;
//         return 1;
//     }
//     return 0;
// }
int main(int argc, char **argv)
{
	ParseConfig config;
	if (argc == 2)
	{
		std::string	file = argv[1];
		config.splitConfigElements(file);
	}
}