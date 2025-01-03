#ifndef PARSECONFIG_HPP
#define PARSECONFIG_HPP

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <fstream>
#include <filesystem>
#include "Utils.hpp"

struct configServer {
	std::string			server;
	std::string			port;
	std::string			ipAddress;
	std::string			server_name;
	std::vector<std::string> methods;
	std::string			index = "index.html";
};

class ParseConfig {
	private:
		std::string							_contentStr;
		std::vector<std::string>			_elements;
		std::map<std::string, std::vector<configServer>>	_serverConfig; //string as key for which server and stores struct of information to that vector
	public:
		ParseConfig();
		// ParseConfig(const std::string);
		~ParseConfig();
		// std::map<std::string, std::string> configElements(std::vector<std::string> fromSplit);
		void splitConfigElements(const std::string configFile);
		std::map<std::string, std::vector<configServer>> server_getter();
};


#endif