#include "bot.hpp"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <functional>

#include "master.hpp"
#include "https_server.hpp"
#include "message_handler.hpp"
#include "callback_handler.hpp"
#include "common/string_utils.hpp"

using namespace pathfinder2;

std::string timestamp_to_readble(const time_t rawtime)
{
    struct tm * dt;
    char buffer [30];
    dt = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%m/%d/%y %H:%M", dt);
    return std::string(buffer);
}

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
		https_server server (atoi(port), _bot.getEventHandler());
		_bot.getApi().setWebhook(webhook_url, TgBot::InputFile::fromFile("/usr/share/inventory_bot/certs/public.crt", "application/x-pem-file"));
		std::cout << "Starting webhook server at " << _bot.getApi().getWebhookInfo()->url << std::endl;
		std::cout << "Has custom certificate: " << (_bot.getApi().getWebhookInfo()->hasCustomCertificate ? "yes" : "no") << std::endl;

        server.start();
	}
	else 
	{
		std::cout << "Warning, webhook url not set, starting long poll mode.\n";

		_bot.getApi().deleteWebhook();
		TgBot::TgLongPoll long_poll(_bot);
		while (true) 
		{
			long_poll.start();
		}
	}

	std::cout << "Last error: " << _bot.getApi().getWebhookInfo()->lastErrorMessage << " at " << timestamp_to_readble(_bot.getApi().getWebhookInfo()->lastErrorDate) << std::endl;
	std::cout << "Pending updates: " << _bot.getApi().getWebhookInfo()->pendingUpdateCount << std::endl;
}