// cedar_version.h

#ifndef E_cedar_version_h
#define E_cedar_version_h 1

#include <string>

using std::string ;

string
cedar_version()
{
    return (string)"DODS cedar/2.0.1: compiled on " + __DATE__ + ":" + __TIME__ ;
}

#endif // E_cedar_version_h

// $Log: cedar_version.h,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
