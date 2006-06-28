// cedar_module.cc

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

#include "BESInitList.h"
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

#include "BESResponseNames.h"
#include "BESResponseHandlerList.h"

#include "BESDASResponseHandler.h"
#include "BESDDSResponseHandler.h"
#include "BESDataResponseHandler.h"
#include "BESDDXResponseHandler.h"

#include "BESShowContainersResponseHandler.h"
#include "BESShowDefsResponseHandler.h"
#include "BESCatalogResponseHandler.h"

#include "BESDefineResponseHandler.h"
#include "BESSetContainerResponseHandler.h"
#include "BESDelContainerResponseHandler.h"
#include "BESDelContainersResponseHandler.h"
#include "BESDelDefResponseHandler.h"
#include "BESDelDefsResponseHandler.h"

#include "BESContainerStorageList.h"
#include "BESContainerStorageVolatile.h"
#include "BESDefinitionStorageList.h"
#include "BESDefinitionStorageVolatile.h"

static bool
CedarInit(int, char**)
{
    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "Initializing OPeNDAP modules:" << endl;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << DAS_RESPONSE << " response handler" << endl;
    BESResponseHandlerList::TheList()->add_handler( DAS_RESPONSE, BESDASResponseHandler::DASResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << DDS_RESPONSE << " response handler" << endl;
    BESResponseHandlerList::TheList()->add_handler( DDS_RESPONSE, BESDDSResponseHandler::DDSResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << DDX_RESPONSE << " response handler" << endl;
    BESResponseHandlerList::TheList()->add_handler( DDX_RESPONSE, BESDDXResponseHandler::DDXResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << DATA_RESPONSE << " response handler" << endl;
    BESResponseHandlerList::TheList()->add_handler( DATA_RESPONSE, BESDataResponseHandler::DataResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << SHOWCONTAINERS_RESPONSE << " response handler" << endl;
    BESResponseHandlerList::TheList()->add_handler( SHOWCONTAINERS_RESPONSE, BESShowContainersResponseHandler::ShowContainersResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << SHOWDEFS_RESPONSE << " response handler" << endl;
    BESResponseHandlerList::TheList()->add_handler( SHOWDEFS_RESPONSE, BESShowDefsResponseHandler::ShowDefsResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << CATALOG_RESPONSE << " response handler" << endl;
    BESResponseHandlerList::TheList()->add_handler( CATALOG_RESPONSE, BESCatalogResponseHandler::CatalogResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << DEFINE_RESPONSE << " response handler" << endl;
    BESResponseHandlerList::TheList()->add_handler( DEFINE_RESPONSE, BESDefineResponseHandler::DefineResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << SETCONTAINER << " response handler" << endl;
    BESResponseHandlerList::TheList()->add_handler( SETCONTAINER, BESSetContainerResponseHandler::SetContainerResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << DELETE_CONTAINER << " response handler" << endl;
    BESResponseHandlerList::TheList()->add_handler( DELETE_CONTAINER, BESDelContainerResponseHandler::DelContainerResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << DELETE_CONTAINERS << " response handler" << endl;
    BESResponseHandlerList::TheList()->add_handler( DELETE_CONTAINERS, BESDelContainersResponseHandler::DelContainersResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << DELETE_DEFINITION << " response handler" << endl;
    BESResponseHandlerList::TheList()->add_handler( DELETE_DEFINITION, BESDelDefResponseHandler::DelDefResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << DELETE_DEFINITIONS << " response handler" << endl;
    BESResponseHandlerList::TheList()->add_handler( DELETE_DEFINITIONS, BESDelDefsResponseHandler::DelDefsResponseBuilder ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << PERSISTENCE_VOLATILE << " container persistence" << endl ;
    BESContainerStorageList::TheList()->add_persistence( new BESContainerStorageVolatile( PERSISTENCE_VOLATILE ) ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << PERSISTENCE_VOLATILE << " definition persistence" << endl ;
    BESDefinitionStorageList::TheList()->add_persistence( new BESDefinitionStorageVolatile( PERSISTENCE_VOLATILE ) ) ;

    /* Initialize Cedar specific handlers and plugins */
    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "Initializing Cedar:" << endl ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "    adding " << CEDAR_NAME << " request handler" << endl ;
    BESRequestHandlerList::TheList()->add_handler( CEDAR_NAME, new CedarRequestHandler( CEDAR_NAME ) ) ;

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
    BESReporterList::TheList()->add_reporter( CEDAR_NAME, new CedarReporter ) ;

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

    return true ;
}

static bool
CedarTerm(void)
{
    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "Removing Cedar Handlers" << endl;
    BESRequestHandler *rh = BESRequestHandlerList::TheList()->remove_handler( CEDAR_NAME ) ;
    if( rh ) delete rh ;
    BESResponseHandlerList::TheList()->remove_handler( FLAT_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( TAB_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( STREAM_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( INFO_RESPONSE ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "Removing Cedar Persistence" << endl;
    BESContainerStorageList::TheList()->del_persistence( "Cedar" ) ;

    if( BESLog::TheLog()->is_verbose() )
	(*BESLog::TheLog()) << "Removing OPeNDAP modules" << endl;

    BESResponseHandlerList::TheList()->remove_handler( DAS_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( DDS_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( DDX_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( DATA_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( SHOWCONTAINERS_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( SHOWDEFS_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( CATALOG_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( DEFINE_RESPONSE ) ;
    BESResponseHandlerList::TheList()->remove_handler( SETCONTAINER ) ;
    BESResponseHandlerList::TheList()->remove_handler( DELETE_RESPONSE ) ;

    BESContainerStorageList::TheList()->del_persistence( PERSISTENCE_VOLATILE ) ;
    BESDefinitionStorageList::TheList()->del_persistence( PERSISTENCE_VOLATILE ) ;

    return true ;
}

FUNINITQUIT( CedarInit, CedarTerm, 3 ) ;

