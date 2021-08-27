#ifndef PATHFINDER2_CACHE
#define PATHFINDER2_CACHE

#include <list>
#include <memory>
#include <utility>
#include <unordered_map>

namespace common
{
	template <typename Key, typename Value> 
	class cache
	{
		private:  
			std::list<std::pair<Key, std::shared_ptr<Value>>>			list; 
			std::unordered_map<Key, typename decltype(list)::iterator> 	map; 

			std::size_t	size_limit; 

		public:  
			explicit cache(std::size_t _size_limit):  
				size_limit(_size_limit)
			{}
			
			~cache() = default;

			//Add a new item to the cache
			std::shared_ptr<Value> insert(const Key& key, std::shared_ptr<Value> value)  
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
			inline std::shared_ptr<Value> get(const Key& key)
			{
				return map.at(key)->second; 
			}

			inline std::shared_ptr<Value> operator[](const Key& key)
			{
				return get(key);
			}
	};
}

#endif