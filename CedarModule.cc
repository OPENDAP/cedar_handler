// CedarModule.cc

// This file is part of the OPeNDAP Cedar data handler, providing data
// access views for CedarWEB data

// Copyright (c) 2004,2005 University Corporation for Atmospheric Research
// Author: Patrick West <pwest@ucar.edu> and Jose Garcia <jgarcia@ucar.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// You can contact University Corporation for Atmospheric Research at
// 3080 Center Green Drive, Boulder, CO 80301
 
// (c) COPYRIGHT University Corporation for Atmostpheric Research 2004-2005
// Please read the full copyright statement in the file COPYRIGHT_UCAR.
//
// Authors:
//      pwest       Patrick West <pwest@ucar.edu>
//      jgarcia     Jose Garcia <jgarcia@ucar.edu>

#include <iostream>

using std::endl ;

#include "CedarModule.h"
#include "BESRequestHandlerList.h"
#include "CedarRequestHandler.h"
#include "BESResponseHandlerList.h"
#include "FlatResponseHandler.h"
#include "TabResponseHandler.h"
#include "StreamResponseHandler.h"
#include "InfoResponseHandler.h"
#include "BESLog.h"
#include "BESResponseNames.h"
#include "CedarResponseNames.h"
#include "BESReporterList.h"
#include "CedarReporter.h"
#include "BESInterface.h"
#include "CedarAuthenticate.h"
#include "BESExceptionManager.h"
#include "CedarAuthenticateException.h"
#include "ContainerStorageCedar.h"
#include "BESContainerStorageList.h"
#include "BESCommand.h"

void
CedarModule::initialize( const string &modname )
{
    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "Initializing Cedar:" << endl ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << modname << " request handler" << endl ;
    BESRequestHandlerList::TheList()->add_handler( modname, new CedarRequestHandler( modname ) ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << FLAT_RESPONSE << " response handler" << endl ;
    BESResponseHandlerList::TheList()->add_handler( FLAT_RESPONSE, FlatResponseHandler::FlatResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << TAB_RESPONSE << " response handler" << endl ;
    BESResponseHandlerList::TheList()->add_handler( TAB_RESPONSE, TabResponseHandler::TabResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << STREAM_RESPONSE << " response handler" << endl ;
    BESResponseHandlerList::TheList()->add_handler( STREAM_RESPONSE, StreamResponseHandler::StreamResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << INFO_RESPONSE << " response handler" << endl ;
    BESResponseHandlerList::TheList()->add_handler( INFO_RESPONSE, InfoResponseHandler::InfoResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding Cedar reporter" << endl ;
    BESReporterList::TheList()->add_reporter( modname, new CedarReporter ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding Cedar authenticate to init callbacks" << endl ;
    BESInterface::add_init_callback( CedarAuthenticate::authenticate ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding Cedar authenticate exception callback" << endl ;
    BESExceptionManager::TheEHM()->add_ehm_callback( CedarAuthenticateException::handleAuthException ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "Adding Cedar Persistence" << endl;
    ContainerStorageCedar *cpf = new ContainerStorageCedar( "Cedar" ) ;
    BESContainerStorageList::TheList()->add_persistence( cpf ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "Initializing Cedar Commands:" << endl ;

    string cmd_name = string( GET_RESPONSE ) + "." + FLAT_RESPONSE ;
    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << cmd_name << " command" << endl;
    BESCommand::add_command( cmd_name, BESCommand::TermCommand ) ;

    cmd_name = string( GET_RESPONSE ) + "." + TAB_RESPONSE ;
    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << cmd_name << " command" << endl;
    BESCommand::add_command( cmd_name, BESCommand::TermCommand ) ;

    cmd_name = string( GET_RESPONSE ) + "." + STREAM_RESPONSE ;
    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << cmd_name << " command" << endl;
    BESCommand::add_command( cmd_name, BESCommand::TermCommand ) ;

    cmd_name = string( GET_RESPONSE ) + "." + INFO_RESPONSE ;
    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << cmd_name << " command" << endl;
    BESCommand::add_command( cmd_name, BESCommand::TermCommand ) ;
}

void
CedarModule::terminate( const string &modname )
{
    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "Removing Cedar Handlers" << endl;
    BESRequestHandler *rh = BESRequestHandlerList::TheList()->remove_handler( modname ) ;
    if( rh ) delete rh ;
    BESResponseHandlerList::TheList()->remove_handler( FLAT_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( TAB_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( STREAM_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( INFO_RESPONSE ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "Removing Cedar Persistence" << endl;
    BESContainerStorageList::TheList()->del_persistence( "Cedar" ) ;
}

extern "C"
{
    BESAbstractModule *maker()
    {
	return new CedarModule ;
    }
}

