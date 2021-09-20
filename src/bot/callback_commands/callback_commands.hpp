#ifndef __CALLBACK_COMMANDS_H__
#define __CALLBACK_COMMANDS_H__

#include <string>
#include <functional>
#include <tgbot/tgbot.h>
#include <unordered_map>
#include <SQLiteCpp/SQLiteCpp.h>

namespace pathfinder2
{
	extern const std::unordered_map<char, std::function<void(TgBot::Bot&, TgBot::CallbackQuery::Ptr, SQLite::Database&)>> callback_commands;
    
    void add(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr query, SQLite::Database& database);
    void remove(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr query, SQLite::Database& database);
}

/*****
COMMAND SNIPPET
#include "callback_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "character/character_cache.hpp"

void pathfinder2::add(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr query, SQLite::Database& database)
{
    auto& text = query->message->text;
	auto id = query->message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	bot.getApi().sendMessage(id, character_->get_context(), false, 0, pathfinder2::remove_keyboard);
}
*/

#endif // __CALLBACK_COMMANDS_H__