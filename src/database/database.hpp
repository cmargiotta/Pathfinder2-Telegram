#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <memory>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

namespace pathfinder2
{
	SQLite::Database& init_database(const std::string& path = "");
}
#endif // DATABASE_HPP_