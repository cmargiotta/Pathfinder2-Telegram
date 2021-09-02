#include "bot.hpp"

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <functional>

#include "master.hpp"
#include "message_handler.hpp"
#include "callback_handler.hpp"
#include "common/string_utils.hpp"

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

	std::cout << "Bot username: " << _bot.getApi().getMe()->username << std::endl;

	const char* port = getenv("PF2_BOT_PORT");
	const char* webhook_url = getenv("WEBHOOK_URL");

	master::get_instance(&database, &_bot);

	if (port != nullptr && webhook_url != nullptr)
	{
		if (!common::is_number(port))
		{
			throw std::runtime_error("Port not valid.");
		}

		
		TgBot::TgWebhookTcpServer webhook_server(atoi(port), _bot);
		_bot.getApi().setWebhook(std::string(webhook_url) + ":" + port);

		std::cout << "Starting webhook server at " << webhook_url << ":" << port << std::endl;

        webhook_server.start();
	}
	else 
	{
		std::cout << "Warning, webhook ";

		if (port == nullptr)
		{
			std::cout << "port ";
		}
		else
		{
			std::cout << "url ";
		}
		std::cout << "not set, starting long poll mode.\n";

		TgBot::TgLongPoll long_poll(_bot);
		while (true) 
		{
			long_poll.start();
		}
	}
}