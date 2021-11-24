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
	void _add(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void _remove(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void _list(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void _set_capacity(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void _money_transaction(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void _get_money(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);

	void _give(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void _edit_item_master(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void _delete_item_master(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void _register_item_master(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void _set_coin_bulk_master(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
	void _send_broadcast_master(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
}
#endif // COMMANDS_HPP_

/*****
COMMAND SNIPPET
#include "commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::_command(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	character_->set_context(context);
	bot.getApi().sendMessage(id, character_->get_context(), false, 0, pathfinder2::remove_keyboard);
}
*/