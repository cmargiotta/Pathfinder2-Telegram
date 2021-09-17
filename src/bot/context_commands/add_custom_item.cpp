#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "character/character_cache.hpp"

void pathfinder2::add_custom_item_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();
    static auto& buttons = pathfinder2::get_commands();

    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	auto data = common::split(text, ",");

	std::string bulk, category;

	bulk = data[0];
	common::trim(bulk);
	if (data.size() == 2)
	{
		category = data[1];
		common::trim(category);
	}

	character_->get_inventory().add_item(character_->get_data(), bulk, category);

	auto keyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();
	std::vector<TgBot::InlineKeyboardButton::Ptr> row0;

	auto remove = std::make_shared<TgBot::InlineKeyboardButton>();
	auto add = std::make_shared<TgBot::InlineKeyboardButton>();
	
	remove->text = "-";
	add->text = "+";

	remove->callbackData = "-" + text;
	add->callbackData = "+" + text;

	row0.push_back(remove);
	row0.push_back(add);

	keyboard->inlineKeyboard.push_back(row0);

	character_->set_context("");
	bot.getApi().sendMessage(id, messages["add_done"], false, 0, keyboard);
    bot.getApi().sendMessage(id, messages["default_message"], false, 0, pathfinder2::get_default_keyboard(master::get_instance().is_master(id)), "MarkdownV2");
}