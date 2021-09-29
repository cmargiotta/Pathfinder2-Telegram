#include "commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::_edit_item_master(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	if (!master::get_instance().is_master(id))
	{
		throw std::runtime_error("authorization_error");
	}

	auto& item_list = character_->get_inventory().get_item_list();
    auto keyboard = pathfinder2::create_keyboard(item_list.begin(), item_list.end());
    pathfinder2::add_button_row(keyboard, get_command("cancel", message->from->languageCode));

	character_->set_context(get_message("item_edit_request", message->from->languageCode));
	bot.getApi().sendMessage(id, character_->get_context(), false, 0, keyboard);
}
