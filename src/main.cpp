
#include <iostream>
#include "gdb.hpp"
#include "person.orm.h"

int main()
{
    GDb oGDB("127.0.0.1", 3306, "root", "000000");
    oGDB.init("");

    DBQuery oQuery;

    db_CreateTable(oGDB, oQuery);

    CDMPB_tb_Person oPerson(oGDB, oQuery);

    db::tb_Person data;
    data.set_id(time(0));
    data.set_number("13900112233");
    data.set_email("person@163.com");
    data.set_phonetype(::db::PhoneType::WORK);

    oPerson.Insert(data);

    {
        std::vector<db::tb_Person> datas;
        oPerson.Select(data, datas);
    }
    db::tb_Person data2;
    data2.set_id(data.id());
    data2.set_number("123456789");

    oPerson.Update(data2);

    {
        std::vector<db::tb_Person> datas;
        oPerson.Select(data, datas);
    }

    oPerson.Del(data);

    {
        std::vector<db::tb_Person> datas;
        oPerson.Select(data, datas);
    }
    return 0;
}
