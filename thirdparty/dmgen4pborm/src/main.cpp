
#include "dmgen.h"


int main( int argc, char* argv[] ) {

    if ( !CDMGen::Instance()->Init() ) {
        goto FAIL;
    }

    if ( !CDMGen::Instance()->DoCommand( argc, argv ) ) {
        goto FAIL;
    }

    return 0;
FAIL:
    return -1;
}
