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
    virtual bool		del_container( const string &s_name ) ;
    virtual void		show_containers( DODSInfo &info ) ;
};

#endif // I_ContainerStorageCedar_h_

