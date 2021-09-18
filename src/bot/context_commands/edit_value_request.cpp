#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "inventory/item_database.hpp"
#include "character/character_cache.hpp"

void pathfinder2::edit_value_request_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();
    static auto& buttons = pathfinder2::get_commands();

	auto& item_db = item_database::get_instance();
    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];
	auto fields = common::split(character_->get_data(), ",");
	auto& name = fields[0];
	auto& field = fields[1];

	if (field == buttons["edit_field_category"])
	{
		item_db.update_category(name, text);
	}
	else if	(field == buttons["edit_field_bulk"])
	{
		item_db.update_bulk(name, text);
	}
	else if	(field == buttons["edit_field_description"])
	{
		item_db.update_description(name, text);
	}
	else if (field == buttons["edit_field_url"])
	{
		item_db.update_url(name, text);
	}
	else
	{
		throw std::runtime_error("generic_error");
	}

	character_->set_context("");
	bot.getApi().sendMessage(id, messages["default_message"], false, 0, pathfinder2::get_default_keyboard(master::get_instance().is_master(id)));
}