#ifndef STRING_UTILS_HPP_
#define STRING_UTILS_HPP_

#include <string>
#include <vector>
#include <algorithm>

namespace common
{
	static inline bool is_number(const std::string& s)
	{
		return std::all_of(s.begin(), s.end(), ::isdigit);
	}

	static inline void rtrim(std::string &s) 
	{
		s.erase(std::find_if(s.rbegin(), s.rend(),
				std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	}

	static inline void ltrim(std::string &s) 
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(),
				std::not1(std::ptr_fun<int, int>(std::isspace))));
	}

	static inline void trim(std::string &s) 
	{
		ltrim(s);
		rtrim(s);
	}

	static inline std::vector<std::string> split (const std::string& s, std::string delimiter) 
	{
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		std::string token;
		std::vector<std::string> res;

		while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
			token = s.substr (pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back (token);
		}

		res.push_back (s.substr (pos_start));
		return res;
	}
}

#endif // STRING_UTILS_HPP_