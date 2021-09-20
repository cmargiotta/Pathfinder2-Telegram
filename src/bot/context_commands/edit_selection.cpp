#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::edit_selection_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	character_->set_data(character_->get_data() + "," + text);

	character_->set_context(get_message("edit_value_request", message->from->languageCode));
	bot.getApi().sendMessage(id, character_->get_context(), false, 0, pathfinder2::remove_keyboard);
}