#include "context_commands.hpp"

const std::unordered_map<std::string, std::function<void(TgBot::Bot&, TgBot::Message::Ptr, SQLite::Database&)>> pathfinder2::context_commands = {
    {"add_response", add_},
    {"list_response", list_},
    {"remove_response", remove_},
    {"add_item_request", add_item_}
};