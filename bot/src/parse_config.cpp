// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <map>

std::map<std::string, std::string> parse_config(const std::string &path_to_config)
{
	std::fstream cfg(path_to_config);
	std::map<std::string, std::string> config_map;
	std::string line;

	while (cfg >> line)
	{
		size_t to_symbol = line.find('=');
		if (to_symbol != std::string::npos)
		{
			std::string key = line.substr(0, to_symbol);
			std::string value = line.substr(to_symbol + 1);
			config_map.insert(std::make_pair(key, value));
		}
	}

	return config_map;
}