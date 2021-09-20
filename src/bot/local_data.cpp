#include "local_data.hpp"

#include <set>
#include <map>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <filesystem>

using std::map;
using std::set;
using std::string;
using std::filesystem::directory_iterator;

set<string> parse_installed_languages()
{
	static set<string> languages;
	bool parsed = false; 

	if (!parsed)
	{
		parsed = true;
		std::cout << "Installed languages: ";

		for (auto& file: directory_iterator("/usr/share/inventory_bot/localization_data/"))
		{
			string path = file.path();
			string lang = path.substr(path.size()-7, path.size()-5);
			languages.insert(lang);

			std::cout << lang << " ";
		}

		std::cout << '\n';
	}
	
	return languages;
}

nlohmann::json& pathfinder2::get_commands(const std::string& locale)
{
	static std::string default_locale = getenv("PF2_INV_LANG");
	static map<string, nlohmann::json> commands;
	static bool init = false;

	if (!init)
	{
		for (auto& l: parse_installed_languages())
		{	
			std::ifstream(std::string("/usr/share/inventory_bot/localization_data/commands_") + l + ".json") >> commands[l];
		}

		init = true;
	}

	return commands[(locale == "") ? default_locale : locale];
}

nlohmann::json& pathfinder2::get_messages(const std::string& locale)
{
	static std::string default_locale = getenv("PF2_INV_LANG");
	static map<string, nlohmann::json> messages;
	static bool init = false;

	if (!init)
	{
		for (auto& l: parse_installed_languages())
		{	
			std::ifstream(std::string("/usr/share/inventory_bot/localization_data/messages_") + l + ".json") >> messages[l];
		}

		init = true;
	}

	return messages[(locale == "") ? default_locale : locale];
}