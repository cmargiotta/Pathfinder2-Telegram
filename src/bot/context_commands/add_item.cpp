#include "context_commands.hpp"

#include <vector>
#include <memory>

#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

using std::vector;
using std::make_shared;

void pathfinder2::add_item_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();
    static auto& buttons = pathfinder2::get_commands();

    const auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    if (text == buttons["ask_master"])
    {
        //TODO
    }
    else if (text == buttons["create_custom_item"])
    {
        //TODO
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

        character_->get_inventory().add_item(text);
        character_->set_context("");

        bot.getApi().sendMessage(id, messages["add_done"]);
	    bot.getApi().sendMessage(id, character_->get_context(), false, 0, keyboard);
        bot.getApi().sendMessage(id, messages["default_message"], false, 0, pathfinder2::get_default_keyboard(), "Markdown");
    }

	
}