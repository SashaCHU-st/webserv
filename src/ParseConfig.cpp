/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseConfig.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:15:03 by alli              #+#    #+#             */
/*   Updated: 2024/12/30 14:57:11 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseConfig.hpp"
#include "Utils.hpp"

void ParseConfig::splitConfigElements(const std::string configFile)
{
	configServer currentConfig;
	
	std::ifstream file(configFile);
	if (!file.is_open()) {
		std::cout << "Configuration file not able to be opened" << std::endl;
		return ;
	}
	while (std::getline(file, _contentStr))
	{
		if (_contentStr.empty())
			continue;
		ParseConfig::_elements = Utils::splitStr(_contentStr, "\n");
	}
	for (const auto& element : _elements) // iterate through the vector
	{
		if (element.find("[server]") != std::string::npos)
		{
			_serverConfig[currentConfig.server].push_back(currentConfig); //creates new server in map
			currentConfig = configServer(); //resets for the next server
			if (element.find("port"))
			{
				std::vector<std::string> tokens = Utils::splitStr(element, "=");
				if (tokens.size() == 2)
					currentConfig.port = tokens[1];
			}
			else if (element.find("ipAddress"))
			{
				std::vector<std::string> tokens = Utils::splitStr(element, "="); //uses local scope
				if (tokens.size() == 2)
					currentConfig.ipAddress = tokens[1];
			}
			//repeat for all structs
			//find location here
			
		}
		currentConfig.server.empty()
		// keyValues = Utils::splitStr(_elements[i], "=");
		//split into key and value
		//if key = server, save to struct?
		//if port then 8080 
		//
	}
}