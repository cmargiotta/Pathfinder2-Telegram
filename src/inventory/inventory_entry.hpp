#ifndef PATHFINDER2_INVENTORY_ENTRY 
#define PATHFINDER2_INVENTORY_ENTRY

#include <string>
#include <cstdint>

namespace pathfinder2
{
	class inventory_entry {
		protected: 
			std::string			owner; 
			std::string 		name; 
			std::string			category;
			std::string			bulk_string;
			float	   			bulk; 
			int					quantity; 

		public: 
			inventory_entry() = default;
			inventory_entry(const std::string& owner, const std::string& name, float bulk, const std::string& category);
			inventory_entry(const char* owner, const char* name, float bulk, const char* category);
			virtual ~inventory_entry();

			const std::string& get_name() const; 
			const std::string& get_category() const;
			float get_bulk() const; 
			int get_quantity() const;

			virtual void update_quantity(int delta);

			virtual const std::string& get_url() const; 
			virtual const std::string& get_description() const; 
	};
}

#endif