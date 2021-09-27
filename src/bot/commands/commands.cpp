#include "commands.hpp"

const std::unordered_map<std::string, std::function<void(TgBot::Bot&, TgBot::Message::Ptr, SQLite::Database&)>> pathfinder2::commands = {
	{"start", _start},
	{"reset", _reset},
	{"add", _add},
	{"remove", _remove},
	{"list", _list},
	{"set_capacity", _set_capacity},
	{"money_transaction", _money_transaction},
	{"get_money", _get_money},
	{"register_item_master", _register_item_master},
	{"delete_item_master", _delete_item_master},
	{"edit_item_master", _edit_item_master},
	{"send_broadcast", _send_broadcast_master},
	{"give", _give_master}
};