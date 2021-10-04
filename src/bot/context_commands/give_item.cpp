#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "inventory/item_database.hpp"
#include "character/character_cache.hpp"

void pathfinder2::give_item_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    if (!master::get_instance().is_master(character_->get_id()))
    {
        //Not the master, the item must be removed from inventory
        character_->get_inventory().remove_item(text);
    }

    std::string target = character_->get_data();
    
    auto dest_character = character_cache[character::get_id(database, target)];

    try 
    {
        dest_character->get_inventory().add_item(text);
    }
    catch(...)
    {
        auto item = character_->get_inventory().get_item(text);
        dest_character->get_inventory().add_item(text, item->get_bulk_string(), item->get_category());
    }

    auto item = dest_character->get_inventory().get_item(text);
    
    std::stringstream message_;
    message_ << get_message("new_item_notification", message->from->languageCode) + " @" + character_->get_username() << "\n\n";
    message_ << "[" << common::escape(text, common::to_escape, '\\') << "](" << item->get_url() << ")\n";
    message_ << "Bulk: " + item->get_bulk_string() + "\n\n";
    message_ << common::escape(item->get_description(), common::to_escape, '\\'); 

    if (item->get_image().size() != 0)
	{
		auto image = std::make_shared<TgBot::InputFile>();
		image->data = item->get_image();
		image->fileName = item->get_name() + ".jpg";
		bot.getApi().sendPhoto(dest_character->get_id(), image, message_.str(), 0, std::make_shared<TgBot::GenericReply>(), "MarkdownV2");
	}
	else 
	{
		bot.getApi().sendMessage(dest_character->get_id(), message_.str(), false, 0, std::make_shared<TgBot::GenericReply>(), "MarkdownV2");
	}

    character_->set_data("");
    character_->set_context("");
    bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
}
