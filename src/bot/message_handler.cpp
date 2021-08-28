#include "message_handler.hpp"

#include <memory>
#include <iostream>

#include "keyboards.hpp"
#include "local_data.hpp"
#include "commands/commands.hpp"
#include "character/character_cache.hpp"
#include "context_commands/context_commands.hpp"

using std::shared_ptr;
using std::make_shared;
using pathfinder2::character;

void pathfinder2::message_handler(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();
	static auto& keys = pathfinder2::get_commands();

	auto id = message->chat->id;
	shared_ptr<character> character_;

	if (pathfinder2::character_cache.contains(id))
	{
		//Load character from cache
		character_ = pathfinder2::character_cache[id];
	}
	else
	{
		//Character not in cache, load from DB or create a new one
		character_ = make_shared<character>(id, database);
		pathfinder2::character_cache.insert(character_->get_id(), character_);
	}

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
	catch(...)
	{
		bot.getApi().sendMessage(character_->get_id(), messages["error"]);
	}
}