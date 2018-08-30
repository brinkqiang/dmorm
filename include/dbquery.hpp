#pragma once
#include "escape_string.h"
#include "resultset.hpp"

namespace gdp
{
namespace db
{
class DBQuery
{
public:
    typedef std::function<void( ResultSetPtr ) > ResultHandler;
    DBQuery& into( const std::string& tbName )
    {
        m_table = tbName;
        m_sql.write( " {} ", tbName );
        return *this;
    }
    DBQuery& create( const std::string& tbName, bool check = false )
    {
        if ( check )
        {
            m_sql.write( " {} IF NOT EXISTS ", tbName );
        }
        else
        {
            m_sql.write( " {} ", tbName );
        }

        return *this;
    }
    DBQuery& begin()
    {
        m_sql << " ( " ;
        return *this;
    }

    DBQuery& end()
    {
        m_sql << " ) " ;
        return *this;
    }

    DBQuery& def( const std::string&   key,
                  const std::string& type,
                  int length = 0,
                  const std::string& dft = "", bool inc  = false )
    {

        if ( definitions.size() > 0 )
        {
            m_sql << " , ";
        }

        fmt::MemoryWriter lenStr;

        if ( length > 0 )
        {
            lenStr << "(" << length << ")";
        }

        //lenStr[1]  = '[';
        fmt::MemoryWriter defStr;

        defStr.write( " {} {}{} {} ", key, type, length > 0 ? lenStr.c_str() : "", inc ? " AUTO_INCREMENT " : "" );
        m_sql << defStr.c_str();
        return *this;
    }


    template <typename ... Args>
    DBQuery& insert( const Args& ... args )
    {
        clear();
        int argLen = sizeof ...( Args ) - 1;
        m_sql << " insert into " << m_table ;

        if ( argLen > 0 )
        {
            m_sql << "( ";
        }

        fmt::MemoryWriter format;

        for ( int i  = 0; i   < argLen ; i++ )
        {
            if ( i < argLen - 1 )
            {
                format << " {}, ";
            }
            else
            {
                format << " {} ";
            }
        }

        //std::cout << "format is " << format.c_str() << std::endl;
        m_sql.write( format.c_str(), args... );

        if ( argLen > 0 )
        {
            m_sql.write( " )  " );
        }

        return *this;
    }

    template <typename ... Args>
    DBQuery& update( const Args& ... args )
    {
        clear();
        int argLen = sizeof ...( Args ) - 1;
        m_sql << " update " << m_table ;

        fmt::MemoryWriter format;

        for ( int i  = 0; i   < argLen ; i++ )
        {
            if ( i < argLen - 1 )
            {
                format << " {}, ";
            }
            else
            {
                format << " {} ";
            }
        }

        //std::cout << "format is " << format.c_str() << std::endl;
        m_sql.write( format.c_str(), args... );

        return *this;
    }

    DBQuery& set( const std::string& term )
    {
        fmt::MemoryWriter termStr;
        termStr.write( " {} ", term );
        sets.push_back( termStr.c_str() );

        if ( sets.size() <= 1 )
        {
            m_sql << " set " << termStr.c_str();
        }
        else
        {
            m_sql << " ," << termStr.c_str();
        }

        return *this;
    }

    template<class T>
    DBQuery& set( const std::string& key, T val )
    {
        fmt::MemoryWriter termStr;
        termStr.write( " {} = {} ", key,  val );
        sets.push_back( termStr.c_str() );

        if ( sets.size() <= 1 )
        {
            m_sql << " set " << termStr.c_str();
        }
        else
        {
            m_sql << " ," << termStr.c_str();
        }

        return *this;
    }

    DBQuery& del()
    {
        clear();
        m_sql << "delete  from " << m_table;
        return *this;
    }

    DBQuery& set( const std::string& key, const char*   val )
    {
        return this->set( key, std::string( val ) );
    }
    DBQuery& set( const std::string& key, const std::string& val )
    {
        fmt::MemoryWriter termStr;
        auto str = gdp::db::EscapeString( val );
        termStr.write( " {} = \"{}\" ", key, str );
        sets.push_back( termStr.c_str() );

        if ( sets.size() <= 1 )
        {
            m_sql << " set " << termStr.c_str();
        }
        else
        {
            m_sql << " ," << termStr.c_str();
        }

        return *this;
    }

    template <class T>
    std::string printarg( T t )
    {
        fmt::MemoryWriter val ;
        val << t ;
        return val.c_str() ;
    }



    std::string printarg( const char*   t )
    {
        auto str = gdp::db::EscapeString( t );
        return std::string( "\"" ) + str + "\"";
    }

    std::string printarg( const std::string& t )
    {
        auto str = gdp::db::EscapeString( t );
        return std::string( "\"" ) + str + "\"";
    }



    template <typename ... Args>
    DBQuery& values( const Args& ... args )
    {
        int argLen = sizeof ...( Args ) - 1;
        m_sql << " values " << " ( "  ;

        fmt::MemoryWriter format;

        for ( int i  = 0; i   < argLen ; i++ )
        {
            if ( i < argLen - 1 )
            {
                format << " {}, ";
            }
            else
            {
                format << " {} ";
            }
        }

        //std::cout << "format is " << format.c_str() << std::endl;
        m_sql.write( format.c_str(), printarg( args )... );
        m_sql.write( " )  " );
        return *this;
    }



    template <typename ... Args>
    DBQuery& select( const Args& ... args )
    {
        clear();
        int argLen = sizeof ...( Args ) - 1;
        m_sql << "select " ;

        fmt::MemoryWriter format;

        for ( int i  = 0; i   < argLen  ; i++ )
        {
            if ( i < argLen - 1 )
            {
                format << " {}, ";
            }
            else
            {
                format << " {} ";
            }
        }

        //std::cout << "format is " << format.c_str() << std::endl;
        m_sql.write( format.c_str(), args... );
        m_sql.write( " from {} ", m_table );
        return *this;
    }
    DBQuery& select( const std::string& selData )
    {
        clear();
        m_sql.write( "select {} from {} ", selData, m_table );
        return *this;
    }

    DBQuery& table( const std::string& tbName )
    {
        m_table = tbName;
        return *this;
    }

    DBQuery& where( const std::string& key,  const char* term )
    {
        return this->where( key, "=", term );
    }
    DBQuery& where( const std::string& key, const std::string& op, const char* term )
    {
        return where( key, op, std::string( term ) );
    }
    DBQuery& where( const std::string& key, const std::string& op, const std::string& term )
    {
        fmt::MemoryWriter termStr;
        auto str = gdp::db::EscapeString( term );
        termStr.write( "{} {} \"{}\"", key, op, str );
        wheres.push_back( termStr.c_str() );

        m_sql.write( wheres.size() > 1 ? " and {} " : " where {} ", termStr.c_str() );
        return *this;
    }
    template <typename T>
    DBQuery& where( T term )
    {
        fmt::MemoryWriter termStr;
        termStr.write( " {} ",  term );
        wheres.push_back( termStr.c_str() );

        m_sql.write( wheres.size() > 1 ? " and  {} " : " where {} ", term );
        return *this;
    }


    template <typename T>
    DBQuery& where( const std::string& key,  T   term )
    {
        return where<T>( key, "=", term );
    }

    template <typename T>
    DBQuery& where( const std::string& key, const std::string& op, T   term )
    {
        fmt::MemoryWriter termStr;
        termStr.write( " {} {} {} ", key, op, term );
        wheres.push_back( termStr.c_str() );
        //ugly way to do this
        m_sql.write( wheres.size() > 1 ? " and {} " : " where {} ", termStr.c_str() );
        return *this;
    }

    template<typename T>
    DBQuery& or_where( const std::string& key, const std::string& op, T  term )
    {
        fmt::MemoryWriter termStr;
        termStr.write( " {} {} {} ", key, op, term );
        wheres.push_back( termStr.c_str() );
        m_sql.write( " or {} ", termStr.c_str() );
        return *this;
    }

    DBQuery& limit( unsigned int count )
    {
        m_sql.write( " limit {} ", count );

        return *this;
    }
    DBQuery& limit( unsigned int offset, unsigned int count )
    {
        m_sql.write( " limit {}, {}  ", offset, count );
        return *this;
    }
    DBQuery& group_by( const std::string& col )
    {
        m_sql.write( " group by {} ", col );
        return *this;
    }


    DBQuery& order_by( const std::string& col, const std::string& type = "asc" )
    {
        m_sql.write( " order by {} {} ", col, type );
        return *this;
    }

    DBQuery& join( const std::string& tb, const std::string& lId, const std::string& op, const std::string& rId )
    {
        return inner_join( tb, lId, op, rId );
    }

    DBQuery& inner_join( const std::string& tb, const std::string& lId, const std::string& op, const std::string& rId )
    {
        m_sql.write( " inner join {} on {} {} {} ", tb, lId, op, rId );
        return *this;
    }

    DBQuery& left_join( const std::string& tb, const std::string& lId, const std::string& op, const std::string& rId )
    {
        m_sql.write( " left join {} on {} {} {} ", tb, lId, op, rId );
        return *this;
    }

    DBQuery& right_join( const std::string& tb, const std::string& lId, const std::string& op, const std::string& rId )
    {
        m_sql.write( " right join {} on {} {} {} ", tb, lId, op, rId );
        return *this;
    }

    const char*   sql() const
    {
        return m_sql.c_str();
    }


    void clear()
    {
        m_sql.clear();
        wheres.clear();
        sets.clear();
    }


private:

    std::vector<std::string > definitions;
    std::vector<std::string > wheres;
    std::vector<std::string > sets ;
    std::string  m_table;
    fmt::MemoryWriter m_sql ;
};

}
}
