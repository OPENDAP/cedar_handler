// cedar_read_tab_support.cc

#include "CedarDataTypes.h"
#include "CedarArray.cc"

#include "cedar_read_tab_support.h"

template class CedarArray<pcedararray_of_field>;

// $Log: cedar_read_tab_support.cc,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
