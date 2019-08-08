#ifndef __{{DMPROTO_NAME_UP}}_ORM_H_INCLUDE__
#define __{{DMPROTO_NAME_UP}}_ORM_H_INCLUDE__

#include "db_policy.h"

#include "{{DMPROTO_NAME}}.pb.h"

#define DM_MAGIC ,
#define DM_MAGIC_END

using namespace gdp::db;
{{#DMPACKAGE_LIST}}{{#DMMESSAGE_LIST}}
class CDMPB_{{DMMESSAGE_NAME}}
{
public:
    CDMPB_{{DMMESSAGE_NAME}}(GDb& oDB, DBQuery& oQuery)
        : m_oDB(oDB), m_oQuery(oQuery)
    {

    }

    int CreateTable()
    {
		m_oDB.execute("CREATE DATABASE IF NOT EXISTS {{DMPACKAGE_NAME}} DEFAULT CHARSET = utf8;");
        std::string strSQL = fmt::format("CREATE TABLE IF NOT EXISTS {{DMPACKAGE_NAME}}.{{DMMESSAGE_NAME}} ("{{#DMFIELD_LIST}} 
            "{{DMFIELD_NAME}} {{DMFIELD_SQL_TYPE}},"{{/DMFIELD_LIST}}
            "PRIMARY KEY({{DMMESSAGE_FIRST_FIELD_NAME}})"
            ") ENGINE = INNODB DEFAULT CHARSET = utf8; ");

        return m_oDB.execute(strSQL.c_str());
    }

    int DropTable()
    {
        return m_oDB.execute("DROP TABLE IF EXISTS {{DMPACKAGE_NAME}}.{{DMMESSAGE_NAME}};");
    }

    int Insert({{DMMESSAGE_CPP_NAME}}& data)
    {
        m_oQuery.table("{{DMPACKAGE_NAME}}.{{DMMESSAGE_NAME}}").insert({{#DMFIELD_LIST}} 
            "{{DMFIELD_NAME}}" {{DMFIELD_COMMA}}{{/DMFIELD_LIST}}
            ).values({{#DMFIELD_LIST}}
                data.{{DMFIELD_NAME}}() {{DMFIELD_COMMA}}{{/DMFIELD_LIST}}
                );
        std::string strSQL = m_oQuery.sql();
        return m_oDB.execute(m_oQuery);
    }

    int Select(std::vector<{{DMMESSAGE_CPP_NAME}}> & datas)
    {
        m_oQuery.table("{{DMPACKAGE_NAME}}.{{DMMESSAGE_NAME}}").select({{#DMFIELD_LIST}}
            "{{DMFIELD_NAME}}" {{DMFIELD_COMMA}} {{/DMFIELD_LIST}}
        );
        std::string strSQL = m_oQuery.sql();
        m_oDB.get(m_oQuery, [&datas](ResultSetPtr res)
        {
            while (res->next())
            {
                {{DMMESSAGE_CPP_NAME}} tmp; {{#DMFIELD_LIST}}
                tmp.set_{{DMFIELD_NAME}}(({{DMFIELD_CPP_NAME}})res->get_{{DMFIELD_TYPE}}("{{DMFIELD_NAME}}")); {{/DMFIELD_LIST}}
                datas.push_back(tmp);
            }
        });
        return datas.size();
    }

    int Select({{DMMESSAGE_CPP_NAME}}& data, std::vector<{{DMMESSAGE_CPP_NAME}}>& datas)
    {
        m_oQuery.table("{{DMPACKAGE_NAME}}.{{DMMESSAGE_NAME}}").select({{#DMFIELD_LIST}} 
            "{{DMFIELD_NAME}}" {{DMFIELD_COMMA}}{{/DMFIELD_LIST}}
            ).where("{{DMMESSAGE_FIRST_FIELD_NAME}}", data.{{DMMESSAGE_FIRST_FIELD_NAME}}());
        std::string strSQL = m_oQuery.sql();
        m_oDB.get(m_oQuery, [&datas](ResultSetPtr res)
        {
            while (res->next())
            {
                {{DMMESSAGE_CPP_NAME}} tmp;{{#DMFIELD_LIST}}
                tmp.set_{{DMFIELD_NAME}}(({{DMFIELD_CPP_NAME}})res->get_{{DMFIELD_TYPE}}("{{DMFIELD_NAME}}"));{{/DMFIELD_LIST}}
                datas.push_back(tmp);
            }
        });
        return datas.size();
    }

    int Update({{DMMESSAGE_CPP_NAME}}& data)
    {
        m_oQuery.table("{{DMPACKAGE_NAME}}.{{DMMESSAGE_NAME}}").update();
        {{#DMFIELD_LIST}}
        if (data.has_{{DMFIELD_NAME}}())
        {
            m_oQuery.set("{{DMFIELD_NAME}}", data.{{DMFIELD_NAME}}());
        }
        {{/DMFIELD_LIST}}
        if (data.has_{{DMMESSAGE_FIRST_FIELD_NAME}}())
        {
            m_oQuery.where("{{DMMESSAGE_FIRST_FIELD_NAME}}", data.{{DMMESSAGE_FIRST_FIELD_NAME}}());
        }

        std::string strSQL = m_oQuery.sql(); 
        return m_oDB.execute(m_oQuery);
    }

    int Del({{DMMESSAGE_CPP_NAME}}& data)
    {
        m_oQuery.table("{{DMPACKAGE_NAME}}.{{DMMESSAGE_NAME}}").del().where("{{DMMESSAGE_FIRST_FIELD_NAME}}", data.{{DMMESSAGE_FIRST_FIELD_NAME}}());
        std::string strSQL = m_oQuery.sql();
        return m_oDB.execute(m_oQuery);
    }
private:
    GDb& m_oDB;
    DBQuery& m_oQuery;
};
{{/DMMESSAGE_LIST}}
void {{DMPACKAGE_NAME}}_CreateTable(GDb& oDB, DBQuery& oQuery)
{{{#DMMESSAGE_LIST}}
    {
        CDMPB_{{DMMESSAGE_NAME}} oCDMPB_{{DMMESSAGE_NAME}}(oDB, oQuery);
        oCDMPB_{{DMMESSAGE_NAME}}.CreateTable();
    }{{/DMMESSAGE_LIST}}
}

void {{DMPACKAGE_NAME}}_DropTable(GDb& oDB, DBQuery& oQuery)
{{{#DMMESSAGE_LIST}}
    {
        CDMPB_{{DMMESSAGE_NAME}} oCDMPB_{{DMMESSAGE_NAME}}(oDB, oQuery);
        oCDMPB_{{DMMESSAGE_NAME}}.DropTable();
    }{{/DMMESSAGE_LIST}}
}
{{/DMPACKAGE_LIST}}

#undef DM_MAGIC
#undef DM_MAGIC_END
#endif // __{{DMPROTO_NAME_UP}}_ORM_H_INCLUDE__