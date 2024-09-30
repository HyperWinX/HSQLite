#include <sqlite3.h>

#include "database.hpp"
#include "constants.hpp"

namespace hsqlite {
  class transaction {
  private:
    database& db;
  public:
    transaction(database& db) : db(db) { }

    error_code rollback() {
      return db.exec("ROLLBACK;");
    }

    error_code commit() {
      return db.exec("COMMIT;");
    }

    ~transaction() = default;
  };
}