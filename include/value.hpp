#pragma once

#include <sqlite3.h>

namespace hsqlite {
  class value {
  private:
    friend class statement;
    sqlite3_value* val;
  public:
    value(sqlite3_value* v) : val(v) { }
  };
}