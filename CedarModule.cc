// CedarModule.cc

// This file is part of bes, A C++ back-end server implementation framework
// for the OPeNDAP Data Access Protocol.

// Copyright (c) 2004,2005 University Corporation for Atmospheric Research
// Author: Patrick West <pwest@ucar.org>
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

#include <iostream>

using std::endl ;

#include "CedarModule.h"
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
#include "ContainerStorageCedar.h"
#include "ContainerStorageList.h"
#include "OPeNDAPCommand.h"

void
CedarModule::initialize()
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

    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "Adding Cedar Persistence" << endl;
    ContainerStorageCedar *cpf = new ContainerStorageCedar( "Cedar" ) ;
    ContainerStorageList::TheList()->add_persistence( cpf ) ;

    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "Initializing Cedar Commands:" << endl ;

    string cmd_name = string( GET_RESPONSE ) + "." + FLAT_RESPONSE ;
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding " << cmd_name << " command" << endl;
    OPeNDAPCommand::add_command( cmd_name, OPeNDAPCommand::TermCommand ) ;

    cmd_name = string( GET_RESPONSE ) + "." + TAB_RESPONSE ;
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding " << cmd_name << " command" << endl;
    OPeNDAPCommand::add_command( cmd_name, OPeNDAPCommand::TermCommand ) ;

    cmd_name = string( GET_RESPONSE ) + "." + STREAM_RESPONSE ;
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding " << cmd_name << " command" << endl;
    OPeNDAPCommand::add_command( cmd_name, OPeNDAPCommand::TermCommand ) ;

    cmd_name = string( GET_RESPONSE ) + "." + INFO_RESPONSE ;
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding " << cmd_name << " command" << endl;
    OPeNDAPCommand::add_command( cmd_name, OPeNDAPCommand::TermCommand ) ;
}

void
CedarModule::terminate()
{
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "Removing Cedar Handlers" << endl;
    DODSRequestHandler *rh = DODSRequestHandlerList::TheList()->remove_handler( CEDAR_NAME ) ;
    if( rh ) delete rh ;
    DODSResponseHandlerList::TheList()->remove_handler( FLAT_RESPONSE ) ;
    DODSResponseHandlerList::TheList()->remove_handler( TAB_RESPONSE ) ;
    DODSResponseHandlerList::TheList()->remove_handler( STREAM_RESPONSE ) ;
    DODSResponseHandlerList::TheList()->remove_handler( INFO_RESPONSE ) ;

    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "Removing Cedar Persistence" << endl;
    ContainerStorageList::TheList()->rem_persistence( "Cedar" ) ;
}

extern "C"
{
    OPeNDAPAbstractModule *maker()
    {
	return new CedarModule ;
    }
}

