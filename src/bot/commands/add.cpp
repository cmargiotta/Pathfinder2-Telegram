#include "commands.hpp"

#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::_add(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();
    static auto& buttons = pathfinder2::get_commands();

    auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    auto& item_list = character_->get_inventory().get_item_list();
    auto keyboard = pathfinder2::create_one_column_keyboard(item_list.begin(), item_list.end());
    pathfinder2::add_button_row(keyboard, buttons["cancel"]);

	character_->set_context(messages["add_response"]);
	bot.getApi().sendMessage(character_->get_id(), character_->get_context(), false, 0, keyboard);
}