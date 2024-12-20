/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseConfig.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:15:03 by alli              #+#    #+#             */
/*   Updated: 2024/12/20 14:15:15 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseConfig.hpp"
#include "Utils.hpp"

void ParseConfig::splitConfigElements(const std::string configFile)
{
	std::vector<configServer> keyValues;
	
	std::ifstream file(configFile);
	if (!file.is_open()) {
		std::cout << "Configuration file not able to be opened" << std::endl;
		return ;
	}
	while (std::getline(file, _contentStr))
	{
		if (_contentStr.empty())
			continue;
	}
	for (int i = 0; i < _contentStr.length(); i++) // iterate through the vector
	{
		if (_contentStr.find("[server]") != std::string::npos)
		{
			_serverConfig.insert()
			if (_contentStr.find("port"))
			{
				
			}
		}
		keyValues = Utils::splitStr(_elements[i], "=");
		if (keyValues.size() == 2)
		{
			_serverConfig[keyValues[0]] = keyValues[1];
		}
		//split into key and value
		//if key = server, save to struct?
		//if port then 8080 
		//
	}
}