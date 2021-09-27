#include "commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::_give(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    auto usernames = character::get_usernames(database);
    auto keyboard = create_keyboard(usernames.begin(), usernames.end());
    add_button_row(keyboard, get_command("cancel", message->from->languageCode));

	character_->set_context(get_message("give_request", message->from->languageCode));
	bot.getApi().sendMessage(id, character_->get_context(), false, 0, keyboard);
}