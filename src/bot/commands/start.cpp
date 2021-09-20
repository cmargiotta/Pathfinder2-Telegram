#include "commands.hpp"

#include <memory>

#include "../master.hpp"
#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

using std::make_shared;
using pathfinder2::character;

void pathfinder2::_start(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages(message->from->languageCode);
	auto character_ = make_shared<character>(message->chat->id, database);
	pathfinder2::character_cache.insert(character_->get_id(), character_);

	const char* master_username = getenv("PF2_INV_MASTER");
	if (master_username != nullptr && message->from->username == master_username)
	{
		pathfinder2::master::get_instance().set_id(message->chat->id);
	}

	character_->set_context(messages["capacity_request"]);
	bot.getApi().sendMessage(character_->get_id(), character_->get_context(), false, 0, pathfinder2::remove_keyboard);
}