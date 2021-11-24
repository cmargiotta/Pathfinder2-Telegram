#ifndef DATABASE_SETTINGS
#define DATABASE_SETTINGS

#include <SQLiteCpp/SQLiteCpp.h>

namespace pathfinder2
{
	class settings
	{
		private:
			double coin_bulk;
			SQLite::Database& database; 

			settings(SQLite::Database& database);

		public:
			~settings(); 

			static settings& get_instance(SQLite::Database* database = nullptr);

			double get_coin_bulk() const; 
			void set_coin_bulk(double value); 
	};
}

#endif /* DATABASE_SETTINGS */
