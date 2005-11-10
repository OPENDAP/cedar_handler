// cedar_module.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include <iostream>

using std::endl ;

#include "DODSInitList.h"
#include "DODSRequestHandlerList.h"
#include "CedarRequestHandler.h"
#include "DODSResponseHandlerList.h"
#include "FlatResponseHandler.h"
#include "TabResponseHandler.h"
#include "StreamResponseHandler.h"
#include "InfoResponseHandler.h"
#include "DODSLog.h"
#include "DODSResponseNames.h"
#include "CedarResponseNames.h"
#include "DODSReporterList.h"
#include "CedarReporter.h"
#include "DODS.h"
#include "CedarAuthenticate.h"
#include "CedarAuthenticateException.h"

static bool
CedarInit(int, char**)
{
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "Initializing Cedar:" << endl ;

    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding " << CEDAR_NAME << " request handler" << endl ;
    DODSRequestHandlerList::TheList()->add_handler( CEDAR_NAME, new CedarRequestHandler( CEDAR_NAME ) ) ;

    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding " << FLAT_RESPONSE << " response handler" << endl ;
    DODSResponseHandlerList::TheList()->add_handler( FLAT_RESPONSE, FlatResponseHandler::FlatResponseBuilder ) ;

    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding " << TAB_RESPONSE << " response handler" << endl ;
    DODSResponseHandlerList::TheList()->add_handler( TAB_RESPONSE, TabResponseHandler::TabResponseBuilder ) ;

    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding " << STREAM_RESPONSE << " response handler" << endl ;
    DODSResponseHandlerList::TheList()->add_handler( STREAM_RESPONSE, StreamResponseHandler::StreamResponseBuilder ) ;

    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding " << INFO_RESPONSE << " response handler" << endl ;
    DODSResponseHandlerList::TheList()->add_handler( INFO_RESPONSE, InfoResponseHandler::InfoResponseBuilder ) ;

    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding Cedar reporter" << endl ;
    DODSReporterList::TheList()->add_reporter( CEDAR_NAME, new CedarReporter ) ;

    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding Cedar authenticate to init callbacks" << endl ;
    DODS::add_init_callback( CedarAuthenticate::authenticate ) ;

    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding Cedar authenticate exception callback" << endl ;
    DODS::add_ehm_callback( CedarAuthenticateException::handleAuthException ) ;

    return true ;
}

static bool
CedarTerm(void)
{
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "Removing Cedar Handlers" << endl;
    DODSRequestHandler *rh = DODSRequestHandlerList::TheList()->remove_handler( CEDAR_NAME ) ;
    if( rh ) delete rh ;
    DODSResponseHandlerList::TheList()->remove_handler( FLAT_RESPONSE ) ;
    DODSResponseHandlerList::TheList()->remove_handler( TAB_RESPONSE ) ;
    DODSResponseHandlerList::TheList()->remove_handler( STREAM_RESPONSE ) ;
    DODSResponseHandlerList::TheList()->remove_handler( INFO_RESPONSE ) ;
    return true ;
}

FUNINITQUIT( CedarInit, CedarTerm, 3 ) ;

// $Log: cedar_module.cc,v $
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
