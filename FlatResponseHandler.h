// FlatResponseHandler.h

#ifndef I_FLATRESPONSEHANDLER_H
#define I_FLATRESPONSEHANDLER_H

#include "DODSResponseHandler.h"

class FlatResponseHandler : public DODSResponseHandler {
public:
				FlatResponseHandler( string handler_name ) ;
    virtual			~FlatResponseHandler(void) ;

    virtual void		execute( DODSDataHandlerInterface &r ) ;
    virtual void		transmit( DODSTransmitter *transmitter,
                                          DODSDataHandlerInterface &r ) ;

    static DODSResponseHandler *FlatResponseBuilder( string handler_name ) ;
};

#endif

// $Log: FlatResponseHandler.h,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
