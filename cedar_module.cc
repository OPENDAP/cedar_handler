// cedar_module.cc

#include <iostream>

using std::endl ;

#include "DODSInitList.h"
#include "TheRequestHandlerList.h"
#include "CedarRequestHandler.h"
#include "TheResponseHandlerList.h"
#include "FlatResponseHandler.h"
#include "TabResponseHandler.h"
#include "StreamResponseHandler.h"
#include "InfoResponseHandler.h"
#include "TheDODSLog.h"
#include "CedarResponseNames.h"
#include "TheReporterList.h"
#include "CedarReporter.h"

static bool
CedarInit(int, char**)
{
    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "Initializing Cedar:" << endl ;

    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "    adding " << CEDAR_NAME << " request handler" << endl ;
    TheRequestHandlerList->add_handler( CEDAR_NAME, new CedarRequestHandler( CEDAR_NAME ) ) ;

    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "    adding " << FLAT_RESPONSE << " response handler" << endl ;
    TheResponseHandlerList->add_handler( FLAT_RESPONSE, FlatResponseHandler::FlatResponseBuilder ) ;

    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "    adding " << TAB_RESPONSE << " response handler" << endl ;
    TheResponseHandlerList->add_handler( TAB_RESPONSE, TabResponseHandler::TabResponseBuilder ) ;

    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "    adding " << STREAM_RESPONSE << " response handler" << endl ;
    TheResponseHandlerList->add_handler( STREAM_RESPONSE, StreamResponseHandler::StreamResponseBuilder ) ;

    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "    adding " << INFO_RESPONSE << " response handler" << endl ;
    TheResponseHandlerList->add_handler( INFO_RESPONSE, InfoResponseHandler::InfoResponseBuilder ) ;

    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "    adding Cedar reporter" << endl ;
    if( TheReporterList ) TheReporterList->add_reporter( CEDAR_NAME, new CedarReporter ) ;

    return true ;
}

static bool
CedarTerm(void)
{
    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "Removing Cedar Handlers" << endl;
    DODSRequestHandler *rh = TheRequestHandlerList->remove_handler( CEDAR_NAME ) ;
    if( rh ) delete rh ;
    TheResponseHandlerList->remove_handler( FLAT_RESPONSE ) ;
    TheResponseHandlerList->remove_handler( TAB_RESPONSE ) ;
    TheResponseHandlerList->remove_handler( STREAM_RESPONSE ) ;
    TheResponseHandlerList->remove_handler( INFO_RESPONSE ) ;
    return true ;
}

FUNINITQUIT( CedarInit, CedarTerm, 3 ) ;

// $Log: cedar_module.cc,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
