#include <iostream>

using std::cout ;
using std::endl ;

#include "DODSEncode.h"

int
main( int argc, char **argv )
{
    if( argc != 2 )
    {
	cout << "USAGE: " << argv[0] << " <password>" << endl ;
	return 1 ;
    }
    string code = DODSEncode::encode( (const char *)argv[1], (const char *)"disp_key" ) ;
    cout << "code = " << code << endl ;
    return 0 ;
}

