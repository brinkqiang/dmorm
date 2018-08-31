#ifndef __PERSON_ORM_H_INCLUDE__
#define __PERSON_ORM_H_INCLUDE__

#include "gdb.hpp"
#include "dbquery.hpp"
#include "dmformat.h"

#include "person.pb.h"

#define DM_MAGIC ,
#define DM_MAGIC_END

using namespace gdp::db;

class CDMPB_tb_Person
{
public:
    CDMPB_tb_Person(GDb& oDB, DBQuery& oQuery)
        : m_oDB(oDB), m_oQuery(oQuery)
    {

    }

    int CreateTable()
    {
		m_oDB.execute("CREATE DATABASE IF NOT EXISTS db DEFAULT CHARSET = utf8;");
        std::string strSQL = fmt::format("CREATE TABLE IF NOT EXISTS db.tb_Person (" 
            "id BIGINT," 
            "number MEDIUMTEXT," 
            "email MEDIUMTEXT," 
            "phonetype BIGINT,"
            "PRIMARY KEY(id)"
            ") ENGINE = INNODB DEFAULT CHARSET = utf8; ");

        return m_oDB.execute(strSQL.c_str());
    }

    int DropTable()
    {
        return m_oDB.execute("DROP TABLE IF EXISTS db.tb_Person;");
    }

    int Insert(::db::tb_Person& data)
    {
        m_oQuery.table("db.tb_Person").insert( 
            "id" DM_MAGIC 
            "number" DM_MAGIC 
            "email" DM_MAGIC 
            "phonetype" DM_MAGIC_END
            ).values(
                data.id() DM_MAGIC
                data.number() DM_MAGIC
                data.email() DM_MAGIC
                data.phonetype() DM_MAGIC_END
                );
        std::string strSQL = m_oQuery.sql();
        return m_oDB.execute(m_oQuery);
    }

    int Select(::db::tb_Person& data, std::vector<::db::tb_Person>& datas)
    {
        m_oQuery.table("db.tb_Person").select( 
            "id" DM_MAGIC 
            "number" DM_MAGIC 
            "email" DM_MAGIC 
            "phonetype" DM_MAGIC_END
            ).where("id", data.id());
        std::string strSQL = m_oQuery.sql();
        m_oDB.get(m_oQuery, [&datas](ResultSetPtr res)
        {
            while (res->next())
            {
                ::db::tb_Person tmp;
                tmp.set_id((::db::MessageId)res->get_int("id"));
                tmp.set_number((::std::string)res->get_string("number"));
                tmp.set_email((::std::string)res->get_string("email"));
                tmp.set_phonetype((::db::PhoneType)res->get_int("phonetype"));
                datas.push_back(tmp);
            }
        });
        return datas.size();
    }

    int Update(::db::tb_Person& data)
    {
        m_oQuery.table("db.tb_Person").update()
        .set("id", data.id())
        .set("number", data.number())
        .set("email", data.email())
        .set("phonetype", data.phonetype())
        .where("id", data.id());
        std::string strSQL = m_oQuery.sql(); 
        return m_oDB.execute(m_oQuery);
    }

    int Del(::db::tb_Person& data)
    {
        m_oQuery.table("db.tb_Person").del().where("id", data.id());
        std::string strSQL = m_oQuery.sql();
        return m_oDB.execute(m_oQuery);
    }
private:
    GDb& m_oDB;
    DBQuery& m_oQuery;
};

class CDMPB_tb_Person2
{
public:
    CDMPB_tb_Person2(GDb& oDB, DBQuery& oQuery)
        : m_oDB(oDB), m_oQuery(oQuery)
    {

    }

    int CreateTable()
    {
		m_oDB.execute("CREATE DATABASE IF NOT EXISTS db DEFAULT CHARSET = utf8;");
        std::string strSQL = fmt::format("CREATE TABLE IF NOT EXISTS db.tb_Person2 (" 
            "id BIGINT," 
            "name MEDIUMTEXT,"
            "PRIMARY KEY(id)"
            ") ENGINE = INNODB DEFAULT CHARSET = utf8; ");

        return m_oDB.execute(strSQL.c_str());
    }

    int DropTable()
    {
        return m_oDB.execute("DROP TABLE IF EXISTS db.tb_Person2;");
    }

    int Insert(::db::tb_Person2& data)
    {
        m_oQuery.table("db.tb_Person2").insert( 
            "id" DM_MAGIC 
            "name" DM_MAGIC_END
            ).values(
                data.id() DM_MAGIC
                data.name() DM_MAGIC_END
                );
        std::string strSQL = m_oQuery.sql();
        return m_oDB.execute(m_oQuery);
    }

    int Select(::db::tb_Person2& data, std::vector<::db::tb_Person2>& datas)
    {
        m_oQuery.table("db.tb_Person2").select( 
            "id" DM_MAGIC 
            "name" DM_MAGIC_END
            ).where("id", data.id());
        std::string strSQL = m_oQuery.sql();
        m_oDB.get(m_oQuery, [&datas](ResultSetPtr res)
        {
            while (res->next())
            {
                ::db::tb_Person2 tmp;
                tmp.set_id((::db::MessageId)res->get_int("id"));
                tmp.set_name((::std::string)res->get_string("name"));
                datas.push_back(tmp);
            }
        });
        return datas.size();
    }

    int Update(::db::tb_Person2& data)
    {
        m_oQuery.table("db.tb_Person2").update()
        .set("id", data.id())
        .set("name", data.name())
        .where("id", data.id());
        std::string strSQL = m_oQuery.sql(); 
        return m_oDB.execute(m_oQuery);
    }

    int Del(::db::tb_Person2& data)
    {
        m_oQuery.table("db.tb_Person2").del().where("id", data.id());
        std::string strSQL = m_oQuery.sql();
        return m_oDB.execute(m_oQuery);
    }
private:
    GDb& m_oDB;
    DBQuery& m_oQuery;
};

void db_CreateTable(GDb& oDB, DBQuery& oQuery)
{
    {
        CDMPB_tb_Person oCDMPB_tb_Person(oDB, oQuery);
        oCDMPB_tb_Person.CreateTable();
    }
    {
        CDMPB_tb_Person2 oCDMPB_tb_Person2(oDB, oQuery);
        oCDMPB_tb_Person2.CreateTable();
    }
}

void db_DropTable(GDb& oDB, DBQuery& oQuery)
{
    {
        CDMPB_tb_Person oCDMPB_tb_Person(oDB, oQuery);
        oCDMPB_tb_Person.DropTable();
    }
    {
        CDMPB_tb_Person2 oCDMPB_tb_Person2(oDB, oQuery);
        oCDMPB_tb_Person2.DropTable();
    }
}


#undef DM_MAGIC
#undef DM_MAGIC_END
#endif // __PERSON_ORM_H_INCLUDE__