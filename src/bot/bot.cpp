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
	 _bot(getenv("PF2_INV_BOT_TOKEN")),
	database(_database)
{
	using namespace std::placeholders;

	_bot.getEvents().onAnyMessage([this](TgBot::Message::Ptr msg){message_handler(_bot, msg, database);});

	_bot.getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) {
        callback_handler(_bot, query, database);
    });

	std::cout << "Bot username: " << _bot.getApi().getMe()->username << std::endl;

	const char* port = getenv("PF2_INV_PORT");
	const char* webhook_url = getenv("PF2_INV_WEBHOOK_URL");

	if (port == nullptr)
	{
		port = "8080";
	}

	if (!common::is_number(port))
	{
		throw std::runtime_error("Error, PF2_INV_PORT is not a valid port.");
	}

	master::get_instance(&database, &_bot);

	if (webhook_url != nullptr)
	{	
		TgBot::TgWebhookTcpServer webhook_server(atoi(port), _bot);
		_bot.getApi().setWebhook(std::string(webhook_url), TgBot::InputFile::fromFile("/usr/share/inventory_bot/certs/public.pem", "application/x-pem-file"));

		std::cout << "Starting webhook server at " << webhook_url << std::endl;

        webhook_server.start();
	}
	else 
	{
		std::cout << "Warning, webhook url not set, starting long poll mode.\n";

		TgBot::TgLongPoll long_poll(_bot);
		while (true) 
		{
			long_poll.start();
		}
	}
}