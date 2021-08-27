#ifndef MESSAGE_HANDLER_HPP_
#define MESSAGE_HANDLER_HPP_

#include <tgbot/tgbot.h>
#include <SQLiteCpp/SQLiteCpp.h>

namespace pathfinder2
{
	void message_handler(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database);
}

#endif // MESSAGE_HANDLER_HPP_