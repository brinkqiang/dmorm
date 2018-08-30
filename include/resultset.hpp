#pragma once
#include <unordered_map>
#include <string>
#include <memory>

#ifdef WIN32
#include "mysql.h"
#else
#include "mysql/mysql.h"
#endif

#include "logger.hpp"


namespace gdp
{
namespace db
{


class ResultSet : public std::enable_shared_from_this<ResultSet>
{

    typedef std::unordered_map<std::string, unsigned int > FieldMap;

public:
    ResultSet( MYSQL_RES* r ): m_res( r )
    {
        m_field_num = mysql_num_fields( m_res );
        load_field_map();
    }
    ~ResultSet()
    {
        if ( m_res )
        {
            mysql_free_result( m_res );
            m_row = nullptr;
            m_res = nullptr;
        }
    }

    std::shared_ptr<ResultSet> first()
    {

        if ( m_res )
        {
            if ( !m_row )
            {
                m_row = mysql_fetch_row( this->m_res );
            }
            else
            {
                mysql_field_seek( this->m_res, 0 );
                m_row = mysql_fetch_row( this->m_res );
            }

            return shared_from_this();
        }

        return nullptr;
    }

    int get_int_at( unsigned int idx )
    {
        if ( idx >= m_field_num )
        {
            elog( "column index out of range" );
            return 0;
        }

        if ( m_row )
        {
            return std::stoi( m_row[idx] );
        }

        return 0;
    }

    int  get_int( const std::string& key )
    {
        if ( m_row )
        {
            auto field =  m_field_map.find( key );

            if ( field != m_field_map.end() )
            {
                unsigned int idx = field->second;
                return std::stoi( m_row[idx] );
            }
        }

        return 0;
    }

    std::string get_string( const std::string& key )
    {
        if ( m_row )
        {
            auto field =  m_field_map.find( key );

            if ( field != m_field_map.end() )
            {
                unsigned int idx = field->second;
                return std::string( m_row[idx] );
            }
        }

        return "";
    }

    std::string get_string_at( unsigned int idx )
    {
        if ( idx >= m_field_num )
        {
            std::cerr << "column index out of range" << std::endl;
            return 0;
        }

        if ( m_row )
        {
            return std::string( m_row[idx] );
        }

        return "";
    }


    float get_float( const std::string& key )
    {
        if ( m_row )
        {
            auto field =  m_field_map.find( key );

            if ( field != m_field_map.end() )
            {
                unsigned int idx = field->second;
                return std::stof( m_row[idx] );
            }

        }

        return 0;
    }

    float  get_float_at( unsigned int idx )
    {
        if ( idx >= m_field_num )
        {
            std::cerr << "column index out of range" << std::endl;
            return 0;
        }

        if ( m_row )
        {
            return std::stof( m_row[idx] );
        }

        return 0;
    }

    long long get_llong( const std::string& key )
    {
        if ( m_row )
        {
            auto field =  m_field_map.find( key );

            if ( field != m_field_map.end() )
            {
                unsigned int idx = field->second;
                return std::stoll( m_row[idx] );
            }
        }

        return 0;
    }

    float  get_llong_at( unsigned int idx )
    {
        if ( idx >= m_field_num )
        {
            std::cerr << "column index out of range" << std::endl;
            return 0;
        }

        if ( m_row )
        {
            return std::stoll( m_row[idx] );
        }

        return 0;
    }



    bool next()
    {
        if ( m_res )
        {
            m_row = mysql_fetch_row( m_res );

            if ( m_row )
            {
                return true;
            }
        }

        return false;
    }

    my_ulonglong count()
    {
        return mysql_num_rows( m_res );
    }

private:
    void load_field_map()
    {
        unsigned int num  = mysql_num_fields( m_res );
        MYSQL_FIELD* fields = mysql_fetch_fields( m_res );

        for ( unsigned int i = 0; i < num ; i ++ )
        {
            m_field_map[fields[i].name ]  = i ;
        }
    }

    MYSQL_RES* m_res  = nullptr;
    MYSQL_ROW  m_row  = nullptr;
    FieldMap m_field_map;
    unsigned int m_field_num = 0;

};

typedef std::shared_ptr<ResultSet> ResultSetPtr;
}
}
