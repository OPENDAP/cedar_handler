// CedarFlat.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef CedarFlat_h_
#define CedarFlat_h_ 1

#include "DODSInfo.h"

class CedarFlat : public DODSInfo {
public:
  			CedarFlat() ;
  			CedarFlat( bool is_http ) ;
    virtual 		~CedarFlat() ;
};

#endif // CedarFlat_h_

// $Log: CedarFlat.h,v $
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
