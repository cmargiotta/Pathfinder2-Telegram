#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "inventory/item_database.hpp"
#include "character/character_cache.hpp"

void pathfinder2::delete_item_master_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	auto& item_db = item_database::get_instance();
	item_db.delete_item(text);

	character_->set_context("");
	bot.getApi().sendMessage(id, get_message("generic_done", message->from->languageCode));
	bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
}