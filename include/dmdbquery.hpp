#pragma once
#include "dmescape_string.h"
#include "dmresultset.hpp"

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
        m_sql += fmt::format( " {} ", tbName );
        return *this;
    }
    DBQuery& create( const std::string& tbName, bool check = false )
    {
        if ( check )
        {
            m_sql += fmt::format( " {} IF NOT EXISTS ", tbName );
        }
        else
        {
            m_sql += fmt::format( " {} ", tbName );
        }

        return *this;
    }
    DBQuery& begin()
    {
        m_sql += " ( ";
        return *this;
    }

    DBQuery& end()
    {
        m_sql += " ) " ;
        return *this;
    }

    DBQuery& def( const std::string&   key,
                  const std::string& type,
                  int length = 0,
                  const std::string& dft = "", bool inc  = false )
    {

        if ( definitions.size() > 0 )
        {
            m_sql += " , ";
        }

        std::string lenStr;

        if ( length > 0 )
        {
            lenStr += fmt::format("({})", length);
        }

        m_sql += fmt::format(" {} {}{} {} ", key, type, length > 0 ? lenStr.c_str() : "", inc ? " AUTO_INCREMENT " : "");

        return *this;
    }


    template <typename ... Args>
    DBQuery& insert( const Args& ... args )
    {
        clear();
        int argLen = sizeof ...( Args );
        m_sql += "insert into ";
        m_sql += m_table ;

        if ( argLen > 0 )
        {
            m_sql += "( ";
        }

        std::string format;

        for ( int i  = 0; i   < argLen ; i++ )
        {
            if ( i < argLen - 1)
            {
                format += " {}, ";
            }
            else
            {
                format += " {} ";
            }
        }

        //std::cout << "format is " << format.c_str() << std::endl;
        m_sql += fmt::format(format.c_str(), args... );

        if ( argLen > 0 )
        {
            m_sql += ( " )  " );
        }

        return *this;
    }

    template <typename ... Args>
    DBQuery& update( const Args& ... args )
    {
        clear();
        int argLen = sizeof ...( Args );
        m_sql += "update ";
        m_sql += m_table ;

        std::string format;

        for ( int i  = 0; i   < argLen ; i++ )
        {
            if ( i < argLen - 1)
            {
                format += " {}, ";
            }
            else
            {
                format += " {} ";
            }
        }

        //std::cout << "format is " << format.c_str() << std::endl;
        m_sql += fmt::format( format.c_str(), args... );

        return *this;
    }

    DBQuery& set( const std::string& term )
    {
        std::string termStr;
        termStr = fmt::format( " {} ", term );
        sets.push_back( termStr.c_str() );

        if ( sets.size() <= 1 )
        {
            m_sql += " set ";
            m_sql += termStr;
        }
        else
        {
            m_sql += " ,";
            m_sql += termStr;
        }

        return *this;
    }

    template<class T>
    DBQuery& set( const std::string& key, T val )
    {
        std::string termStr;
        termStr = fmt::format( " {} = {} ", key,  val );
        sets.push_back( termStr.c_str() );

        if (sets.size() <= 1)
        {
            m_sql += " set ";
            m_sql += termStr;
        }
        else
        {
            m_sql += " ,";
            m_sql += termStr;
        }

        return *this;
    }

    DBQuery& del()
    {
        clear();
        m_sql += "delete  from ";
        m_sql += m_table;
        return *this;
    }

    DBQuery& set( const std::string& key, const char*   val )
    {
        return this->set( key, std::string( val ) );
    }
    DBQuery& set( const std::string& key, const std::string& val )
    {
        std::string termStr;
        auto str = gdp::db::EscapeString( val );
        termStr += fmt::format( " {} = \"{}\" ", key, str );
        sets.push_back( termStr.c_str() );

        if (sets.size() <= 1)
        {
            m_sql += " set ";
            m_sql += termStr;
        }
        else
        {
            m_sql += " ,";
            m_sql += termStr;
        }

        return *this;
    }

    template <class T>
    std::string printarg( T t )
    {
        std::string val = fmt::format("{}", t);
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
        int argLen = sizeof ...( Args );
        m_sql += " values ";
        m_sql += " ( "  ;

        std::string format;

        for ( int i  = 0; i   < argLen ; i++ )
        {
            if ( i < argLen - 1)
            {
                format += " {}, ";
            }
            else
            {
                format += " {} ";
            }
        }

        //std::cout << "format is " << format.c_str() << std::endl;
        m_sql += fmt::format( format.c_str(), printarg( args )... );
        m_sql += ( " )  " );
        return *this;
    }



    template <typename ... Args>
    DBQuery& select( const Args& ... args )
    {
        clear();
        int argLen = sizeof ...( Args );
        m_sql += "select " ;

        std::string format;

        for ( int i  = 0; i   < argLen  ; i++ )
        {
            if ( i < argLen - 1)
            {
                format += " {}, ";
            }
            else
            {
                format += " {} ";
            }
        }

        //std::cout << "format is " << format.c_str() << std::endl;
        m_sql += fmt::format( format.c_str(), args... );
        m_sql += fmt::format( " from {} ", m_table );
        return *this;
    }
    DBQuery& select( const std::string& selData )
    {
        clear();
        m_sql += fmt::format( "select {} from {} ", selData, m_table );
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
        std::string termStr;
        auto str = gdp::db::EscapeString( term );
        termStr += fmt::format( "{} {} \"{}\"", key, op, str );
        wheres.push_back( termStr.c_str() );

        m_sql += fmt::format( wheres.size() > 1 ? " and {} " : " where {} ", termStr.c_str() );
        return *this;
    }
    template <typename T>
    DBQuery& where( T term )
    {
        std::string termStr;
        termStr += fmt::format( " {} ",  term );
        wheres.push_back( termStr.c_str() );

        m_sql += fmt::format( wheres.size() > 1 ? " and  {} " : " where {} ", term );
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
        std::string termStr;
        termStr += fmt::format( " {} {} {} ", key, op, term );
        wheres.push_back( termStr.c_str() );
        //ugly way to do this
        m_sql += fmt::format( wheres.size() > 1 ? " and {} " : " where {} ", termStr.c_str() );
        return *this;
    }

    template<typename T>
    DBQuery& or_where( const std::string& key, const std::string& op, T  term )
    {
        std::string termStr;
        termStr += fmt::format( " {} {} {} ", key, op, term );
        wheres.push_back( termStr.c_str() );
        m_sql += fmt::format( " or {} ", termStr.c_str() );
        return *this;
    }

    DBQuery& limit( unsigned int count )
    {
        m_sql += fmt::format( " limit {} ", count );

        return *this;
    }
    DBQuery& limit( unsigned int offset, unsigned int count )
    {
        m_sql += fmt::format( " limit {}, {}  ", offset, count );
        return *this;
    }
    DBQuery& group_by( const std::string& col )
    {
        m_sql += fmt::format( " group by {} ", col );
        return *this;
    }


    DBQuery& order_by( const std::string& col, const std::string& type = "asc" )
    {
        m_sql += fmt::format( " order by {} {} ", col, type );
        return *this;
    }

    DBQuery& join( const std::string& tb, const std::string& lId, const std::string& op, const std::string& rId )
    {
        return inner_join( tb, lId, op, rId );
    }

    DBQuery& inner_join( const std::string& tb, const std::string& lId, const std::string& op, const std::string& rId )
    {
        m_sql += fmt::format( " inner join {} on {} {} {} ", tb, lId, op, rId );
        return *this;
    }

    DBQuery& left_join( const std::string& tb, const std::string& lId, const std::string& op, const std::string& rId )
    {
        m_sql += fmt::format( " left join {} on {} {} {} ", tb, lId, op, rId );
        return *this;
    }

    DBQuery& right_join( const std::string& tb, const std::string& lId, const std::string& op, const std::string& rId )
    {
        m_sql += fmt::format( " right join {} on {} {} {} ", tb, lId, op, rId );
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
    std::string  m_sql ;
};

}
}
