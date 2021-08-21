#include <list>
#include <utility>
#include <unordered_map>

namespace common
{
	template <typename Key, typename Value> 
	class cache
	{
		private:  
			std::list<std::pair<Key, Value>>				  			list; 
			std::unordered_map<Key, typename decltype(list)::iterator> 	map; 

			std::size_t	size_limit; 

		public:  
			explicit cache(std::size_t _size_limit):  
				size_limit(_size_limit)
			{}
			
			~cache() = default;

			//Add a new item to the cache
			const Value& insert(const Key& key, const Value& value)  
			{
				auto map_element = map.find(key); 

				if (map_element == map.end())
				{
					//value is not in map  
					if (map.size() == size_limit)
					{
						//the cache is full, remove the last item
						map.erase(list.back().first); 
						list.pop_back();
					}
				}
				else  
				{
					//value found, erase it
					list.erase(map_element->second);
				}

				list.push_front(std::make_pair(key, value));
				map[key] = list.begin(); 

				return list.front().second;
			}

			//Given the key, get the corresponding item from the queue
			inline const Value& get(const Key& key) const
			{
				return map.at(key)->second; 
			}

			inline const Value& operator[](const Key& key) const
			{
				return get(key);
			}
	};
}