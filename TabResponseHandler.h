// TabResponseHandler.h

#ifndef I_TABRESPONSEHANDLER_H
#define I_TABRESPONSEHANDLER_H

#include "DODSResponseHandler.h"

class TabResponseHandler : public DODSResponseHandler {
public:
				TabResponseHandler( string handler_name ) ;
    virtual			~TabResponseHandler(void) ;

    virtual void		execute( DODSDataHandlerInterface &r ) ;
    virtual void		transmit( DODSTransmitter *transmitter,
                                          DODSDataHandlerInterface &r ) ;

    static DODSResponseHandler *TabResponseBuilder( string handler_name ) ;
};

#endif // I_TABRESPONSEHANDLER_H

// $Log: TabResponseHandler.h,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
