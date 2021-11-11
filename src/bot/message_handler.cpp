#include "message_handler.hpp"

#include <string>
#include <memory>
#include <iostream>

#include "master.hpp"
#include "keyboards.hpp"
#include "local_data.hpp"
#include "commands/commands.hpp"
#include "common/string_utils.hpp"
#include "character/character_cache.hpp"
#include "dice_expression_parser/node.hpp"
#include "context_commands/context_commands.hpp"

void pathfinder2::message_handler(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	auto& context = character_->get_context();

	if (character_->get_username().size() == 0)
	{
		//If no username on DB, register it
		character_->set_username(message->from->username);
	}

	if (message->text == get_command("cancel", message->from->languageCode))
	{
		character_->set_data("");
		character_->set_context("");
		bot.getApi().sendMessage(id, get_message("cancel_done", message->from->languageCode));
		bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
		return;
	}

	try
	{
		if (context.empty())
		{
			if (message->text.empty())
			{
				bot.getApi().sendMessage(id, get_message("generic_error", message->from->languageCode));
				return;
			}
			
			try 
			{
				auto expression = dice::build_dice_tree(message->text); 
				auto res = expression->compute(); 
				auto expr_print = common::escape(expression->print(), common::to_escape, '\\');   
				auto response = expr_print + "\n" + std::to_string(res); 
				
				bot.getApi().sendMessage(id, response, false, 0, pathfinder2::remove_keyboard, "MarkdownV2");
				bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
				return; 
			}
			catch(...)
			{
				std::string cmd = get_command_id(message->text, message->from->languageCode);

				pathfinder2::commands.at(cmd)(bot, message, database);
			}	
		}
		else
		{
			std::string last_request = get_message_id(context, message->from->languageCode);

			pathfinder2::context_commands.at(last_request)(bot, message, database);	
		}
	}
	catch(std::runtime_error& e)
	{
		try
		{
			bot.getApi().sendMessage(id, get_message(e.what(), message->from->languageCode));
		}
		catch(...)
		{
			bot.getApi().sendMessage(id, e.what());
		}
	}
	catch(...)
	{
		bot.getApi().sendMessage(id, get_message("generic_error", message->from->languageCode));
	}
}