#include "local_data.hpp"

#include <fstream>

nlohmann::json& pathfinder2::get_keys()
{
	static nlohmann::json keys;
	static bool init = false;

	if (!init)
	{
		init = true;
		std::ifstream("keyboards.json") >> keys;
	}

	return keys;
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