#include "message_handler.hpp"

#include <memory>
#include <iostream>

#include "master.hpp"
#include "keyboards.hpp"
#include "local_data.hpp"
#include "commands/commands.hpp"
#include "character/character_cache.hpp"
#include "context_commands/context_commands.hpp"

void pathfinder2::message_handler(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	auto& context = character_->get_context();

	try
	{
		if (context.empty())
		{		
			std::string cmd = get_command_id(message->text, message->from->languageCode);

			pathfinder2::commands.at(cmd)(bot, message, database);	
		}
		else
		{
			if (message->text == get_command("cancel", message->from->languageCode))
			{
				character_->set_context("");
				bot.getApi().sendMessage(character_->get_id(), get_message("cancel_done", message->from->languageCode));
				bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
				return;
			}

			std::string last_request = get_message_id(context, message->from->languageCode);

			pathfinder2::context_commands.at(last_request)(bot, message, database);	
		}
	}
	catch(std::runtime_error& e)
	{
		try
		{
			bot.getApi().sendMessage(character_->get_id(), get_message(e.what(), message->from->languageCode));
		}
		catch(...)
		{
			bot.getApi().sendMessage(character_->get_id(), e.what());
		}
	}
	catch(...)
	{
		bot.getApi().sendMessage(character_->get_id(), get_message("generic_error", message->from->languageCode));
	}
}