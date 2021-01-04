
#include <iostream>
#include "dmgdb.hpp"
#include "person.orm.h"

uint64_t NextID()
{
    static uint64_t NextID = time(0);
    return NextID++;
}

int main()
{
    GDb oGDB("127.0.0.1", 3306, "root", "000000");
    oGDB.init("");

    DBQuery oQuery;

    db_CreateTable(oGDB, oQuery);

    CDMPB_tb_Person oPerson(oGDB, oQuery);

    db::tb_Person data;
    data.set_id(NextID());
    data.set_number("13900112233");
    data.set_email("person@163.com");
    data.set_phonetype(::db::PhoneType::WORK);

    oPerson.Insert(data);

    {
        std::vector<db::tb_Person> datas;
        oPerson.Select(data, datas);

        for (int i=0; i < datas.size(); ++i)
        {
            std::cout << datas[i].DebugString() << std::endl;
        }
    }
    db::tb_Person data2;
    data2.set_id(data.id());
    data2.set_number("123456789");

    oPerson.Update(data2);

    db::tb_Person data3;
    data3.set_id(NextID());
    data3.set_number("13655265368");
    data3.set_email("tom@qq.com");
    data3.set_phonetype(::db::PhoneType::WORK);

    oPerson.Insert(data3);
    {
        std::vector<db::tb_Person> datas;
        oPerson.Select(datas);
        for (int i = 0; i < datas.size(); ++i)
        {
            std::cout << datas[i].DebugString() << std::endl;
        }
    }

    oPerson.Del(data);

    {
        std::vector<db::tb_Person> datas;
        oPerson.Select(data, datas);
        for (int i = 0; i < datas.size(); ++i)
        {
            std::cout << datas[i].DebugString() << std::endl;
        }
    }

    fmt::print("Done\n");
    return 0;
}
