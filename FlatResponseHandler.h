// FlatResponseHandler.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef I_FLATRESPONSEHANDLER_H
#define I_FLATRESPONSEHANDLER_H

#include "DODSResponseHandler.h"

class FlatResponseHandler : public DODSResponseHandler {
public:
				FlatResponseHandler( string handler_name ) ;
    virtual			~FlatResponseHandler(void) ;

    virtual void		parse( DODSTokenizer &tokenizer,
                                       DODSDataHandlerInterface &dhi ) ;
    virtual void		execute( DODSDataHandlerInterface &r ) ;
    virtual void		transmit( DODSTransmitter *transmitter,
                                          DODSDataHandlerInterface &r ) ;

    static DODSResponseHandler *FlatResponseBuilder( string handler_name ) ;
};

#endif

// $Log: FlatResponseHandler.h,v $
// Revision 1.3  2005/02/01 17:58:37  pwest
// integration of ESG into opendap
//
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
