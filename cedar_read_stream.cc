// cedar_read_stream.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <stdio.h>

using std::ifstream ;
using std::ios ;
using std::cerr ;
using std::endl ;
using std::string ;

bool cedar_read_stream(const string &filename, const string &query, string &error)
{
    int bytes=0;
    ifstream os;
    os.open (filename.c_str(),ios::binary|ios::in);
    if (!os)
    {
	error="can not open file " +filename;
	return false;
    }

    int nbytes;
    char block[4096];
    os.read(block, sizeof block);
    while (os)
    {
	nbytes=os.gcount();
	bytes+=nbytes;
	write(fileno(stdout),(void*)block, nbytes);
	os.read(block, sizeof block);
    }
    os.close();

    //cerr<<"BYTES TOTAL = "<<bytes<<endl;

    return true;
}

// $Log: cedar_read_stream.cc,v $
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
