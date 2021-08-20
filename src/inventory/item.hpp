#include <string>
#include <cstdint>

namespace pathfinder2
{
    class item 
    {
        private: 
            std::string url; 
            std::string name; 
            std::string description;
            float       bulk; 
        
        public:
            item(const std::string& name, const std::string& url, const std::string& description, float bulk) noexcept; 
            
            ~item() = default;

            const std::string&  get_url() const noexcept;
            const std::string&  get_name() const noexcept;
            const std::string&  get_description() const noexcept;
            float               get_bulk() const noexcept;
    };
}