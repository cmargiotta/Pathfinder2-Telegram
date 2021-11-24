#include "context_commands.hpp"

#include <cmath>
#include <string>

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "database/settings.hpp"
#include "common/string_utils.hpp"
#include "inventory/item_database.hpp"
#include "character/character_cache.hpp"

void pathfinder2::set_coin_bulk_master_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	common::trim(text); 
	static auto& settings = pathfinder2::settings::get_instance(&database); 
	
	double bulk = common::parse_bulk(text); 
	settings.set_coin_bulk(bulk);

	auto bcast_text = get_message("new_coin_bulk", message->from->languageCode);
	bcast_text += common::bulk_to_string(bulk); 

	for (auto& id_dest: character::get_ids(database))
	{
		try
		{
			//bot.getApi().sendMessage(id_dest, text);
		}
		catch (...)
		{
			;
		}
	}

	character_->set_context("");
	bot.getApi().sendMessage(id, get_message("generic_done", message->from->languageCode));
	bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
}