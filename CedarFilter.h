// CedarFilter.h

#ifndef _cedarfilter_h
#define _cedarfilter_h

#ifndef __POWERPC__
#ifdef __GNUG__
#pragma interface
#endif
#endif

#include "DODSFilter.h"

class CedarTab ;
class CedarFlat ;

class CedarFilter : public DODSFilter {
public:
    /** Types of responses DODSFilter know about. */
    enum Response {
	TAB_Response = DODSFilter::Version_Response + 1,
	FLAT_Response,
	STREAM_Response,
	INFO_Response
    };

public:
    CedarFilter();
    CedarFilter(int argc, char *argv[]) throw(Error);

    virtual ~CedarFilter();

    virtual void set_response(const string &r) throw(Error);
};

// $Log: CedarFilter.h,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//

#endif // _cedarfilter_h

// $Log: CedarFilter.h,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
