// CedarFlat.cc

#ifdef __GNUG__
#pragma implementation
#endif

#include "CedarFlat.h"

CedarFlat::CedarFlat()
    : DODSInfo( dods_data )
{
    initialize( "" ) ;
}

CedarFlat::CedarFlat( bool is_http )
    : DODSInfo( is_http, dods_data )
{
    initialize( "Cedar.Flat.Buffered" ) ;
}

CedarFlat::~CedarFlat()
{
}

// $Log: CedarFlat.cc,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
