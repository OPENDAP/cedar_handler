// FlatResponseHandler.cc

#include "FlatResponseHandler.h"
#include "CedarFlat.h"
#include "cgi_util.h"

FlatResponseHandler::FlatResponseHandler( string name )
    : DODSResponseHandler( name )
{
}

FlatResponseHandler::~FlatResponseHandler( )
{
}

void
FlatResponseHandler::execute( DODSDataHandlerInterface &dhi )
{
    _response = new CedarFlat( dhi.transmit_protocol == "HTTP" ) ;
    execute_each( dhi ) ;
}

void
FlatResponseHandler::transmit( DODSTransmitter *transmitter,
                               DODSDataHandlerInterface &dhi )
{
    if( _response )
	transmitter->send_text( *((CedarFlat *)_response) ) ;
}

DODSResponseHandler *
FlatResponseHandler::FlatResponseBuilder( string handler_name )
{
    return new FlatResponseHandler( handler_name ) ;
}

// $Log: FlatResponseHandler.cc,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
