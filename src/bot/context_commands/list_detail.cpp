#include "context_commands.hpp"

#include <memory>
#include <string>

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "character/character_cache.hpp"

void pathfinder2::list_detail_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];
	auto item = character_->get_inventory().get_item(text);

	common::trim(text);
	text = common::escape(text, common::to_escape, '\\');

	std::stringstream message_;
	message_ << "[" << text << "](" << item->get_url() << ")\n";
    message_ << "Bulk: " + item->get_bulk_string() + "\n\n";
    message_ << item->get_description(); 

	character_->set_context("");

	if (item->get_image().size() != 0)
	{
		auto image = std::make_shared<TgBot::InputFile>();
		image->data = item->get_image();
		image->fileName = item->get_name() + ".jpg";
		bot.getApi().sendPhoto(id, image, message_.str(), 0, remove_keyboard, "MarkdownV2");
	}
	else 
	{
		bot.getApi().sendMessage(id, message_.str(), false, 0, pathfinder2::remove_keyboard, "MarkdownV2");
	}
	
	bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
}