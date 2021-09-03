#include "commands.hpp"

#include <sstream>
#include <string>

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

using std::stringstream;

void pathfinder2::_get_money(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();

	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    stringstream text;
    auto cp = character_->get_cp();
    
    auto gp = cp/100;
    cp -= gp*100;

    auto sp = cp/10;
    cp -= sp*10;

    text << gp << "gp\n" << sp << "sp\n" << cp << "cp";

	character_->set_context("");
    bot.getApi().sendMessage(id, text.str());
	bot.getApi().sendMessage(id, messages["default_message"], false, 0, pathfinder2::get_default_keyboard(master::get_instance().is_master(id)));
}