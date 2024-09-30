#pragma once

#include "constants.hpp"
#include "database.hpp"
#include <sqlite3.h>

namespace hsqlite {
  class blob {
  private:
    sqlite3_blob* blb;
    error_code code;
  public:
    // sqlite3_blob_open
    blob(database& db, std::string_view zdb, std::string_view table, std::string_view column, std::int64_t row, int flags) {
      code = static_cast<error_code>(sqlite3_blob_open(db.db, zdb.begin(), table.begin(), column.begin(), row, flags, &blb));
    }

    // sqlite3_blob_read
    error_code read(void* buf, int n, int offset) {
      return static_cast<error_code>(sqlite3_blob_read(blb, buf, n, offset));
    }

    // sqlite3_blob_write
    error_code write(const void* buf, int n, int offset) {
      return static_cast<error_code>(sqlite3_blob_write(blb, buf, n, offset));
    }

    // sqlite3_blob_reopen
    error_code reopen(std::int64_t row) {
      return static_cast<error_code>(sqlite3_blob_reopen(blb, row));
    }

    // sqlite3_blob_bytes
    int bytes() {
      return sqlite3_blob_bytes(blb);
    }

    // sqlite3_blob_close
    ~blob() {
      sqlite3_blob_close(blb);
    }
  };
}