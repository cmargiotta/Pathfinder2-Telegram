#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

#include <string>
#include <functional>
#include <tgbot/tgbot.h>
#include <unordered_map>
#include <SQLiteCpp/SQLiteCpp.h>

namespace pathfinder2
{
	extern const std::unordered_map<std::string, std::function<void(TgBot::Bot&, TgBot::Message::Ptr, SQLite::Database&)>> commands;

	void _start(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
}
#endif // COMMANDS_HPP_