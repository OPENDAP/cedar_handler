// CedarRequestHandler.h

#ifndef I_CEDARREQUESTHANDLER_H
#define I_CEDARREQUESTHANDLER_H

#include "DODSRequestHandler.h"

class CedarRequestHandler : public DODSRequestHandler {
public:
			CedarRequestHandler( string name ) ;
    virtual		~CedarRequestHandler( void ) ;

    static bool		cedar_build_das( DODSDataHandlerInterface &r ) ;
    static bool		cedar_build_dds( DODSDataHandlerInterface &r ) ;
    static bool		cedar_build_flat( DODSDataHandlerInterface &r ) ;
    static bool		cedar_build_stream( DODSDataHandlerInterface &r ) ;
    static bool		cedar_build_tab( DODSDataHandlerInterface &r ) ;
    static bool		cedar_build_info( DODSDataHandlerInterface &r ) ;
    static bool		cedar_build_vers( DODSDataHandlerInterface &r ) ;
    static bool		cedar_build_help( DODSDataHandlerInterface &r ) ;
};

#endif

// $Log: CedarRequestHandler.h,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
