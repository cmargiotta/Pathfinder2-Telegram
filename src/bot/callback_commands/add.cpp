#include "callback_commands.hpp"

#include <string>
#include <stdlib.h>

#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "character/character_cache.hpp"

using std::vector;
using std::make_shared;

void pathfinder2::add(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr query, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();
    static auto& buttons = pathfinder2::get_commands();

    auto& text = query->message->text;
	auto id = query->message->chat->id;
	auto character_ = pathfinder2::character_cache[id];
	auto item = query->data.substr(1);

	auto keyboard = make_shared<TgBot::InlineKeyboardMarkup>();
	vector<TgBot::InlineKeyboardButton::Ptr> row0;

	auto remove = make_shared<TgBot::InlineKeyboardButton>();
	auto add = make_shared<TgBot::InlineKeyboardButton>();
	
	remove->text = "-";
	add->text = "+";

	remove->callbackData = "-" + item;
	add->callbackData = "+" + item;

	row0.push_back(remove);
	row0.push_back(add);

	keyboard->inlineKeyboard.push_back(row0);

	auto quantity = common::split(text, "x");
	quantity[1] = std::to_string(atoi(quantity[1].c_str()) + 1);

	character_->get_inventory().add_item(item);

	text = messages["add_done"];
	bot.getApi().editMessageText(text + " x" + quantity[1], query->message->chat->id, query->message->messageId, "", "", false, keyboard);
	bot.getApi().answerCallbackQuery(query->id);
}