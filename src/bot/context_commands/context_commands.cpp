#include "context_commands.hpp"

const std::unordered_map<std::string, std::function<void(TgBot::Bot&, TgBot::Message::Ptr, SQLite::Database&)>> pathfinder2::context_commands = {
    {"add_response", add_},
    {"list_granularity_request", list_},
    {"item_remove_select", remove_},
    {"add_item_request", add_item_},
	{"capacity_request", set_capacity_},
	{"list_detail_selection", list_detail_},
	{"custom_item_info_request", add_custom_item_},
	{"money_transaction_request", money_transaction_},
	{"item_edit_request", edit_item_master_},
	{"item_delete_request", delete_item_master_},
	{"item_register_request", register_item_master_},
	{"edit_selection", edit_selection_},
	{"edit_value_request", edit_value_request_},
	{"give_request", give_request_},
	{"give_response", give_item_},
	{"broadcast_message_content_req", broadcast_message_content_req_master_},
	{"money_dest_request", money_dest_request_},
	{"money_bulk_request", set_coin_bulk_master_}
};