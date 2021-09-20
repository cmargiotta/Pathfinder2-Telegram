#ifndef LOCAL_DATA_HPP_
#define LOCAL_DATA_HPP_

#include <nlohmann/json.hpp>

namespace pathfinder2
{
	const std::string& get_command(const std::string& key, const std::string& locale = "");
	const std::string& get_message(const std::string& key, const std::string& locale = "");
	const std::string& get_command_id(const std::string& key, const std::string& locale = "");
	const std::string& get_message_id(const std::string& key, const std::string& locale = "");
}
#endif // LOCAL_DATA_HPP_