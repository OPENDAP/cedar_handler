// CedarResponseNames.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef E_CedarResponseNames_H
#define E_CedarResponseNames_H 1

#define CEDAR_NAME "cedar"
#define FLAT_RESPONSE "flat"
#define INFO_RESPONSE "info"
#define STREAM_RESPONSE "stream"
#define TAB_RESPONSE "tab"

#endif // E_CedarResponseNames_H

// $Log: CedarResponseNames.h,v $
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
