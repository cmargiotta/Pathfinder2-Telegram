#include "character_cache.hpp"

#include "database/database.hpp"

using std::shared_ptr;
using pathfinder2::character;

common::cache<int, character> pathfinder2::character_cache(pathfinder2::CHARACTER_CACHE_SIZE_LIMIT, pathfinder2::build_character);

shared_ptr<character> pathfinder2::build_character(const int& id)
{
    static auto& db = pathfinder2::init_database();

    return std::make_shared<character>(id, db);
}