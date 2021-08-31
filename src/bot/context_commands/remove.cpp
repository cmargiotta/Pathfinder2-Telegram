#include "context_commands.hpp"

#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::remove_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();

    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    character_->get_inventory().remove_item(text);

	character_->set_context("");
	bot.getApi().sendMessage(id, messages["remove_done"], false, 0, pathfinder2::remove_keyboard);
    bot.getApi().sendMessage(id, messages["default_message"], false, 0, pathfinder2::get_default_keyboard());
}