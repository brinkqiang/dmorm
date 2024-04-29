# dmorm

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

## Build status
| [Linux][lin-link] | [Windows][win-link] |
| :---------------: | :-----------------: |
| ![lin-badge]      | ![win-badge]        |

[lin-badge]: https://github.com/brinkqiang/dmorm/workflows/linux/badge.svg "linux build status"
[lin-link]:  https://github.com/brinkqiang/dmorm/actions/workflows/linux.yml "linux build status"
[win-badge]: https://github.com/brinkqiang/dmorm/workflows/win/badge.svg "win build status"
[win-link]:  https://github.com/brinkqiang/dmorm/actions/workflows/win.yml "win build status"

**English** · [简体中文](./README.zh.md) 

## Intro
dmorm is a framework that simplifies working with relational databases by providing Object-Relational Mapping (ORM) functionality. This guide will explain how to install and use dmorm on both Windows and Linux.

Usage:

Bash:
```
dmormtest -user=root -pass=000000
```

Important: Use the provided credentials with caution, especially in a production environment.

- Windows:
Modify the src/person.proto file according to your needs.
Run the build_person.bat script. This will generate the person.orm.h file, which acts as the automatically generated ORM mapping file.
Make sure you have CMake installed before proceeding.
After installing CMake, run the build.bat script again. This will generate a Visual Studio project for you to work with.
Note: The libraries located in the thirdparty/mysql directory are specifically for WIN64 systems. If you need to use dmorm on a WIN32 system, you'll need to download the appropriate MySQL libraries yourself.

- Linux:
Similar to Windows, modify the src/person.proto file to fit your data model.
Run the build_person.sh script. This will also generate the person.orm.h file.
Unlike Windows, you don't need any additional installations. Simply running bash build.sh in your terminal will handle everything.
Generating ORM Mapping Files:

dmorm utilizes a tool called dmgen4pborm to generate ORM mapping files from Protocol Buffers files.

Bash:
```
dmgen4pborm --cpp_out=. person.proto
```

This command generates the mapping file in your current directory (denoted by .) based on the person.proto file.

## Additional Notes:

The thirdparty/mysql directory (Windows only) contains the MySQL libraries required by dmorm.
For WIN32 compatibility, download the appropriate MySQL libraries yourself.
The dmormtest tool allows you to test the dmorm framework by executing queries against your MySQL database.

```cpp

#include <iostream>
#include "dmgdb.hpp"
#include "person.orm.h"
#include "dmsnowflake.h"
#include "dmflags.h"

uint64_t NextID()
{
    static CDMIDGenerator gGen(0, 0);
    return gGen.GetNextID();
}

DEFINE_string(ip, "127.0.0.1", "127.0.0.1");
DEFINE_string(user, "root", "root");
DEFINE_string(pass, "000000", "000000");
DEFINE_int32(port, 3306, "3306");

int main(int argc, char** argv)
{
    DMFLAGS_INIT(argc, argv);

    GDb oGDB(FLAGS_ip, FLAGS_port, FLAGS_user, FLAGS_pass);
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

        for (int i = 0; i < datas.size(); ++i)
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

```

## Thanks
