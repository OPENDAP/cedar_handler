// CedarReporter.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef A_CedarReporter_h
#define A_CedarReporter_h 1

#include <fstream>

using std::ofstream ;
using std::ios ;
using std::endl ;

#include "DODSReporter.h"
#include "DODSDataRequestInterface.h"
#include "DODSDataHandlerInterface.h"

class CedarReporter : public DODSReporter
{
private:
    ofstream *		_file_buffer;
public:
			CedarReporter() ;
    virtual		~CedarReporter() ;

    virtual void	report( const DODSDataHandlerInterface &dhi ) ;
} ;

#endif // A_CedarReporter_h

// $Log: CedarReporter.h,v $
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
