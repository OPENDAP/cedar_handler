// TabResponseHandler.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include "TabResponseHandler.h"
#include "CedarTab.h"
#include "cgi_util.h"

TabResponseHandler::TabResponseHandler( string name )
    : DODSResponseHandler( name )
{
}

TabResponseHandler::~TabResponseHandler( )
{
}

void
TabResponseHandler::execute( DODSDataHandlerInterface &dhi )
{
    _response = new CedarTab( dhi.transmit_protocol == "HTTP" ) ;
    execute_each( dhi ) ;
}

void
TabResponseHandler::transmit( DODSTransmitter *transmitter,
                              DODSDataHandlerInterface &dhi )
{
    if( _response )
	transmitter->send_text( *((CedarTab *)_response) ) ;
}

DODSResponseHandler *
TabResponseHandler::TabResponseBuilder( string handler_name )
{
    return new TabResponseHandler( handler_name ) ;
}

// $Log: TabResponseHandler.cc,v $
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
