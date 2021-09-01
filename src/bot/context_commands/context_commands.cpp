#include "context_commands.hpp"

const std::unordered_map<std::string, std::function<void(TgBot::Bot&, TgBot::Message::Ptr, SQLite::Database&)>> pathfinder2::context_commands = {
    {"add_response", add_},
    {"list_granularity_request", list_},
    {"item_remove_select", remove_},
    {"add_item_request", add_item_},
	{"capacity_request", set_capacity_},
	{"list_detail_selection", list_detail_},
	{"custom_item_info_request", add_custom_item_},
	{"money_transaction_request", money_transaction_}
};