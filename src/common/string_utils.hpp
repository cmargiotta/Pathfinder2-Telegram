#ifndef STRING_UTILS_HPP_
#define STRING_UTILS_HPP_

#include <set>
#include <cmath>
#include <cctype>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>

namespace common
{
	static inline const std::set<char> to_escape ({'.', '-', '+', '(', ')', '=', '<', '>', '!', '[', ']'});

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
		return std::all_of(s.begin(), s.end(), ::isdigit);
	}

	static inline bool is_float_number(const std::string& s)
	{
		if (std::count(s.begin(), s.end(), '.') <= 1)
		{
			return std::all_of(s.begin(), s.end(), 
				[](char c){
					return std::isdigit(c) || c == '.';
				}) &&
				s.back() != '.' &&
				s.front() != '.'; 
		}

		return false;
	}

	static inline bool is_bulk_string(std::string s)
	{
		if (s.back() == 'L' || s.back() == 'l')
		{
			s = s.substr(0, s.size() - 1); 
		}

		return is_float_number(s); 
	}

	static inline std::string bulk_to_string(double bulk)
	{
		std::stringstream text; 
		
		if (bulk - int(bulk) < 0.0001)
		{
			//Bulk is only an int
			text << std::fixed << std::setprecision(0) << bulk;
		}
		else if (bulk >= 1.0)
		{
			//If bulk is only a number
			text << std::fixed << std::setprecision(2) << bulk;
		}
		else
		{
			if (bulk == 0.1)
			{
				//If it is only 'L'
				text << 'L';
			}
			else
			{
				//If it contains a number + 'L'
				text << std::fixed << std::setprecision(2) << bulk*10 << 'L';
			}
		}
		
		return text.str();  
	}

	static inline double parse_bulk(std::string bulk)
	{
		double res = 1; 

		if (bulk.back() == 'L' || bulk.back() == 'l')
		{
			res = 0.1;
			bulk = bulk.substr(0, bulk.size() - 1); 

			if (bulk.empty())
			{
				return res; 
			}
		}

		if (!common::is_float_number(bulk))
		{
			throw std::runtime_error("generic_error");
		}

		res *= std::stod(bulk.c_str()); 

		return res; 
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

		bool description_found = false; 

		do
		{
			pos_end = s.find (delimiter, pos_start);
			
			if (description_found && pos_start == pos_end)
			{
				pos_start--; 
			}
			
			token = s.substr (pos_start, pos_end - pos_start);
			
			pos_start = pos_end + delim_len;

			if (token[0] == '"')
			{
				description_found = true; 
				res.push_back("");
			}
			
			if (description_found)
			{
				if (token.back() == '"')
				{
					res.back() += token;
					description_found = false;
				}
				else
				{
					res.back() += token; 
				}
			}
			else
			{
				res.push_back(token);
			}
		} while (pos_end != std::string::npos); 
		
		return res;
	}
}

#endif // STRING_UTILS_HPP_
