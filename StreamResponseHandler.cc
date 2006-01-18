// StreamResponseHandler.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include "StreamResponseHandler.h"
#include "DODSRequestHandlerList.h"

StreamResponseHandler::StreamResponseHandler( string name )
    : DODSResponseHandler( name )
{
}

StreamResponseHandler::~StreamResponseHandler( )
{
}

void
StreamResponseHandler::execute( DODSDataHandlerInterface &dhi )
{
    _response = 0 ;
    DODSRequestHandlerList::TheList()->execute_each( dhi ) ;
}

void
StreamResponseHandler::transmit( DODSTransmitter *transmitter,
                                 DODSDataHandlerInterface & )
{
    // The Data is transmitted when it is read, dumped to stdout
}

DODSResponseHandler *
StreamResponseHandler::StreamResponseBuilder( string handler_name )
{
    return new StreamResponseHandler( handler_name ) ;
}

// $Log: StreamResponseHandler.cc,v $
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
