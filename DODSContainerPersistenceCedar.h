// DODSContainerPersistenceCedar.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef I_DODSContainerPersistenceCedar_h_
#define I_DODSContainerPersistenceCedar_h_ 1

#include <string>

using std::string ;

#include "DODSContainerPersistence.h"

class DODSContainerPersistenceCedar : public DODSContainerPersistence
{
private:
    string			_cedar_base ;
public:
    				DODSContainerPersistenceCedar( const string &n);
    virtual			~DODSContainerPersistenceCedar() ;

    virtual void		look_for( DODSContainer &d ) ;
    virtual void		add_container( string s_name, string r_ame,
					       string type ) ;
    virtual DODSContainer *	rem_container( string s_name ) ;
};

#endif // I_DODSContainerPersistenceCedar_h_

// $Log: DODSContainerPersistenceCedar.h,v $
// Revision 1.4  2005/02/09 20:30:18  pwest
// catch up to dispatch
//
// Revision 1.3  2005/02/01 17:58:37  pwest
// integration of ESG into opendap
//
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
