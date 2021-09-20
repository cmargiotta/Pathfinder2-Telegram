#include "context_commands.hpp"

#include <stdlib.h>

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "character/character_cache.hpp"

void pathfinder2::money_transaction_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages(message->from->languageCode);

    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	if (!common::is_number(text))
	{
		throw std::runtime_error("generic_error");
	}

	character_->update_cp(atoi(text.c_str()));

	character_->set_context("");
	bot.getApi().sendMessage(id, messages["generic_done"]);
	bot.getApi().sendMessage(id, messages["default_message"], false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
}