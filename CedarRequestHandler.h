// CedarRequestHandler.h

#ifndef I_CEDARREQUESTHANDLER_H
#define I_CEDARREQUESTHANDLER_H

#include "DODSRequestHandler.h"

class CedarRequestHandler : public DODSRequestHandler {
public:
			CedarRequestHandler( string name ) ;
    virtual		~CedarRequestHandler( void ) ;

    static bool		cedar_build_das( DODSDataHandlerInterface &dhi ) ;
    static bool		cedar_build_dds( DODSDataHandlerInterface &dhi ) ;
    static bool		cedar_build_data( DODSDataHandlerInterface &dhi ) ;
    static bool		cedar_build_flat( DODSDataHandlerInterface &dhi ) ;
    static bool		cedar_build_stream( DODSDataHandlerInterface &dhi ) ;
    static bool		cedar_build_tab( DODSDataHandlerInterface &dhi ) ;
    static bool		cedar_build_info( DODSDataHandlerInterface &dhi ) ;
    static bool		cedar_build_vers( DODSDataHandlerInterface &dhi ) ;
    static bool		cedar_build_help( DODSDataHandlerInterface &dhi ) ;
};

#endif

// $Log: CedarRequestHandler.h,v $
// Revision 1.2  2004/07/02 21:11:47  pwest
// added function to read data instead of using dds function
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
