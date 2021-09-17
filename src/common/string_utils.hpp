#ifndef STRING_UTILS_HPP_
#define STRING_UTILS_HPP_

#include <set>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>

namespace common
{
	static inline const std::set<char> to_escape ({'.', '-', '+', '(', ')'});

	//Used for escaping description when loading from/in database
	static inline std::string escape(const std::string& src, const std::set<char>& escapee, const char marker)
	{
		std::string r;

		for (char c: src)
		{
			if (escapee.find(c) != escapee.end())
			{
				r += marker;
			}

			r += c; 
		}

		return r;
	}

	static inline bool is_number(const std::string& s)
	{
		return (std::isdigit(s[0]) || s[0] == '-') && std::all_of(s.begin()+1, s.end(), ::isdigit);
	}

	static inline void trim(std::string& str, const std::string& whitespace = " \t\n")
	{
		const auto str_begin = str.find_first_not_of(whitespace);

		const auto str_end = str.find_last_not_of(whitespace);
		const auto str_range = str_end - str_begin + 1;

		str = str.substr(str_begin, str_range);
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