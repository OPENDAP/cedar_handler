// DODSContainerPersistenceCedar.h

#ifndef I_DODSContainerPersistenceCedar_h_
#define I_DODSContainerPersistenceCedar_h_ 1

#include <string>

using std::string ;

#include "DODSContainerPersistence.h"

class DODSContainerPersistenceCedar : public DODSContainerPersistence
{
private:
    string		_cedar_base ;
public:
    			DODSContainerPersistenceCedar( const string &n );
    virtual		~DODSContainerPersistenceCedar() ;

    virtual void	look_for( const string &s ) ;
};

#endif // I_DODSContainerPersistenceCedar_h_

// $Log: DODSContainerPersistenceCedar.h,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
