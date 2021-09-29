#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "inventory/item_database.hpp"
#include "character/character_cache.hpp"

void pathfinder2::register_item_master_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	auto& item_db = item_database::get_instance();

	auto data = common::split(text, "\n");

	std::string name, url, description, bulk, category;
	for (auto& field: data)
	{
		common::trim(field);
		if (field[0] == '\"' && description.size() == 0)
		{
			description = field.substr(1, field.size() - 2);
		}
		else if (field.substr(0, 4) == "http" && url.size() == 0)
		{
			url = field;
		}
		else if ((((field[0] == 'L' || field[0] == 'l') && field.size() == 1) || 
					(field[0] >= '0' && field[0] <= '9')) && bulk.size() == 0)
		{
			bulk = field;
		}
		else if (name.size() == 0)
		{
			name = field;
		}
		else if (category.size() == 0)
		{
			category = field;
		}
		else
		{
			throw std::runtime_error(field);
		}
	}

	if (name.size() == 0 || bulk.size() == 0)
	{
		throw std::runtime_error("no_bulk_name");
	}

	item_db.register_new_item(name, url, category, description, bulk);

	character_->set_context("");
	bot.getApi().sendMessage(id, get_message("generic_done", message->from->languageCode));
	bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
}