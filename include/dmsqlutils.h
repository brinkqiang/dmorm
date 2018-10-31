/**
 * @file sqltrait.h
 * @brief
 * @author arthur fatih@qq.com
 * @version 1.0.0
 * @date 2017-11-24
 */

#pragma once
#include "escape_string.h"

typedef std::shared_ptr<sql::ResultSet> ResultSetSPtr;
typedef std::unique_ptr<sql::ResultSet> ResultSetUPtr;


template <typename T>
struct SqlTypeTrait
{
    SqlTypeTrait( fmt::MemoryWriter& wt ): writer( wt )
    {
    }
    SqlTypeTrait<T>& operator()( T&   val )
    {

        writer.write( " {} ", val );
        return *this;
    }
    fmt::MemoryWriter& writer;
};


template <>
struct SqlTypeTrait<const char* >
{
    SqlTypeTrait( fmt::MemoryWriter& wt ): writer( wt )
    {
    }
    SqlTypeTrait<const char* >& operator()( const char*&     val )
    {
        auto str = gdp::db::EscapeString( val );
        writer.write( " \"{}\" ", str );
        return *this;
    }
    fmt::MemoryWriter& writer;
};

template <>
struct SqlTypeTrait<const std::string& >
{
    SqlTypeTrait( fmt::MemoryWriter& wt ): writer( wt )
    {
    }
    SqlTypeTrait<const std::string& >& operator()( const std::string&    val )
    {
        auto str = gdp::db::EscapeString( val );
        writer.write( " \"{}\" ", str );
        return *this;
    }
    fmt::MemoryWriter& writer;
};
