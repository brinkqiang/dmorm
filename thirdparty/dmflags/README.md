# dmflags

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

[dmflags GitHub](https://github.com/brinkqiang/dmflags)

## Build status
| [Linux][lin-link] | [MacOSX][osx-link] | [Windows][win-link] |
| :---------------: | :----------------: | :-----------------: |
| ![lin-badge]      | ![osx-badge]       | ![win-badge]        |

[lin-badge]: https://travis-ci.org/brinkqiang/dmflags.svg?branch=master "Travis build status"
[lin-link]:  https://travis-ci.org/brinkqiang/dmflags "Travis build status"
[osx-badge]: https://travis-ci.org/brinkqiang/dmflags.svg?branch=master "Travis build status"
[osx-link]:  https://travis-ci.org/brinkqiang/dmflags "Travis build status"
[win-badge]: https://ci.appveyor.com/api/projects/status/github/brinkqiang/dmflags?branch=master&svg=true "AppVeyor build status"
[win-link]:  https://ci.appveyor.com/project/brinkqiang/dmflags "AppVeyor build status"

## Intro
C++ library that implements commandline flags processing. based on gflags.
```cpp

#include "dmflags.h"
#include <iostream>

DEFINE_uint64(AGE, 23, "age");
DEFINE_string(NAME, "andy", "name");

// dmflagstest --AGE=36 --NAME=tom
int main(int argc, char **argv) 
{   
	DMFLAGS_INIT(argc, argv);
	std::cout << "AGE = " << FLAGS_AGE << std::endl;
	std::cout << "NAME = " << FLAGS_NAME << std::endl;
	return 0;   
}

```
## Contacts
[![Join the chat](https://badges.gitter.im/brinkqiang/dmflags/Lobby.svg)](https://gitter.im/brinkqiang/dmflags)

## Thanks
