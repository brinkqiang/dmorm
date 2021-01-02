
#include <iostream>
#include "dmgdb.hpp"
#include "person.orm.h"
#include "libgo/libgo.h"
#include "dmsnowflake.h"

uint64_t NextID()
{
    static CDMIDGenerator gen(0, 0);
    return gen.GetNextID();
}

int main()
{
    for (int i=0; i < 10; i++)
    {
        go [&]
        {
            GDb oGDB("127.0.0.1", 3306, "dmsoft", "sdo.com");
            oGDB.init("");

            DBQuery oQuery;

            CDMPB_tb_Person oPerson(oGDB, oQuery);

            for (int j=0; j < 10000; j++)
            {
                db::tb_Person data;
                data.set_id(NextID());
                data.set_number("13900112233");
                data.set_email("person@163.com");
                data.set_phonetype(::db::PhoneType::WORK);

                bool b = oPerson.Insert(data);
                if (!b)
                {
                    exit(0);
                }
            }
        };
    }

    while (!g_Scheduler.IsEmpty()) {
        g_Scheduler.Start(10, 100);
    }

    fmt::print("Done\n");

    //{
    //    std::vector<db::tb_Person> datas;
    //    oPerson.Select(data, datas);

    //    for (int i=0; i < datas.size(); ++i)
    //    {
    //        std::cout << datas[i].DebugString() << std::endl;
    //    }
    //}
    //db::tb_Person data2;
    //data2.set_id(data.id());
    //data2.set_number("123456789");

    //oPerson.Update(data2);

    //db::tb_Person data3;
    //data3.set_id(NextID());
    //data3.set_number("13655265368");
    //data3.set_email("tom@qq.com");
    //data3.set_phonetype(::db::PhoneType::WORK);

    //oPerson.Insert(data3);
    //{
    //    std::vector<db::tb_Person> datas;
    //    oPerson.Select(datas);
    //    for (int i = 0; i < datas.size(); ++i)
    //    {
    //        std::cout << datas[i].DebugString() << std::endl;
    //    }
    //}

    //oPerson.Del(data);

    //{
    //    std::vector<db::tb_Person> datas;
    //    oPerson.Select(data, datas);
    //    for (int i = 0; i < datas.size(); ++i)
    //    {
    //        std::cout << datas[i].DebugString() << std::endl;
    //    }
    //}
    return 0;
}
