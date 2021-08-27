#include "character.hpp"

#include "common/cache.hpp"

namespace pathfinder2
{
	const size_t CHARACTER_CACHE_SIZE_LIMIT = 100;

	static common::cache<int, character> character_cache (CHARACTER_CACHE_SIZE_LIMIT);
}