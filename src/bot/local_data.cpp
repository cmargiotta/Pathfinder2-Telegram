#include "local_data.hpp"

#include <fstream>

nlohmann::json& pathfinder2::get_commands()
{
	static nlohmann::json commands;
	static bool init = false;

	if (!init)
	{
		init = true;
		std::ifstream("commands.json") >> commands;
	}

	return commands;
}

nlohmann::json& pathfinder2::get_messages()
{
	static nlohmann::json messages;
	static bool init = false;

	if (!init)
	{
		init = true;
		std::ifstream("messages.json") >> messages;
	}

	return messages;
}