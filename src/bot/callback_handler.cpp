#include "callback_handler.hpp"

#include <memory>
#include <iostream>

#include "keyboards.hpp"
#include "local_data.hpp"
#include "commands/commands.hpp"
#include "character/character_cache.hpp"
#include "callback_commands/callback_commands.hpp"

void pathfinder2::callback_handler(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr query, SQLite::Database& database)
{
	auto id = query->message->chat->id;
	auto character_ = pathfinder2::character_cache[id];
	
	try
	{
		pathfinder2::callback_commands.at(query->data[0])(bot, query, database);
	}
	catch(std::runtime_error& e)
	{
		try
		{
			bot.getApi().sendMessage(character_->get_id(), get_message(e.what(), query->message->from->languageCode));
		}
		catch(...)
		{
			bot.getApi().sendMessage(character_->get_id(), e.what());
		}
	}
	catch(...)
	{
		bot.getApi().sendMessage(character_->get_id(), get_message("generic_error", query->message->from->languageCode));
	}
}