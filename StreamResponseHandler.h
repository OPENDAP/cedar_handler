// StreamResponseHandler.h

#ifndef I_STREAMRESPONSEHANDLER_H
#define I_STREAMRESPONSEHANDLER_H

#include "DODSResponseHandler.h"

class StreamResponseHandler : public DODSResponseHandler {
public:
				StreamResponseHandler( string handler_name ) ;
    virtual			~StreamResponseHandler(void) ;

    virtual void		execute( DODSDataHandlerInterface &r ) ;
    virtual void		transmit( DODSTransmitter *transmitter,
                                          DODSDataHandlerInterface &r ) ;

    static DODSResponseHandler *StreamResponseBuilder( string handler_name ) ;
};

#endif // I_STREAMRESPONSEHANDLER_H

// $Log: StreamResponseHandler.h,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
