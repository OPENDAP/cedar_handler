// cedar_read_tab.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef cedar_read_tab_h_
#define cedar_read_tab_h_ 1

#include <string>

using std::string ;

class CedarTab ;

int cedar_read_tab(CedarTab &dt, string filename, string query, string &error);

#endif // cedar_read_tab_h_

// $Log: cedar_read_tab.h,v $
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
