#ifndef KEYBOARDS_HPP_
#define KEYBOARDS_HPP_

#include <vector>
#include <memory>
#include <string>
#include <iterator>
#include <type_traits>
#include <tgbot/tgbot.h>

namespace pathfinder2
{
	TgBot::ReplyKeyboardMarkup::Ptr create_keyboard(const std::vector<std::vector<std::string>>& button_layout);
	TgBot::ReplyKeyboardMarkup::Ptr get_default_keyboard(const std::string& locale, bool master = false);
	TgBot::ReplyKeyboardMarkup::Ptr get_edit_keyboard(const std::string& locale);

	void add_button_row(TgBot::ReplyKeyboardMarkup::Ptr keyboard, const std::string& text);

	//This function accepts only string iterators
	template<class T>
	typename std::enable_if<
		std::is_same<typename std::iterator_traits<T>::value_type, std::string>::value,
		TgBot::ReplyKeyboardMarkup::Ptr
	>::type
	create_keyboard(const T buttons_start, const T buttons_end)
	{
		auto keyboard = std::make_shared<TgBot::ReplyKeyboardMarkup>();

		for (auto i = buttons_start; i != buttons_end; ++i) {
			std::vector<TgBot::KeyboardButton::Ptr> row;

			auto button = std::make_shared<TgBot::KeyboardButton>();
			button->text = *i;
			row.push_back(button);
			keyboard->keyboard.push_back(row);
		}

		return keyboard;
	}

	extern const TgBot::ReplyKeyboardRemove::Ptr remove_keyboard;
}
#endif // KEYBOARDS_HPP_