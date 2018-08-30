#pragma once
#include <string>
#include <stdint.h>
#include <assert.h>

namespace gdp
{
namespace db
{
static inline int32_t EscapeMySQLString( const char* from, int32_t from_length, char* to, int32_t to_length )
{
    assert( from && to );

    if ( from_length * 2 + 1 < to_length )
    {
        return -1;
    }

    int32_t result_length = 0;

    for ( int32_t index = 0; index < from_length; ++index )
    {
        char c = from[index];

        switch ( c )
        {
        case '\0':
            to[result_length++] = '\\';
            to[result_length++] = '0';
            break;

        case '\n':
            to[result_length++] = '\\';
            to[result_length++] = 'n';
            break;

        case '\r':
            to[result_length++] = '\\';
            to[result_length++] = 'r';
            break;

        case 0x1a:
            to[result_length++] = '\\';
            to[result_length++] = 'Z';
            break;

        case '\'':
            to[result_length++] = '\\';
            to[result_length++] = '\'';
            break;

        case '"':
            to[result_length++] = '\\';
            to[result_length++] = '\"';
            break;

        case '\\':
            to[result_length++] = '\\';
            to[result_length++] = '\\';
            break;

        default:
            to[result_length++] = c;
        }
    }

    return result_length;
}

static inline std::string EscapeString( const std::string& from )
{
    std::string to;
    to.resize( from.size() * 2 + 1 );
    int32_t size = EscapeMySQLString( from.c_str(), from.size(), &*to.begin(), to.size() );
    to.resize( size );
    return to;
}

}
}
