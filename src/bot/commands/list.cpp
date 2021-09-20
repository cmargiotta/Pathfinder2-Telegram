#include "commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::_list(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    auto keyboard = pathfinder2::create_keyboard({
		{
			get_command("list_brief")
		}, 
		{
			get_command("list_detail", message->from->languageCode)
		}
	});

	character_->set_context(get_message("list_granularity_request", message->from->languageCode));
	bot.getApi().sendMessage(character_->get_id(), character_->get_context(), false, 0, keyboard);
}