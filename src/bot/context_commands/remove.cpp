#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::remove_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	
    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    character_->get_inventory().remove_item(text);

	character_->set_context("");
	bot.getApi().sendMessage(id, get_message("remove_done", message->from->languageCode), false, 0, pathfinder2::remove_keyboard);
    bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
}