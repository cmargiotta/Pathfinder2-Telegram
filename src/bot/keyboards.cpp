#include "keyboards.hpp"

#include <fstream>

#include "local_data.hpp"

using std::vector;
using std::string;
using std::ifstream;
using pathfinder2::get_commands;
using TgBot::KeyboardButton;
using TgBot::ReplyKeyboardMarkup;

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

ReplyKeyboardMarkup::Ptr pathfinder2::create_one_column_keyboard(const vector<string>& buttons)
{
	auto keyboard = std::make_shared<TgBot::ReplyKeyboardMarkup>();

	for (auto& text: buttons) 
	{
		vector<KeyboardButton::Ptr> row;

		auto button = std::make_shared<KeyboardButton>();
		button->text = text;
		row.push_back(button);

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

ReplyKeyboardMarkup::Ptr& pathfinder2::get_default_keyboard()
{
	static auto& keys = get_commands();
	static auto keyboard = pathfinder2::create_keyboard({
		{keys["add"], keys["remove"]},
		{keys["list"]},
		{keys["set_capacity"]},
		{keys["get_money"], keys["money_transaction"]}
	});

	return keyboard;
}