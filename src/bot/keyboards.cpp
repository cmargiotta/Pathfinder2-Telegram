#include "keyboards.hpp"

#include <vector>
#include <string>
#include <fstream>

#include "local_data.hpp"

using std::vector;
using std::string;
using std::ifstream;
using pathfinder2::get_keys;

TgBot::ReplyKeyboardMarkup::Ptr create_keyboard(const vector<vector<string>>& button_layout)
{
	TgBot::ReplyKeyboardMarkup::Ptr keyboard;

	for (size_t i = 0; i < button_layout.size(); ++i) 
	{
		vector<TgBot::KeyboardButton::Ptr> row;
		for (size_t j = 0; j < button_layout[i].size(); ++j) 
		{
			TgBot::KeyboardButton::Ptr button(new TgBot::KeyboardButton);
			button->text = button_layout[i][j];
			row.push_back(button);
		}
		keyboard->keyboard.push_back(row);
	}

	return keyboard;
}

TgBot::ReplyKeyboardMarkup::Ptr& pathfinder2::get_default_keyboard()
{
	static auto& keys = get_keys();
	static auto keyboard = create_keyboard({
      {keys["add"], keys["remove"]},
      {keys["list"]},
      {keys["set_capacity"]},
      {keys["money"], keys["money_transaction"]}
    });

	return keyboard;
}