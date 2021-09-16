#include "local_data.hpp"

#include <fstream>
#include <stdlib.h>

nlohmann::json& pathfinder2::get_commands()
{
	static std::string json = std::string("/usr/share/inventory_bot/localization_data/commands_") + getenv("PF2_INV_LANG") + ".json";
	static nlohmann::json commands;
	static bool init = false;

	if (!init)
	{
		init = true;
		std::ifstream(json) >> commands;
	}

	return commands;
}

nlohmann::json& pathfinder2::get_messages()
{
	static std::string json = std::string("/usr/share/inventory_bot/localization_data/messages_") + getenv("PF2_INV_LANG") + ".json";
	static nlohmann::json messages;
	static bool init = false;

	if (!init)
	{
		init = true;
		std::ifstream(json) >> messages;
	}

	return messages;
}