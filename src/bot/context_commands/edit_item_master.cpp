#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::edit_item_master_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages(message->from->languageCode);
    static auto& buttons = pathfinder2::get_commands(message->from->languageCode);
	static auto keyboard = create_keyboard({
		{std::string(buttons["edit_field_category"])},
		{std::string(buttons["edit_field_bulk"])},
		{std::string(buttons["edit_field_description"])},
		{std::string(buttons["edit_field_url"])}
	});

    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];
	character_->set_data(text);
	character_->set_context(messages["edit_selection"]);
	bot.getApi().sendMessage(id, character_->get_context(), false, 0, keyboard);
}