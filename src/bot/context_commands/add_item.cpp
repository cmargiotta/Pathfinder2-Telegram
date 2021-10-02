#include "context_commands.hpp"

#include <vector>
#include <memory>

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
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
        character_->get_inventory().add_item(text);

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
        std::string _text = get_message("add_done", message->from->languageCode);
        bot.getApi().sendMessage(id, _text + " x1", false, 0, keyboard);
        bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
    }
}
