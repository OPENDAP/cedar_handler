// cedar_version.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef E_cedar_version_h
#define E_cedar_version_h 1

#include <string>

using std::string ;

inline string
cedar_version()
{
    return (string)"DODS cedar/2.0.1: compiled on " + __DATE__ + ":" + __TIME__ ;
}

#endif // E_cedar_version_h

// $Log: cedar_version.h,v $
// Revision 1.3  2005/02/01 17:58:37  pwest
// integration of ESG into opendap
//
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
