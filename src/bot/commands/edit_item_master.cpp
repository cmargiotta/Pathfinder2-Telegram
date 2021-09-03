#include "commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::_edit_item_master(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();
    static auto& buttons = pathfinder2::get_commands();

	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	if (!master::get_instance().is_master(id))
	{
		throw std::runtime_error("authorization_error");
	}

	character_->set_context(messages["item_edit_request"]);
	bot.getApi().sendMessage(id, character_->get_context(), false, 0, pathfinder2::remove_keyboard);
}