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

**简体中文** · [English](./README.md)

## Doc

- [deepwiki-dmorm](https://deepwiki.com/brinkqiang/dmorm)

## Intro
dmorm

用法
```
dmormtest -user=root -pass=000000
```

### 1. windows
修改src/person.proto 执行build_person.bat即可 person.orm.h 为自动生成的orm映射文件.  
命令行安装好cmake之后执行build.bat 即可生成vs工程  
注意: thirdparty/mysql下面的库为WIN64 如需WIN32请自行下载  
### 2. linux
修改src/person.proto 执行build_person.sh即可 person.orm.h 为自动生成的orm映射文件.  
直接bash build.sh即可  
### 3. 生成工具dmgen4pborm
dmgen4pborm --cpp_out=. person.proto

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
