#ifndef LOCAL_DATA_HPP_
#define LOCAL_DATA_HPP_

#include <nlohmann/json.hpp>

namespace pathfinder2
{
	nlohmann::json& get_commands(const std::string& locale = "");
	nlohmann::json& get_messages(const std::string& locale = "");
}
#endif // LOCAL_DATA_HPP_