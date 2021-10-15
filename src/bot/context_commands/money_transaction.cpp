#include "context_commands.hpp"

#include <stdlib.h>

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "character/character_cache.hpp"

void pathfinder2::money_transaction_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];
	auto dest = character_cache[character::get_id(database, character_->get_data())];

	auto q = atoi(text.c_str());

	if (!common::is_number(text) || q < 0)
	{
		throw std::runtime_error("generic_error");
	}

	if (!master::get_instance().is_master(dest->get_id()))
	{
		dest->update_cp(q);
	}

	if (!master::get_instance().is_master(id))
	{
		character_->update_cp(0 - q);
	}

	character_->set_context("");
	character_->set_data("");

	bot.getApi().sendMessage(dest->get_id(), get_message("money_notification", message->from->languageCode) 
																	+ "@" + message->chat->username 
																	+ "\n" + text + "cp");
	bot.getApi().sendMessage(id, get_message("generic_done", message->from->languageCode));
	bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
}