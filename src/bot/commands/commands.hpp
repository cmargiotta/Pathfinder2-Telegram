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
	void _reset(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
}
#endif // COMMANDS_HPP_

/*****
COMMAND SNIPPET
#include "commands.hpp"

#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

using pathfinder2::character;

void pathfinder2::command_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();
	auto character_ = pathfinder2::character_cache[id];

	character_->set_context(context);
	bot.getApi().sendMessage(character_->get_id(), character_->get_context(), false, 0, pathfinder2::remove_keyboard);
}
*/