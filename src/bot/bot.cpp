#include "bot.hpp"

#include <cstdlib>
#include <iostream>
#include <functional>

#include "message_handler.hpp"
#include "callback_handler.hpp"

using namespace pathfinder2;

bot::bot(SQLite::Database& _database):
	// _bot(getenv("PF2_BOT_TOKEN")),
	_bot("1996957656:AAGPYXXLrs4IDKl6dqT7bFPCTjJB-8bxoSQ"),
	database(_database)
{
	using namespace std::placeholders;

	_bot.getEvents().onAnyMessage([this](TgBot::Message::Ptr msg){message_handler(_bot, msg, database);});

	_bot.getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) {
        callback_handler(_bot, query, database);
    });

	try 
	{
		std::cout << "Bot username: " << _bot.getApi().getMe()->username << std::endl;

        TgBot::TgLongPoll longPoll(_bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
}