#include "commands.hpp"

const std::unordered_map<std::string, std::function<void(TgBot::Bot&, TgBot::Message::Ptr, SQLite::Database&)>> pathfinder2::commands = {
	{"/start", _start},
	{"/reset", _reset},
	{"add", _add},
	{"remove", _remove}
};