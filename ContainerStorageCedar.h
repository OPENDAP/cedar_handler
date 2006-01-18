// ContainerStorageCedar.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef I_ContainerStorageCedar_h_
#define I_ContainerStorageCedar_h_ 1

#include <string>

using std::string ;

#include "ContainerStorage.h"

class ContainerStorageCedar : public ContainerStorage
{
private:
    string			_cedar_base ;
public:
    				ContainerStorageCedar( const string &n);
    virtual			~ContainerStorageCedar() ;

    virtual void		look_for( DODSContainer &d ) ;
    virtual void		add_container( const string &s_name,
                                               const string &r_ame,
					       const string &type ) ;
    virtual bool		rem_container( const string &s_name ) ;
    virtual void		show_containers( DODSInfo &info ) ;
};

#endif // I_ContainerStorageCedar_h_

// $Log: ContainerStorageCedar.h,v $
// Revision 1.5  2005/03/17 20:46:58  pwest
// impelementing rem_container and show_containers
//
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
