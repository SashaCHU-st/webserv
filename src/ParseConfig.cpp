/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseConfig.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:15:03 by alli              #+#    #+#             */
/*   Updated: 2024/12/31 13:51:00 by alli             ###   ########.fr       */
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
			if (!currentConfig.server.empty())
				_serverConfig[currentConfig.server].push_back(currentConfig); //creates new server in map
			currentConfig = configServer(); //resets for the next server
			if (element.find("port"))
			{
				//check if there is already a port
				std::vector<std::string> tokens = Utils::splitStr(element, "=");
				if (tokens.size() == 2)
					currentConfig.port = tokens[1];
			}
			else if (element.find("ipAddress"))
			{
				//check if there is already an IPaddress
				std::vector<std::string> tokens = Utils::splitStr(element, "="); //uses local scope
				if (tokens.size() == 2)
					currentConfig.ipAddress = tokens[1];
				std::cout << currentConfig.ipAddress << std::endl;
			}
			else if(element.find("server_name"))
			{
				std::vector<std::string> tokens = Utils::splitStr(element, "=");
				if (tokens.size() == 2)
					currentConfig.server_name = tokens[1];
			}
			else if (element.find("methods"))
			{
				std::vector<std::string> tokens = Utils::splitStr(element, "=");
				if (tokens.size() >= 2 && tokens.size() <= 4)
				{
					if (tokens.size() == 2)
						currentConfig.methods.push_back(tokens[1]);
					else
					{
						currentConfig.methods = Utils::splitStr(tokens[1], " "); // some more parsing here to make sure it's GET POST and DELETE
						std::cout << currentConfig.methods << std::endl;
					}
				}
			}
			if (element.empty())
				return;
			//find location here
		}
		if (!currentConfig.server.empty())
			_serverConfig[currentConfig.server].push_back(currentConfig);
	}
}

int main(int argv, char **arv)
{
	
}