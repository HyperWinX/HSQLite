#pragma once

#include <cstring>
#include <string_view>

#include <sqlite3.h>

#include "database.hpp"
#include "constants.hpp"
#include "value.hpp"

namespace hsqlite {
  class statement {
  private:
    sqlite3_stmt* stmt;
    error_code last_error;

  public:
    using deleter_cb = void(*)(void*);
    statement() = delete;
    statement(statement&) = delete;
    // sqlite3_prepare_v2 UTF-8 constructor
    statement(database& db, std::string_view query, int bytes, const char** tail = nullptr) {
        last_error = static_cast<error_code>(sqlite3_prepare_v2(db.db, query.begin(), bytes, &stmt, tail));
    }
    
    // sqlite3_prepare_v3 UTF-8 constructor
    statement(database& db, std::string_view query, int bytes, unsigned int flags, const char** tail = 0) {
      last_error = static_cast<error_code>(sqlite3_prepare_v3(db.db, query.begin(), bytes, flags, &stmt, tail));
    }
    
    // sqlite3_prepare16_v2 UTF-16 constructor
    statement(database& db, std::u16string_view query, int bytes, const void** tail = 0) {
      last_error = static_cast<error_code>(sqlite3_prepare16_v2(db.db, query.begin(), bytes, &stmt, tail));
    }

    // sqlite3_prepare16_v3 UTF-16 constructor
    statement(database& db, std::u16string_view query, int bytes, unsigned int flags, const void** tail = 0) {
      last_error = static_cast<error_code>(sqlite3_prepare16_v3(db.db, query.begin(), bytes, flags, &stmt, tail));
    }
    
    // sqlite3_bind_blob
    error_code bind_blob(statement& statemt, int index, const void* value, int n, deleter_cb deleter) {
      return static_cast<error_code>(sqlite3_bind_blob(statemt.stmt, index, value, n, deleter));
    }

    // sqlite3_bind_blob64
    error_code bind_blob64(statement& statemt, int index, const void* value, std::uint64_t n, deleter_cb deleter) {
      return static_cast<error_code>(sqlite3_bind_blob64(statemt.stmt, index, value, n, deleter));
    }

    // sqlite3_bind_double
    error_code bind_double(statement& statemt, int index, double value) {
      return static_cast<error_code>(sqlite3_bind_double(statemt.stmt, index, value));
    }

    // sqlite3_bind_int
    error_code bind_int(statement& statemt, int index, int value) {
      return static_cast<error_code>(sqlite3_bind_int(statemt.stmt, index, value));
    }

    // sqlite3_bind_int64
    error_code bind_int64(statement& statemt, int index, std::uint64_t value) {
      return static_cast<error_code>(sqlite3_bind_int64(statemt.stmt, index, value));
    }

    // sqlite3_bind_null
    error_code bind_null(statement& statemt, int index) {
      return static_cast<error_code>(sqlite3_bind_null(statemt.stmt, index));
    }

    // sqlite3_bind_text
    error_code bind_text(statement& statemt, int index, std::string_view value, int n, deleter_cb deleter) {
      return static_cast<error_code>(sqlite3_bind_text(statemt.stmt, index, value.begin(), n, deleter));
    }

    // sqlite3_bind_text16
    error_code bind_text16(statement& statemt, int index, std::u16string_view value, int n, deleter_cb deleter) {
      return static_cast<error_code>(sqlite3_bind_text16(statemt.stmt, index, value.begin(), n, deleter));
    }

    // sqlite_bind_text64
    error_code bind_text64(statement& statemt, int index, std::string_view value, std::uint64_t n, deleter_cb deleter, encoding encoding) {
      return static_cast<error_code>(sqlite3_bind_text64(statemt.stmt, index, value.begin(), n, deleter, encoding));
    }

    // sqlite_bind_value
    error_code bind_value(statement& statemt, int index, const value& value) {
      return static_cast<error_code>(sqlite3_bind_value(statemt.stmt, index, value.val));
    }

    // sqlite3_bind_pointer
    error_code bind_pointer(statement& statemt, int index, void* value, const char* x, deleter_cb deleter) {
      return static_cast<error_code>(sqlite3_bind_pointer(statemt.stmt, index, value, x, deleter));
    }

    // sqlite3_bind_zeroblob
    error_code bind_zeroblob(statement& statemt, int index, int n) {
      return static_cast<error_code>(sqlite3_bind_zeroblob(statemt.stmt, index, n));
    }

    // sqlite3_bind_zeroblob64
    error_code bind_zeroblob64(statement& statemt, int index, std::uint64_t n) {
      return static_cast<error_code>(sqlite3_bind_zeroblob64(statemt.stmt, index, n));
    }

    // sqlite3_step
    error_code step() {
      return static_cast<error_code>(sqlite3_step(stmt));
    }

    // sqlite3_column_blob
    template<int col>
    const void* get_column_blob() {
      return sqlite3_column_blob(stmt, col);
    }
    
    // sqlite3_column_double
    template<int col>
    double get_column_double() {
      return sqlite3_column_double(stmt, col);
    }

    // sqlite3_column_int
    template<int col>
    int get_column_int() {
      return sqlite3_column_int(stmt, col);
    }

    // sqlite3_column_int64
    template<int col>
    std::int64_t get_column_int64() {
      return sqlite3_column_int64(stmt, col);
    }
    
    // sqlite3_column_text
    template<int col>
    const std::string_view get_column_text() {
      return { reinterpret_cast<const char*>(sqlite3_column_text(stmt, col)) };
    }

    // sqlite3_column_text
    template<int col>
    const unsigned char* get_column() {
      return sqlite3_column_text(stmt, col);
    }

    // sqlite3_column_text16
    template<int col>
    const std::u16string_view get_column() {
      return { static_cast<const char16_t*>(sqlite3_column_text16(stmt, col)) };
    }

    // sqlite3_column_text16
    const void* get_column_text16(int col) {
      return sqlite3_column_text16(stmt, col);
    }

    // sqlite3_column_value
    template<int col>
    value get_column_value() {
      return sqlite3_column_value(stmt, col);
    }

    // sqlite3_column_bytes
    template<int col>
    int get_column_bytes() {
      return sqlite3_column_bytes(stmt, col);
    }

    // sqlite_column_bytes16
    template<int col>
    int get_column_bytes16() {
      return sqlite3_column_bytes16(stmt, col);
    }

    // sqlite3_column_type
    template<int col>
    type get_column_type() {
      return static_cast<type>(sqlite3_column_type(stmt, col));
    }

    // sqlite3_bind_parameter_count
    int bind_parameter_count() {
      return sqlite3_bind_parameter_count(stmt);
    }

    // sqlite3_bind_parameter_index
    int bind_parameter_index(std::string_view name) {
      return sqlite3_bind_parameter_index(stmt, name.begin());
    }

    // sqlite3_bind_parameter_name
    std::string_view bind_parameter_name_sv(int param) {
      return { sqlite3_bind_parameter_name(stmt, param) };
    }

    // sqlite3_bind_parameter_name
    const char* bind_parameter_name(int param) {
      return sqlite3_bind_parameter_name(stmt, param);
    }


    ~statement() {
      sqlite3_finalize(stmt);
    }
  };
}