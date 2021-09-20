#include "context_commands.hpp"

#include <string>

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "character/character_cache.hpp"

void pathfinder2::list_detail_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages(message->from->languageCode);
    static auto& buttons = pathfinder2::get_commands(message->from->languageCode);

    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];
	auto item = character_->get_inventory().get_item(text);

	common::trim(text);

	std::stringstream message_;
	message_ << "[" << text << "](" << item->get_url() << ")\n";
    message_ << "Bulk: " + item->get_bulk_string() + "\n\n";
    message_ << item->get_description(); 

	character_->set_context("");
	bot.getApi().sendMessage(id, message_.str(), false, 0, pathfinder2::remove_keyboard, "MarkdownV2");
	bot.getApi().sendMessage(id, messages["default_message"], false, 0, pathfinder2::get_default_keyboard(master::get_instance().is_master(id)));
}