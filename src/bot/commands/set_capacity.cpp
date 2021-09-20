#include "commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::_set_capacity(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	character_->set_context(get_message("capacity_request", message->from->languageCode));
	bot.getApi().sendMessage(id, character_->get_context(), false, 0, pathfinder2::remove_keyboard);
}