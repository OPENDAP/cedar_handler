// CedarTab.cc

// 2004 Copyright University Corporation for Atmospheric Research

#ifdef __GNUG__
#pragma implementation
#endif

#include "CedarTab.h"

CedarTab::CedarTab()
    : DODSInfo( dods_data )
{
    initialize( "" ) ;
}

CedarTab::CedarTab( bool is_http )
    : DODSInfo( is_http, dods_data )
{
    initialize( "" ) ;
}

CedarTab::~CedarTab()
{
}

// $Log: CedarTab.cc,v $
// Revision 1.3  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.2  2004/07/09 16:11:55  pwest
// Using default key for buffering information instead of uniq keys for flat
// and tab
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
