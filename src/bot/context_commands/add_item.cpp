#include "context_commands.hpp"

#include <vector>
#include <memory>

#include "../master.hpp"
#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

using std::vector;
using std::make_shared;

void pathfinder2::add_item_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
    const auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    if (text == get_command("ask_master", message->from->languageCode))
    {
        auto& master = master::get_instance();
		master.send_message(std::string(message->from->username) + ": " + character_->get_data());

		character_->set_context("");

        bot.getApi().sendMessage(id, get_message("generic_done", message->from->languageCode));
        bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
    }
    else if (text == get_command("create_custom_item", message->from->languageCode))
    {
		character_->set_context(get_message("custom_item_info_request", message->from->languageCode));
		bot.getApi().sendMessage(id, character_->get_context(), false, 0, pathfinder2::remove_keyboard);
    }
    else
    {
        auto keyboard = make_shared<TgBot::InlineKeyboardMarkup>();
        vector<TgBot::InlineKeyboardButton::Ptr> row0;

        auto remove = make_shared<TgBot::InlineKeyboardButton>();
        auto add = make_shared<TgBot::InlineKeyboardButton>();
        
        remove->text = "-";
        add->text = "+";

        remove->callbackData = "-" + text;
        add->callbackData = "+" + text;

        row0.push_back(remove);
        row0.push_back(add);

        keyboard->inlineKeyboard.push_back(row0);
        character_->set_context("");

        if (character_->get_data() != "")
        {
			if (!master::get_instance().is_master(character_->get_id()))
            {
                //Not the master, the item must be removed from inventory
                character_->get_inventory().remove_item(text);
            }

            std::string target = character_->get_data();
            character_->set_data("");
            
            character_ = character_cache[character::get_id(database, target)];

            character_->get_inventory().add_item(text);
            auto item = character_->get_inventory().get_item(text);

            text = common::escape(text, common::to_escape, '\\');

            std::stringstream message_;
            message_ << get_message("new_item_notification", message->from->languageCode) << "\n\n";
            message_ << "[" << text << "](" << item->get_url() << ")\n";
            message_ << "Bulk: " + item->get_bulk_string() + "\n\n";
            message_ << common::escape(item->get_description(), common::to_escape, '\\'); 

            bot.getApi().sendMessage(character_->get_id(), message_.str(), false, 0, std::make_shared<TgBot::GenericReply>(), "MarkdownV2");
        }
        else 
        {
            character_->get_inventory().add_item(text);

            std::string _text = get_message("add_done", message->from->languageCode);
            bot.getApi().sendMessage(id, _text + " x1", false, 0, keyboard);
        }

        bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
    }
}
