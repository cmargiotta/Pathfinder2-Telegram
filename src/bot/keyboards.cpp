#include "keyboards.hpp"

#include <fstream>

#include "local_data.hpp"

using std::vector;
using std::string;
using std::ifstream;
using pathfinder2::get_commands;
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

ReplyKeyboardMarkup::Ptr pathfinder2::get_default_keyboard(bool master)
{
	static auto& keys = get_commands();

	static auto keyboard = pathfinder2::create_keyboard({
		{keys["add"], keys["remove"]},
		{keys["list"]},
		{keys["set_capacity"]},
		{keys["get_money"], keys["money_transaction"]}
	});
	
	static auto master_keyboard = pathfinder2::create_keyboard({
		{keys["add"], keys["remove"]},
		{keys["list"]},
		{keys["set_capacity"]},
		{keys["get_money"], keys["money_transaction"]},
		{keys["register_item_master"]},
		{keys["delete_item_master"]},
		{keys["edit_item_master"]}
	});

	if (!master)
	{
		return keyboard;
	}
	else
	{
		return master_keyboard;
	}
}