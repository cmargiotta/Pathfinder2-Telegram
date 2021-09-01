#include "master.hpp"

#include <exception>

using pathfinder2::master;

master::master(int _id, TgBot::Bot& _bot):
	id(_id),
	bot(_bot)
{}

master& master::get_instance(int id, TgBot::Bot* bot)
{
	static bool init = false;

	if (!init && !bot)
	{
		throw std::runtime_error("No master registered");
	}

	static master instance (id, *bot);
	init = true;

	return instance;
}

int master::get_id()
{
	return id;
}

void master::send_message(const std::string& message)
{
	bot.getApi().sendMessage(get_id(), message);
}