#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "inventory/item_database.hpp"
#include "character/character_cache.hpp"

void pathfinder2::give_request_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    auto& item_list = character_->get_inventory().get_item_list(true);
    auto keyboard = create_keyboard(item_list.begin(), item_list.end());
    pathfinder2::add_button_row(keyboard, get_command("cancel", message->from->languageCode));

    character_->set_data(text);
    character_->set_context(get_message("give_response", message->from->languageCode));
	bot.getApi().sendMessage(character_->get_id(), character_->get_context(), false, 0, keyboard);
}
