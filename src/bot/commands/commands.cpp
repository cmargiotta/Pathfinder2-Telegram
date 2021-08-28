#include "commands.hpp"

const std::unordered_map<std::string, std::function<void(TgBot::Bot&, TgBot::Message::Ptr, SQLite::Database&)>> pathfinder2::commands = {
	{"start", _start},
	{"reset", _reset},
	{"add", _add},
	{"remove", _remove},
	{"list", _list},
	{"set_capacity", _set_capacity},
	{"money_transaction", _money_transaction},
	{"get_money", _get_money}
};