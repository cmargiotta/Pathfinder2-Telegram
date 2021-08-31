#ifndef __CALLBACK_HANDLER_H__
#define __CALLBACK_HANDLER_H__

#include <tgbot/tgbot.h>
#include <SQLiteCpp/SQLiteCpp.h>

namespace pathfinder2
{
	void callback_handler(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr query, SQLite::Database& database);
}
#endif // __CALLBACK_HANDLER_H__