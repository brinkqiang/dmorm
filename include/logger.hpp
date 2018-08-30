#pragma once

#include <iostream>
#include <stdio.h>
#include <errno.h>

#ifndef DLEVEL
#define DLEVEL  5
#endif


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



//#define Trace( format, ... )   printf( "%s::%s(%d)" format, __FILE__, __FUNCTION__,  __LINE__, ##__VA_ARGS__ )

#if DLEVEL  > 3
#define dlog( fmt , ...  ) fprintf(stdout, ANSI_COLOR_CYAN    "[DEBUG]%s(%d)," fmt ANSI_COLOR_RESET "\n",  __FUNCTION__,  __LINE__, ##__VA_ARGS__ )
#define ilog( fmt , ...  ) fprintf(stdout, ANSI_COLOR_GREEN   "[INFO]%s(%d),"  fmt ANSI_COLOR_RESET "\n",  __FUNCTION__,  __LINE__, ##__VA_ARGS__ )
#define wlog( fmt , ...  ) fprintf(stdout, ANSI_COLOR_YELLOW  "[WARN]%s(%d),"  fmt ANSI_COLOR_RESET "\n",  __FUNCTION__,  __LINE__, ##__VA_ARGS__ )
#define elog( fmt , ...  ) fprintf(stderr, ANSI_COLOR_RED     "[ERROR]%s(%d)," fmt ANSI_COLOR_RESET "\n",  __FUNCTION__,  __LINE__, ##__VA_ARGS__ )
#elif DLEVEL == 3
#define dlog( fmt , ...  )
#define ilog( fmt , ...  ) fprintf(stdout, ANSI_COLOR_GREEN  "[INFO]%s(%d),"  fmt ANSI_COLOR_RESET "\n",  __FUNCTION__,  __LINE__, ##__VA_ARGS__ )
#define wlog( fmt , ...  ) fprintf(stdout, ANSI_COLOR_YELLOW "[WARN]%s(%d),"  fmt ANSI_COLOR_RESET "\n",  __FUNCTION__,  __LINE__, ##__VA_ARGS__ )
#define elog( fmt , ...  ) fprintf(stderr, ANSI_COLOR_RED    "[ERROR]%s(%d)," fmt ANSI_COLOR_RESET "\n",  __FUNCTION__,  __LINE__, ##__VA_ARGS__ )

#elif DLEVEL == 2
#define dlog( fmt , ...  )
#define ilog( fmt , ...  )
#define wlog( fmt , ...  ) fprintf(stdout, ANSI_COLOR_YELLOW "[WARN]%s(%d),"  fmt ANSI_COLOR_RESET "\n",  __FUNCTION__,  __LINE__, ##__VA_ARGS__ )
#define elog( fmt , ...  ) fprintf(stderr, ANSI_COLOR_RED    "[ERROR]%s(%d)," fmt ANSI_COLOR_RESET "\n",  __FUNCTION__,  __LINE__, ##__VA_ARGS__ )

#elif DLEVEL == 1

#define dlog( fmt , ...  )
#define ilog( fmt , ...  )
#define wlog( fmt , ...  )
#define elog( fmt , ...  ) fprintf(stderr, ANSI_COLOR_RED    "[ERROR]%s(%d)," fmt ANSI_COLOR_RESET "\n",  __FUNCTION__,  __LINE__, ##__VA_ARGS__ )

#elif DLEVEL == 0

#define dlog( fmt , ...  )
#define ilog( fmt , ...  )
#define wlog( fmt , ...  )
#define elog( fmt , ...  )

#endif


