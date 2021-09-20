#ifndef __CONTEXT_COMMANDS_H__
#define __CONTEXT_COMMANDS_H__

#include <string>
#include <functional>
#include <tgbot/tgbot.h>
#include <unordered_map>
#include <SQLiteCpp/SQLiteCpp.h>

namespace pathfinder2
{
	extern const std::unordered_map<std::string, std::function<void(TgBot::Bot&, TgBot::Message::Ptr, SQLite::Database&)>> context_commands;
    
    void add_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
    void list_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
    void remove_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
    void add_item_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void list_detail_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void set_capacity_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void edit_selection_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void add_custom_item_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void edit_item_master_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void money_transaction_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void edit_value_request_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void delete_item_master_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void register_item_master_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
}

/*****
COMMAND SNIPPET
#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::command_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	character_->set_context(context);
	bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
}
*/
#endif // __CONTEXT_COMMANDS_H__