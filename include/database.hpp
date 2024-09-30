#pragma once

#include <string_view>

#include <sqlite3.h>

#include "constants.hpp"


namespace hsqlite {
  class database {
  private:
    friend class statement;
    friend class blob;

    sqlite3* db;
    std::string_view filename_;
    error_code last_error;
  public:
    database(std::string_view filename) {
      this->filename_ = filename;
      last_error = static_cast<error_code>(sqlite3_open(filename.begin(), &db));
    }

    database(std::string_view filename, int flags, std::string_view zfs = "") {
      last_error = static_cast<error_code>(sqlite3_open_v2(filename.begin(), &db, flags, zfs.begin()));
    }

    database(database&) = delete;

    database(database&&) = default;

    error_code cacheflush() {
      return static_cast<error_code>(sqlite3_db_cacheflush(db));
    }

    template<typename... Args>
    error_code config(int op, Args... args) {
      return static_cast<error_code>(sqlite3_db_config(db, op, std::forward<Args>(args)...));
    }

    error_code release_memory() {
      return static_cast<error_code>(sqlite3_db_release_memory(db));
    }

    std::string_view filename() {
      return filename_;
    }

    error_code get_last_error() {
      return last_error;
    }

    error_code exec(std::string_view query, int(*callback)(void*, int, char**, char**) = nullptr, void* v = nullptr, char** errmsg = nullptr) {
      return static_cast<error_code>(sqlite3_exec(db, query.begin(), callback, v, errmsg));
    }
  };
}