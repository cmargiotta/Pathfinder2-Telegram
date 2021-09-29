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
	static bool parsed = false; 

	if (!parsed)
	{
		parsed = true;
		std::cout << "Installed languages: ";

		for (auto& file: directory_iterator("/usr/share/inventory_bot/localization_data/"))
		{
			string path = file.path();
			string lang = path.substr(path.size()-7, 2);
			languages.insert(lang);
		}

		for (auto& lang: languages)
		{
			std::cout << lang << ' ';
		}

		std::cout << '\n';
	}

	return languages;
}

const std::string& pathfinder2::get_command(const std::string& key, const std::string& locale)
{
	static std::string default_locale = getenv("PF2_INV_LANG");
	static map<string, map<string, string>> commands;
	static bool init = false;

	if (!init)
	{
		for (auto& l: parse_installed_languages())
		{
			nlohmann::json commands_json;
			std::ifstream(std::string("/usr/share/inventory_bot/localization_data/commands_") + l + ".json") >> commands_json;

			for (auto i = commands_json.begin(); i != commands_json.end(); ++i)
			{
				commands[l][i.key()] = i.value();
			}
		}
	}

	try 
	{
		return commands[(locale == "") ? default_locale : locale].at(key);
	}
	catch(...)
	{
		return key;
	}
}

const std::string& pathfinder2::get_command_id(const std::string& key, const std::string& locale)
{
	static std::string default_locale = getenv("PF2_INV_LANG");
	static map<string, map<string, string>> commands;
	static bool init = false;

	if (!init)
	{
		for (auto& l: parse_installed_languages())
		{
			nlohmann::json commands_json;
			std::ifstream(std::string("/usr/share/inventory_bot/localization_data/commands_") + l + ".json") >> commands_json;

			for (auto i = commands_json.begin(); i != commands_json.end(); ++i)
			{
				commands[l][i.value()] = i.key();
			}
		}

		init = true;
	}

	try 
	{
		return commands[(locale == "") ? default_locale : locale].at(key);
	}
	catch(...)
	{
		return key;
	}
}

const std::string& pathfinder2::get_message(const std::string& key, const std::string& locale)
{
	static std::string default_locale = getenv("PF2_INV_LANG");
	static map<string, map<string, string>> messages;
	static bool init = false;

	if (!init)
	{
		for (auto& l: parse_installed_languages())
		{	
			nlohmann::json message_json;
			std::ifstream(std::string("/usr/share/inventory_bot/localization_data/messages_") + l + ".json") >> message_json;

			for (auto i = message_json.begin(); i != message_json.end(); ++i)
			{
				messages[l][i.key()] = i.value();
			}
		}

		init = true;
	}

	try 
	{
		return messages[(locale == "") ? default_locale : locale].at(key);
	}
	catch(...)
	{
		return key;
	}
}

const std::string& pathfinder2::get_message_id(const std::string& key, const std::string& locale)
{
	static std::string default_locale = getenv("PF2_INV_LANG");
	static map<string, map<string, string>> messages_ids;
	static bool init = false;

	if (!init)
	{
		for (auto& l: parse_installed_languages())
		{
			nlohmann::json message_json;
			std::ifstream(std::string("/usr/share/inventory_bot/localization_data/messages_") + l + ".json") >> message_json;

			for (auto i = message_json.begin(); i != message_json.end(); ++i)
			{
				messages_ids[l][i.value()] = i.key();
			}
		}

		init = true;
	}

	return messages_ids[(locale == "") ? default_locale : locale].at(key);
}