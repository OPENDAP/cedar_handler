// CedarTab.h

#ifndef CedarTab_h_
#define CedarTab_h_ 1

#include "DODSInfo.h"

class CedarTab : public DODSInfo {
public:
  			CedarTab() ;
  			CedarTab( bool is_http ) ;
    virtual 		~CedarTab() ;
};

#endif // CedarTab_h_

// $Log: CedarTab.h,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
