// InfoResponseHandler.h

#ifndef I_InfoResponseHandler_h
#define I_InfoResponseHandler_h 1

#include "DODSResponseHandler.h"

class InfoResponseHandler : public DODSResponseHandler {
public:
				InfoResponseHandler( string name ) ;
    virtual			~InfoResponseHandler( void ) ;

    virtual void		execute( DODSDataHandlerInterface &r ) ;
    virtual void		transmit( DODSTransmitter *transmitter,
                                          DODSDataHandlerInterface &r ) ;

    static DODSResponseHandler *InfoResponseBuilder( string handler_name ) ;
};

#endif // I_InfoResponseHandler_h

// $Log: InfoResponseHandler.h,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
