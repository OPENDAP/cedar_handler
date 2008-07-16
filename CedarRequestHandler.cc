// CedarRequestHandler.cc

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

#include "CedarRequestHandler.h"
#include "BESResponseHandler.h"
#include "BESInternalError.h"
#include "BESInternalFatalError.h"
#include "BESDapError.h"
#include "BESResponseNames.h"
#include "CedarResponseNames.h"
#include "BESDataNames.h"
#include "cedar_read_attributes.h"
#include "BESDASResponse.h"
#include "cedar_read_descriptors.h"
#include "BESDDSResponse.h"
#include "BESDataDDSResponse.h"
#include "Ancillary.h"
#include "cedar_read_tab.h"
#include "CedarTab.h"
#include "cedar_read_flat.h"
#include "CedarFlat.h"
#include "cedar_read_stream.h"
#include "BESVersionInfo.h"
#include "cedar_read_info.h"
#include "CedarVersion.h"
#include "TheBESKeys.h"
#include "BESDebug.h"
#include "config_cedar.h"

CedarRequestHandler::CedarRequestHandler( string name )
    : BESRequestHandler( name )
{
    add_handler( DAS_RESPONSE, CedarRequestHandler::cedar_build_das ) ;
    add_handler( DDS_RESPONSE, CedarRequestHandler::cedar_build_dds ) ;
    add_handler( DATA_RESPONSE, CedarRequestHandler::cedar_build_data ) ;
    add_handler( FLAT_RESPONSE, CedarRequestHandler::cedar_build_flat ) ;
    add_handler( STREAM_RESPONSE, CedarRequestHandler::cedar_build_stream ) ;
    add_handler( TAB_RESPONSE, CedarRequestHandler::cedar_build_tab ) ;
    add_handler( INFO_RESPONSE, CedarRequestHandler::cedar_build_info ) ;
    add_handler( VERS_RESPONSE, CedarRequestHandler::cedar_build_vers ) ;
    add_handler( HELP_RESPONSE, CedarRequestHandler::cedar_build_help ) ;
}

CedarRequestHandler::~CedarRequestHandler()
{
}

/** @brief dumps information about this object
 *
 * Displays the pointer value of this instance and calls the parent dump
 * method
 *
 * @param strm C++ i/o stream to dump the information to
 */
void
CedarRequestHandler::dump( ostream &strm ) const
{
    strm << BESIndent::LMarg << "CedarRequestHandler::dump - ("
			     << (void *)this << ")" << endl ;
    BESIndent::Indent() ;
    BESRequestHandler::dump( strm ) ;
    BESIndent::UnIndent() ;
}

bool
CedarRequestHandler::cedar_build_das( BESDataHandlerInterface &dhi )
{
    BESDEBUG( "cedar", "building cedar das response:" << endl )

    bool ret = true ;

    BESResponseObject *response =
        dhi.response_handler->get_response_object() ;
    BESDASResponse *bdas = dynamic_cast < BESDASResponse * >(response) ;
    DAS *das = 0 ;
    if (bdas)
	das = bdas->get_das() ;
    else
	throw BESInternalError( "cast error", __FILE__, __LINE__ ) ;

    try
    {
	string cedar_error ;
	string container = dhi.container->access() ;
	if( !cedar_read_attributes( *das, container, cedar_error ) )
	{
	    throw BESInternalError( cedar_error, __FILE__, __LINE__ ) ;
	}
	Ancillary::read_ancillary_das( *das, container ) ;
    }
    catch( BESError &e ) {
	throw e ;
    }
    catch(InternalErr & e) {
        BESDapError ex( e.get_error_message(), true, e.get_error_code(),
	                __FILE__, __LINE__ ) ;
        throw ex;
    }
    catch(Error & e) {
        BESDapError ex( e.get_error_message(), false, e.get_error_code(),
	                __FILE__, __LINE__ ) ;
        throw ex;
    }
    catch(...) {
        string s = "unknown exception caught building DAS";
        BESInternalFatalError ex(s, __FILE__, __LINE__);
        throw ex;
    }

    BESDEBUG( "cedar", "returning from building cedar das response:" << endl << *das << endl )

    return ret ;
}

bool
CedarRequestHandler::cedar_build_dds( BESDataHandlerInterface &dhi )
{
    bool ret = true ;

    BESResponseObject *response =
        dhi.response_handler->get_response_object();
    BESDDSResponse *bdds = dynamic_cast < BESDDSResponse * >(response);
    DDS *dds = 0 ;
    if (bdds)
	dds = bdds->get_dds();
    else
	throw BESInternalError( "cast error", __FILE__, __LINE__ ) ;

    try
    {
	string cedar_error ;
	string accessed = dhi.container->access() ;
	if( !cedar_read_descriptors( *dds, accessed,
				     dhi.container->get_symbolic_name(),
				     dhi.container->get_constraint(),
				     cedar_error ) )
	{
	    throw BESInternalError( cedar_error, __FILE__, __LINE__ ) ;
	}
	Ancillary::read_ancillary_dds( *dds, accessed ) ;

	// The dds now includes attribute information. Read the attributes,
	// including any ancillary attributes
	DAS das ;
	if( !cedar_read_attributes( das, accessed, cedar_error ) )
	{
	    throw BESInternalError( cedar_error, __FILE__, __LINE__ ) ;
	}
	Ancillary::read_ancillary_das( das, accessed ) ;

	// transfer the attributes to the dds.
	dds->transfer_attributes(&das);

	dhi.data[POST_CONSTRAINT] = "" ;
    }
    catch( BESError &e ) {
	throw e ;
    }
    catch(InternalErr & e) {
        BESDapError ex( e.get_error_message(), true, e.get_error_code(),
	                __FILE__, __LINE__ ) ;
        throw ex;
    }
    catch(Error & e) {
        BESDapError ex( e.get_error_message(), false, e.get_error_code(),
	                __FILE__, __LINE__ ) ;
        throw ex;
    }
    catch(...) {
        string s = "unknown exception caught building DDS";
        BESInternalFatalError ex(s, __FILE__, __LINE__);
        throw ex;
    }
    return ret ;
}

bool
CedarRequestHandler::cedar_build_data( BESDataHandlerInterface &dhi )
{
    BESResponseObject *response =
        dhi.response_handler->get_response_object();
    BESDataDDSResponse *bdds =
        dynamic_cast < BESDataDDSResponse * >(response);
    DataDDS *dds = 0 ;
    if (bdds)
	dds = bdds->get_dds();
    else
	throw BESInternalError( "cast error", __FILE__, __LINE__ ) ;
  
    try
    {
	string cedar_error ;
	string accessed = dhi.container->access() ;
	if( !cedar_read_descriptors( *dds, accessed,
				     dhi.container->get_symbolic_name(),
				     dhi.container->get_constraint(),
				     cedar_error ) )
	{
	    throw BESInternalError( cedar_error, __FILE__, __LINE__ ) ;
	}
	Ancillary::read_ancillary_dds( *dds, accessed ) ;

	// The dds now includes attribute information. Read the attributes,
	// including any ancillary attributes
	DAS das ;
	if( !cedar_read_attributes( das, accessed, cedar_error ) )
	{
	    throw BESInternalError( cedar_error, __FILE__, __LINE__ ) ;
	}
	Ancillary::read_ancillary_das( das, accessed ) ;

	// transfer the attributes to the dds.
	dds->transfer_attributes(&das);

	dhi.data[POST_CONSTRAINT] = "" ;
    }
    catch( BESError &e ) {
	throw e ;
    }
    catch(InternalErr & e) {
        BESDapError ex( e.get_error_message(), true, e.get_error_code(),
	                __FILE__, __LINE__ ) ;
        throw ex;
    }
    catch(Error & e) {
        BESDapError ex( e.get_error_message(), false, e.get_error_code(),
	                __FILE__, __LINE__ ) ;
        throw ex;
    }
    catch(...) {
        string s = "unknown exception caught building DataDDS";
        BESInternalFatalError ex(s, __FILE__, __LINE__);
        throw ex;
    }
    return true ;
}

bool
CedarRequestHandler::cedar_build_flat( BESDataHandlerInterface &dhi )
{
    bool ret = true ;

    BESResponseObject *response =
        dhi.response_handler->get_response_object() ;
    CedarFlat *flat = dynamic_cast < CedarFlat * >(response) ;
    if( !flat )
	throw BESInternalError( "cast error", __FILE__, __LINE__ ) ;

    string cedar_error ;
    if( !cedar_read_flat( *flat, dhi.container->access(),
			  dhi.container->get_constraint(), cedar_error ) )
    {
	throw BESInternalError( cedar_error, __FILE__, __LINE__ ) ;
    }
    return ret ;
}

bool
CedarRequestHandler::cedar_build_stream( BESDataHandlerInterface &dhi )
{
    bool ret = true ;
    string cedar_error ;
    if( !cedar_read_stream( dhi.container->access(),
			    dhi.container->get_constraint(), cedar_error ) )
    {
	throw BESInternalError( cedar_error, __FILE__, __LINE__ ) ;
    }
    return ret ;
}

bool
CedarRequestHandler::cedar_build_tab( BESDataHandlerInterface &dhi )
{
    bool ret = true ;

    BESResponseObject *response =
        dhi.response_handler->get_response_object() ;
    CedarTab *dtab = dynamic_cast < CedarTab * >(response) ;
    if( !dtab )
	throw BESInternalError( "cast error", __FILE__, __LINE__ ) ;

    string cedar_error ;
    if( !cedar_read_tab( *dtab, dhi.container->access(),
			 dhi.container->get_constraint(), cedar_error ) )
    {
	throw BESInternalError( cedar_error, __FILE__, __LINE__ ) ;
    }
    return ret ;
}

bool
CedarRequestHandler::cedar_build_info( BESDataHandlerInterface &dhi )
{
    bool ret = true ;

    BESInfo *info =
	dynamic_cast<BESInfo *>(dhi.response_handler->get_response_object());
    if( !info )
	throw BESInternalError( "cast error", __FILE__, __LINE__ ) ;

    string cedar_error ;
    if( !cedar_read_info( *info, dhi.container->access(),
			  dhi.container->get_symbolic_name(),
			  dhi.container->get_constraint(),
			  cedar_error ) )
    {
	throw BESInternalError( cedar_error, __FILE__, __LINE__ ) ;
    }
    return ret ;
}

bool
CedarRequestHandler::cedar_build_vers( BESDataHandlerInterface &dhi )
{
    bool ret = true ;

    BESResponseObject *response =
        dhi.response_handler->get_response_object();
    BESVersionInfo *info = dynamic_cast < BESVersionInfo * >(response);
    if( !info )
	throw BESInternalError( "cast error", __FILE__, __LINE__ ) ;
  
    info->addHandlerVersion( PACKAGE_NAME, PACKAGE_VERSION ) ;

    return ret ;
}

bool
CedarRequestHandler::cedar_build_help( BESDataHandlerInterface &dhi )
{
    bool ret = true ;

    BESResponseObject *response =
        dhi.response_handler->get_response_object();
    BESInfo *info = dynamic_cast < BESInfo * >(response);
    if( !info )
	throw BESInternalError( "cast error", __FILE__, __LINE__ ) ;
  
    info->begin_tag( "Handler" ) ;
    info->add_tag( "name", PACKAGE_NAME ) ;
    string handles = (string)DAS_RESPONSE
                     + "," + DDS_RESPONSE
                     + "," + DATA_RESPONSE
                     + "," + FLAT_RESPONSE
                     + "," + TAB_RESPONSE
                     + "," + INFO_RESPONSE
                     + "," + STREAM_RESPONSE
                     + "," + HELP_RESPONSE
                     + "," + VERS_RESPONSE ;
    info->add_tag( "handles", handles ) ;
    info->add_tag( "version", PACKAGE_STRING ) ;
    info->begin_tag( "help" ) ;

    info->add_data_from_file( "Cedar.Help", CEDAR_NAME ) ;

    info->end_tag( "help" ) ;
    info->end_tag( "Handler" ) ;

    return ret ;
}

