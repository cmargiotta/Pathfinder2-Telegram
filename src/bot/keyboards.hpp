#ifndef KEYBOARDS_HPP_
#define KEYBOARDS_HPP_

#include <tgbot/tgbot.h>

namespace pathfinder2
{
	TgBot::ReplyKeyboardMarkup::Ptr& get_default_keyboard();

	static TgBot::ReplyKeyboardRemove::Ptr remove_keyboard;
}
#endif // KEYBOARDS_HPP_