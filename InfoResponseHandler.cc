// InfoResponseHandler.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include "InfoResponseHandler.h"
#include "DODSTextInfo.h"
#include "cgi_util.h"
#include "DODSRequestHandlerList.h"

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
    DODSRequestHandlerList::TheList()->execute_each( dhi ) ;
}

void
InfoResponseHandler::transmit( DODSTransmitter *transmitter,
                               DODSDataHandlerInterface &dhi )
{
    if( _response )
	transmitter->send_text( *((DODSTextInfo *)_response), dhi ) ;
}

DODSResponseHandler *
InfoResponseHandler::InfoResponseBuilder( string handler_name )
{
    return new InfoResponseHandler( handler_name ) ;
}

// $Log: InfoResponseHandler.cc,v $
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
