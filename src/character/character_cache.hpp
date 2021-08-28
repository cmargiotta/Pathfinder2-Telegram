#include "character.hpp"

#include <memory>

#include "common/cache.hpp"

namespace pathfinder2
{
	const size_t CHARACTER_CACHE_SIZE_LIMIT = 100;

	std::shared_ptr<character> build_character(const int& id);

	extern common::cache<int, character> character_cache;
}