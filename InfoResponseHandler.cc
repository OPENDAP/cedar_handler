// InfoResponseHandler.cc

#include "InfoResponseHandler.h"
#include "DODSTextInfo.h"
#include "cgi_util.h"

InfoResponseHandler::InfoResponseHandler( string name )
    : DODSResponseHandler( name )
{
}

InfoResponseHandler::~InfoResponseHandler( )
{
}

void
InfoResponseHandler::execute( DODSDataHandlerInterface &dhi )
{
    _response = new DODSTextInfo( dhi.transmit_protocol == "HTTP" ) ;
    execute_each( dhi ) ;
}

void
InfoResponseHandler::transmit( DODSTransmitter *transmitter,
                               DODSDataHandlerInterface &dhi )
{
    if( _response )
	transmitter->send_text( *((DODSTextInfo *)_response) ) ;
}

DODSResponseHandler *
InfoResponseHandler::InfoResponseBuilder( string handler_name )
{
    return new InfoResponseHandler( handler_name ) ;
}

// $Log: InfoResponseHandler.cc,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
