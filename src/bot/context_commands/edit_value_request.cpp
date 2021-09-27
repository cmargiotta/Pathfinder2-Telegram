#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "inventory/item_database.hpp"
#include "character/character_cache.hpp"

void pathfinder2::edit_value_request_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	auto& item_db = item_database::get_instance();
    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];
	auto fields = common::split(character_->get_data(), ",");
	auto& name = fields[0];
	auto& field = fields[1];

	if (field == get_command("edit_field_category", message->from->languageCode))
	{
		item_db.update_category(name, text);
	}
	else if	(field == get_command("edit_field_bulk", message->from->languageCode))
	{
		item_db.update_bulk(name, text);
	}
	else if	(field == get_command("edit_field_description", message->from->languageCode))
	{
		item_db.update_description(name, text);
	}
	else if (field == get_command("edit_field_url", message->from->languageCode))
	{
		item_db.update_url(name, text);
	}
	else
	{
		throw std::runtime_error("generic_error");
	}

	character_->set_context("");
	character_->set_data("");
	bot.getApi().sendMessage(id, get_message("default_message", message->from->languageCode), false, 0, pathfinder2::get_default_keyboard(message->from->languageCode, master::get_instance().is_master(id)));
}