#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "inventory/item_database.hpp"
#include "character/character_cache.hpp"

void pathfinder2::add_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& item_db = pathfinder2::item_database::get_instance();

    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	for (auto& item: character_->get_inventory().get_item_list())
	{
		if (item == text)
		{
			//Perfect match on inventory, no need to continue, add it directly
			add_item_(bot, message, database);
            return;
		}
	}

    auto matches = item_db.search_items(text);

    for (auto& item: matches)
    {
        if (item->name == text)
        {
			//Perfect match on item database, no need to continue, add it directly
			add_item_(bot, message, database);
            return;
        }
    }

    auto keyboard = pathfinder2::create_keyboard({});

	for (auto& item: matches)
    {
        pathfinder2::add_button_row(keyboard, item->name);
    }

    if (character_->get_data() == "")
    {
        pathfinder2::add_button_row(keyboard, get_command("create_custom_item", message->from->languageCode));
        pathfinder2::add_button_row(keyboard, get_command("ask_master", message->from->languageCode));
    }
    
    pathfinder2::add_button_row(keyboard, get_command("cancel", message->from->languageCode));
	
    character_->set_context(get_message("add_item_request", message->from->languageCode));
    bot.getApi().sendMessage(id, character_->get_context(), false, 0, keyboard);
}