// CedarAuthenticateException.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef CedarAuthenticateException_h_
#define CedarAuthenticateException_h_ 1

#include "DODSBasicException.h"
#include "DODSDataHandlerInterface.h"

#define CEDAR_AUTHENTICATE_EXCEPTION 13

/** @brief exception thrown if authentication fails
 */
class CedarAuthenticateException: public DODSBasicException
{
public:
      			CedarAuthenticateException() {}
      virtual		~CedarAuthenticateException() {}

      static int	handleAuthException( DODSException &e,
					     DODSDataHandlerInterface &dhi ) ;
};

#endif // CedarAuthenticateException_h_ 

// $Log: CedarAuthenticateException.h,v $
// Revision 1.3  2004/12/15 17:39:03  pwest
// Added doxygen comments
//
// Revision 1.2  2004/09/09 17:17:12  pwest
// Added copywrite information
//
// Revision 1.1  2004/06/30 20:16:24  pwest
// dods dispatch code, can be used for apache modules or simple cgi script
// invocation or opendap daemon. Built during cedar server development.
//
