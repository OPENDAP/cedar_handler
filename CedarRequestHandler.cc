// CedarRequestHandler.cc

#include <iostream>
#include <fstream>

using std::ifstream ;

#include "CedarRequestHandler.h"
#include "DODSResponseHandler.h"
#include "DODSResponseException.h"
#include "DODSResponseNames.h"
#include "CedarResponseNames.h"
#include "cedar_read_attributes.h"
#include "DAS.h"
#include "cedar_read_descriptors.h"
#include "DDS.h"
#include "cedar_read_tab.h"
#include "CedarTab.h"
#include "cedar_read_flat.h"
#include "cedar_read_stream.h"
#include "DODSInfo.h"
#include "cedar_read_info.h"
#include "cedar_version.h"
#include "CedarVersion.h"
#include "TheDODSKeys.h"

CedarRequestHandler::CedarRequestHandler( string name )
    : DODSRequestHandler( name )
{
    add_handler( DAS_RESPONSE, CedarRequestHandler::cedar_build_das ) ;
    add_handler( DDS_RESPONSE, CedarRequestHandler::cedar_build_dds ) ;
    add_handler( DATA_RESPONSE, CedarRequestHandler::cedar_build_dds ) ;
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

bool
CedarRequestHandler::cedar_build_das( DODSDataHandlerInterface &dhi )
{
    bool ret = true ;
    DAS *das = (DAS *)dhi.response_handler->get_response_object() ;
    string cedar_error ;
    if( !cedar_read_attributes( *das, dhi.container->get_real_name(), cedar_error ) )
    {
	throw DODSResponseException( cedar_error ) ;
    }
    return ret ;
}

bool
CedarRequestHandler::cedar_build_dds( DODSDataHandlerInterface &dhi )
{
    bool ret = true ;
    DDS *dds = (DDS *)dhi.response_handler->get_response_object() ;
    string cedar_error ;
    if( !cedar_read_descriptors( *dds, dhi.container->get_real_name(),
				 dhi.container->get_symbolic_name(),
				 dhi.container->get_constraint(),
				 cedar_error ) )
    {
	throw DODSResponseException( cedar_error ) ;
    }
    dhi.post_constraint = "" ;
    return ret ;
}

bool
CedarRequestHandler::cedar_build_flat( DODSDataHandlerInterface &dhi )
{
    bool ret = true ;
    CedarFlat *flat = (CedarFlat *)dhi.response_handler->get_response_object() ;
    string cedar_error ;
    if( !cedar_read_flat( *flat, dhi.container->get_real_name(),
			  dhi.container->get_constraint(), cedar_error ) )
    {
	throw DODSResponseException( cedar_error ) ;
    }
    return ret ;
}

bool
CedarRequestHandler::cedar_build_stream( DODSDataHandlerInterface &dhi )
{
    bool ret = true ;
    string cedar_error ;
    if( !cedar_read_stream( dhi.container->get_real_name(),
			    dhi.container->get_constraint(), cedar_error ) )
    {
	throw DODSResponseException( cedar_error ) ;
    }
    return ret ;
}

bool
CedarRequestHandler::cedar_build_tab( DODSDataHandlerInterface &dhi )
{
    bool ret = true ;
    CedarTab *dtab = (CedarTab *)dhi.response_handler->get_response_object() ;
    string cedar_error ;
    if( !cedar_read_tab( *dtab, dhi.container->get_real_name(),
			 dhi.container->get_constraint(), cedar_error ) )
    {
	throw DODSResponseException( cedar_error ) ;
    }
    return ret ;
}

bool
CedarRequestHandler::cedar_build_info( DODSDataHandlerInterface &dhi )
{
    bool ret = true ;
    DODSInfo *info = (DODSInfo *)dhi.response_handler->get_response_object() ;
    string cedar_error ;
    if( !cedar_read_info( *info, dhi.container->get_real_name(),
			  dhi.container->get_symbolic_name(),
			  dhi.container->get_constraint(),
			  cedar_error ) )
    {
	throw DODSResponseException( cedar_error ) ;
    }
    return ret ;
}

bool
CedarRequestHandler::cedar_build_vers( DODSDataHandlerInterface &dhi )
{
    bool ret = true ;
    DODSInfo *info = (DODSInfo *)dhi.response_handler->get_response_object() ;
    info->add_data( (string)"    " + cedar_version() + "\n" ) ;
    info->add_data( (string)"        libCedar++: " + CedarVersion::get_version_number() + "\n" ) ;
    return ret ;
}

bool
CedarRequestHandler::cedar_build_help( DODSDataHandlerInterface &dhi )
{
    bool ret = true ;
    DODSInfo *info = (DODSInfo *)dhi.response_handler->get_response_object() ;
    info->add_data( (string)"cedar-dods help: " + cedar_version() + "\n" ) ;
    bool found = false ;
    string key = (string)"Cedar.Help." + dhi.transmit_protocol ;
    string file = TheDODSKeys->get_key( key, found ) ;
    if( found == false )
    {
	info->add_data( "no help information available for cedar-dods\n" ) ;
    }
    else
    {
	ifstream ifs( file.c_str() ) ;
	if( !ifs )
	{
	    info->add_data( "cedar-dods help file not found, help information not available\n" ) ;
	}
	else
	{
	    char line[4096] ;
	    while( !ifs.eof() )
	    {
		ifs.getline( line, 4096 ) ;
		if( !ifs.eof() )
		{
		    info->add_data( line ) ;
		    info->add_data( "\n" ) ;
		}
	    }
	    ifs.close() ;
	}
    }

    return ret ;
}

// $Log: CedarRequestHandler.cc,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
