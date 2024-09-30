# HSQLite
HSQLite is a C++ wrapper for SQLite that enables developers to utilize SQLite in more modern and efficient ways.  
- Functions such as sqlite3_open and sqlite3_close have been encapsulated in ctors and dtors.  
- Transactions have been simplified for ease of use.  
- The library is easy to integrate into existing projects.

## Installation
1. Put repository in any directory, for example, dist
2. Add following to your CMakeLists.txt
```cmake
add_subdirectory(dist/HSQLite)
```
3. Now you can link HSQLite to your executable:
```cmake
target_link_libraries(<program> PUBLIC HSQLite)
```

## Basic usage
```c++
#include <hsqlite.hpp> // Include main header

using flag = hsqlite::flag;

int main() {
  // Open (create if no file) database as read/write
  hsqlite::database db("test.db", flag::OPEN_READWRITE | flag::OPEN_CREATE);
  
  if (db.get_last_error() != hsqlite::error_code::OK) {
    return 1;
  }

  // Begin transaction
  hsqlite::transaction tr(db);
  // Create table if it doesnt exist - test query
  db.exec("CREATE IF NOT EXISTS foo(id INT PRIMARY KEY AUTO_INCREMENT, str VARCHAR(16));");
  // Commit changes
  tr.commit();

  // Database is closed automatically
}
```

## Advanced usage
### Database API
- `hsqlite::database::cacheflush() -> sqlite3_db_cacheflush()`
- `hsqlite::database::config() -> sqlite3_db_config()`
- `hsqlite::database::release_memory() -> sqlite3_db_release_memory()`
- `hsqlite::database::filename() -> sqlite3_db_filename()`
- `hsqlite::database::exec() -> sqlite3_exec()`
- `hsqlite::database::get_last_error() -> returns last error - class constructor sets error code`
