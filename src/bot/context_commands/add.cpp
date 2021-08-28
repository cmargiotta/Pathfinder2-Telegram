#include "context_commands.hpp"

#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "inventory/item_database.hpp"
#include "character/character_cache.hpp"

void pathfinder2::add_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();
    static auto& item_db = pathfinder2::item_database::get_instance();
    static auto& buttons = pathfinder2::get_commands();

    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    auto matches = item_db.search_items(text);

    for (auto& item: matches)
    {
        if (item->name == text)
        {
            //Perfect match, no need to continue, add it directly
            character_->get_inventory().add_item(item->name);
            character_->set_context("");
            bot.getApi().sendMessage(id, messages["add_done"], false, 0, pathfinder2::get_default_keyboard());
            return;
        }
    }

    auto keyboard = pathfinder2::create_one_column_keyboard({});

	for (auto& item: matches)
    {
        pathfinder2::add_button_row(keyboard, item->name);
    }

    pathfinder2::add_button_row(keyboard, buttons["create_custom_item"]);
    pathfinder2::add_button_row(keyboard, buttons["ask_master"]);
    pathfinder2::add_button_row(keyboard, buttons["cancel"]);
	
    character_->set_context(messages["add_item_request"]);
    bot.getApi().sendMessage(id, character_->get_context(), false, 0, keyboard);
}