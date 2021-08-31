#include "context_commands.hpp"

const std::unordered_map<std::string, std::function<void(TgBot::Bot&, TgBot::Message::Ptr, SQLite::Database&)>> pathfinder2::context_commands = {
    {"add_response", add_},
    {"list_granularity_request", list_},
    {"item_remove_select", remove_},
    {"add_item_request", add_item_}
};