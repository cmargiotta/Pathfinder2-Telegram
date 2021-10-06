#include "context_commands.hpp"

#include <stdlib.h>

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "common/string_utils.hpp"
#include "character/character_cache.hpp"

void pathfinder2::money_dest_request_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    //Only for exception for non existing characters
    character::get_id(database, text);

    character_->set_data(text);

	character_->set_context(get_message("money_transaction_request", message->from->languageCode));
	bot.getApi().sendMessage(id, character_->get_context());
}