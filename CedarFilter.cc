// CedarFilter.cc

#ifdef __GNUG__
#pragma implementation
#endif

#include "CedarFilter.h"
#include "CedarResponseNames.h"
#include "CedarTab.h"
#include "CedarFlat.h"
#include "cgi_util.h"

CedarFilter::CedarFilter()
    : DODSFilter()
{
}

CedarFilter::CedarFilter(int argc, char *argv[]) throw(Error)
    : DODSFilter( )
{
    initialize( argc, argv ) ;
}

CedarFilter::~CedarFilter()
{
}

/** Set the response to be returned to TAB_Response if "TAB" or "tab"
    or to FLAT_Response if "FLAT" or "flat"
    or call parent set_response to check for other options.
    @param o The name of the object. 
    @exceptoion InternalErr Thrown if the response is not one of the valid
    names. */
void CedarFilter::set_response(const string &r) throw(Error)
{
    if (r == "TAB" || r == "tab")
    {
	d_response = (DODSFilter::Response)CedarFilter::TAB_Response;
	d_action = TAB_RESPONSE ;
    }
    else if (r == "FLAT" || r == "flat")
    {
	d_response = (DODSFilter::Response)CedarFilter::FLAT_Response;
	d_action = FLAT_RESPONSE ;
    }
    else if (r == "STREAM" || r == "stream")
    {
	d_response = (DODSFilter::Response)CedarFilter::STREAM_Response;
	d_action = STREAM_RESPONSE ;
    }
    else if (r == "INFO" || r == "info")
    {
	d_response = (DODSFilter::Response)CedarFilter::INFO_Response;
	d_action = INFO_RESPONSE ;
    }
    else
	DODSFilter::set_response( r ) ;
}

// $Log: CedarFilter.cc,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
