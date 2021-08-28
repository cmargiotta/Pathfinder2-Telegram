#ifndef LOCAL_DATA_HPP_
#define LOCAL_DATA_HPP_

#include <nlohmann/json.hpp>

namespace pathfinder2
{
	nlohmann::json& get_commands();
	nlohmann::json& get_messages();
}
#endif // LOCAL_DATA_HPP_