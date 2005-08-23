// CedarRequestHandler.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include "CedarRequestHandler.h"
#include "DODSResponseHandler.h"
#include "DODSResponseException.h"
#include "DODSResponseNames.h"
#include "CedarResponseNames.h"
#include "OPeNDAPDataNames.h"
#include "cedar_read_attributes.h"
#include "DAS.h"
#include "cedar_read_descriptors.h"
#include "DDS.h"
#include "cedar_read_tab.h"
#include "CedarTab.h"
#include "cedar_read_flat.h"
#include "CedarFlat.h"
#include "cedar_read_stream.h"
#include "DODSTextInfo.h"
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

bool
CedarRequestHandler::cedar_build_das( DODSDataHandlerInterface &dhi )
{
    bool ret = true ;
    DAS *das = dynamic_cast<DAS *>(dhi.response_handler->get_response_object());
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
    DDS *dds = dynamic_cast<DDS *>(dhi.response_handler->get_response_object());
    string cedar_error ;
    if( !cedar_read_descriptors( *dds, dhi.container->get_real_name(),
				 dhi.container->get_symbolic_name(),
				 dhi.container->get_constraint(),
				 cedar_error ) )
    {
	throw DODSResponseException( cedar_error ) ;
    }
    dhi.data[POST_CONSTRAINT] = "" ;
    return ret ;
}

bool
CedarRequestHandler::cedar_build_data( DODSDataHandlerInterface &dhi )
{
    DDS *dds = dynamic_cast<DDS *>(dhi.response_handler->get_response_object());
    string cedar_error ;
    if( !cedar_read_descriptors( *dds, dhi.container->get_real_name(),
				 dhi.container->get_symbolic_name(),
				 dhi.container->get_constraint(),
				 cedar_error ) )
    {
	throw DODSResponseException( cedar_error ) ;
    }
    dhi.data[POST_CONSTRAINT] = "" ;
    return true ;
}

bool
CedarRequestHandler::cedar_build_flat( DODSDataHandlerInterface &dhi )
{
    bool ret = true ;
    CedarFlat *flat = dynamic_cast<CedarFlat *>(dhi.response_handler->get_response_object()) ;
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
    CedarTab *dtab = dynamic_cast<CedarTab *>(dhi.response_handler->get_response_object()) ;
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
    DODSTextInfo *info = dynamic_cast<DODSTextInfo *>(dhi.response_handler->get_response_object());
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
    DODSTextInfo *info = dynamic_cast<DODSTextInfo *>(dhi.response_handler->get_response_object());
    info->add_data( (string)"    " + cedar_version() + "\n" ) ;
    info->add_data( (string)"        libCedar++: " + CedarVersion::get_version_number() + "\n" ) ;
    return ret ;
}

bool
CedarRequestHandler::cedar_build_help( DODSDataHandlerInterface &dhi )
{
    bool ret = true ;
    DODSInfo *info = dynamic_cast<DODSInfo *>(dhi.response_handler->get_response_object());

    info->add_data( (string)"cedar-dods help: " + cedar_version() + "\n" ) ;

    string key ;
    if( dhi.transmit_protocol == "HTTP" )
	key = (string)"Cedar.Help." + dhi.transmit_protocol ;
    else
	key = "Cedar.Help.TXT" ;
    info->add_data_from_file( key, CEDAR_NAME ) ;

    return ret ;
}

// $Log: CedarRequestHandler.cc,v $
// Revision 1.5  2005/04/07 19:56:06  pwest
// using add_data_from_file method of DODSInfo
//
// Revision 1.4  2005/02/01 17:58:37  pwest
// integration of ESG into opendap
//
// Revision 1.3  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.2  2004/07/02 21:11:47  pwest
// added function to read data instead of using dds function
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
