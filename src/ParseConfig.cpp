/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseConfig.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:15:03 by alli              #+#    #+#             */
/*   Updated: 2025/01/03 11:01:07 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseConfig.hpp"
#include "Utils.hpp"

ParseConfig::ParseConfig() {};
ParseConfig::~ParseConfig() {};

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
		std::vector<std::string> splitElements = Utils::splitStr(_contentStr, "\n");
		ParseConfig::_elements.insert(ParseConfig::_elements.end(), splitElements.begin(), splitElements.end());
	}
	for (const auto& element : ParseConfig::_elements) // iterate through the vector
	{
		// std::cout << element << std::endl;
		if (element.find("[server]")) //element == "[server]"
		{
			// std::cout << element << std::endl;
			if (!currentConfig.server.empty())
				_serverConfig[currentConfig.server].push_back(currentConfig); //creates new server in map
			currentConfig = configServer(); //resets for the next server
			//find location here
		}
		if (element.find("port") == 0)
		{
			//check if there is already a port
			std::cout << "element in port: " << element << std::endl;
			std::vector<std::string> tokens = Utils::splitStr(element, "=");
			if (tokens.size() == 2)
				currentConfig.port = tokens[1];
			std::cout << "port: " << currentConfig.port << std::endl;
			continue;
		}
		if (element.find("ipAddress") == 0)
		{
			//check if there is already an IPaddress
			std::cout << "element in ipaddress: " << element << std::endl;
			std::vector<std::string> tokens = Utils::splitStr(element, "="); //uses local scope
			if (tokens.size() == 2)
				currentConfig.ipAddress = tokens[1];
			std::cout << "ip address: " << currentConfig.ipAddress << std::endl;
		}
		if (element.find("server_name") == 0)
		{
			std::cout << "element in server_name: " << element << std::endl;
			std::vector<std::string> tokens = Utils::splitStr(element, "=");
			if (tokens.size() == 2)
				currentConfig.server_name = tokens[1];
			std::cout << "server_name: " << currentConfig.server_name << std::endl;
		}
		if (element.find("methods"))
		{
			std::vector<std::string> tokens = Utils::splitStr(element, "=");
			if (tokens.size() >= 2 && tokens.size() <= 4)
			{
				if (tokens.size() == 2)
					currentConfig.methods.push_back(tokens[1]);
				else
				{
					currentConfig.methods = Utils::splitStr(tokens[1], " "); // some more parsing here to make sure it's GET POST and DELETE
					for (unsigned long i = 0; i < currentConfig.methods.size(); i++)
					std::cout << "method " << i << " : " << currentConfig.methods[i] << std::endl;
				}
			}
		}
		if (element.empty())
			return;
		if (!currentConfig.server.empty())
			_serverConfig[currentConfig.server].push_back(currentConfig);
	}
}

// int main(int argv, char **arv)
// {
// 	ParseConfig config;
// 	std::string	file = arv[1];
// 	config.splitConfigElements(file);
// }