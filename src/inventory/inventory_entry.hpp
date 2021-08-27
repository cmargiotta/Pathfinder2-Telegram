#ifndef PATHFINDER2_INVENTORY_ENTRY 
#define PATHFINDER2_INVENTORY_ENTRY

#include <string>
#include <cstdint>

namespace pathfinder2
{
	class inventory_entry {
		protected: 
			int					owner; 
			std::string 		name; 
			std::string			category;
			std::string			bulk_string;
			float	   			bulk; 
			int					quantity; 

		public: 
			inventory_entry() = default;
			inventory_entry(int owner, const std::string& name, float bulk, const std::string& category);
			virtual ~inventory_entry();

			const std::string& get_name() const;
			int get_quantity() const;

			virtual const std::string& get_category() const;
			virtual float get_bulk() const; 
			virtual const std::string& get_url() const; 
			virtual const std::string& get_description() const; 

			virtual void update_quantity(int delta);
			virtual void set_category(const std::string& category);
			virtual void set_bulk(const std::string& bulk);
			virtual void set_description(const std::string& description);
			virtual void set_url(const std::string& url);
	};
}

#endif