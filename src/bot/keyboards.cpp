#include "keyboards.hpp"

#include <fstream>
#include <unordered_map>

#include "local_data.hpp"

using std::vector;
using std::string;
using std::ifstream;
using TgBot::KeyboardButton;
using TgBot::ReplyKeyboardMarkup;

const TgBot::ReplyKeyboardRemove::Ptr pathfinder2::remove_keyboard = std::make_shared<TgBot::ReplyKeyboardRemove>();

ReplyKeyboardMarkup::Ptr pathfinder2::create_keyboard(const vector<vector<string>>& button_layout)
{
	auto keyboard = std::make_shared<TgBot::ReplyKeyboardMarkup>();

	for (size_t i = 0; i < button_layout.size(); ++i) 
	{
		vector<KeyboardButton::Ptr> row;

		for (size_t j = 0; j < button_layout[i].size(); ++j) 
		{
			auto button = std::make_shared<KeyboardButton>();
			button->text = button_layout[i][j];
			row.push_back(button);
		}

		keyboard->keyboard.push_back(row);
	}

	return keyboard;
}

void pathfinder2::add_button_row(ReplyKeyboardMarkup::Ptr keyboard, const string& text)
{
	vector<KeyboardButton::Ptr> row;
	KeyboardButton::Ptr button(new KeyboardButton);
	button->text = text;
	row.push_back(button);
	keyboard->keyboard.push_back(row);
}

ReplyKeyboardMarkup::Ptr pathfinder2::get_default_keyboard(const std::string& locale, bool master)
{
	static std::unordered_map<std::string, ReplyKeyboardMarkup::Ptr> keyboards, keyboards_master;

	if (master)
	{
		try
		{
			return keyboards_master.at(locale);
		}
		catch(const std::exception& e)
		{
			keyboards_master[locale] = pathfinder2::create_keyboard({
				{get_command("add", locale), get_command("remove", locale)},
				{get_command("list", locale)},
				{get_command("set_capacity", locale)},
				{get_command("get_money", locale), get_command("money_transaction", locale)},
				{get_command("give", locale)},
				{get_command("register_item_master", locale)},
				{get_command("delete_item_master", locale)},
				{get_command("edit_item_master", locale)},
				{get_command("send_broadcast", locale)}
			});

			return keyboards_master[locale];
		}
	}
	else
	{
		try
		{
			return keyboards.at(locale);
		}
		catch(const std::exception& e)
		{
			keyboards[locale] = pathfinder2::create_keyboard({
				{get_command("add", locale), get_command("remove", locale)},
				{get_command("list", locale)},
				{get_command("set_capacity", locale)},
				{get_command("get_money", locale), get_command("money_transaction", locale)},
				{get_command("give", locale)}
			});

			return keyboards[locale];
		}
	}
}