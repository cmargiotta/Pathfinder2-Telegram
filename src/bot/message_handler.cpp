#include "message_handler.hpp"

#include <memory>
#include <iostream>

#include "keyboards.hpp"
#include "local_data.hpp"
#include "commands/commands.hpp"
#include "character/character_cache.hpp"
#include "context_commands/context_commands.hpp"

void pathfinder2::message_handler(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();
	static auto& keys = pathfinder2::get_commands();

	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	auto& context = character_->get_context();

	try
	{
		if (context.empty())
		{		
			std::string cmd;
			for (auto i = keys.begin(); i != keys.end(); ++i)
			{
				if (i.value() == message->text)
				{
					cmd = i.key();
					break;
				}
			}

			pathfinder2::commands.at(cmd)(bot, message, database);	
		}
		else
		{
			if (message->text == keys["cancel"])
			{
				character_->set_context("");
				bot.getApi().sendMessage(character_->get_id(), messages["cancel_done"]);
				bot.getApi().sendMessage(id, messages["default_message"], false, 0, pathfinder2::get_default_keyboard());
			}

			std::string last_request;
			for (auto i = messages.begin(); i != messages.end(); ++i)
			{
				if (i.value() == context)
				{
					last_request = i.key();
					break;
				}
			}

			pathfinder2::context_commands.at(last_request)(bot, message, database);	
		}
	}
	catch(std::runtime_error& e)
	{
		bot.getApi().sendMessage(character_->get_id(), e.what());
	}
	// catch(...)
	// {
	// 	bot.getApi().sendMessage(character_->get_id(), messages["generic_error"]);
	// }
}