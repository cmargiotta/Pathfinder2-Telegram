#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "inventory/item_database.hpp"
#include "character/character_cache.hpp"

void pathfinder2::edit_item_master_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{	static auto keyboard = get_edit_keyboard(message->from->languageCode);

    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	//This throws an exception if the item does not exist
	auto& item_db = item_database::get_instance();
	item_db.get_item(text);

	character_->set_data(text);
	character_->set_context(get_message("edit_selection", message->from->languageCode));
	bot.getApi().sendMessage(id, character_->get_context(), false, 0, keyboard);
}