// DODSContainerPersistenceCedar.cc

#include <sstream>
#include <fstream>
#include <iostream>

using std::stringstream ;
using std::ifstream ;

#include "DODSContainerPersistenceCedar.h"
#include "TheDODSKeys.h"
#include "DODSContainerPersistenceException.h"

DODSContainerPersistenceCedar::DODSContainerPersistenceCedar( const string &n )
    : DODSContainerPersistence( n )
{
    string key = "DODS.Container.Persistence.Cedar.BaseDir" ;
    bool found = false ;
    _cedar_base = TheDODSKeys->get_key( key, found ) ;
    if( _cedar_base == "" )
    {
	string s = key + " not defined in key file" ;
	DODSContainerPersistenceException pe ;
	pe.set_error_description( s ) ;
	throw pe;
    }
}

DODSContainerPersistenceCedar::~DODSContainerPersistenceCedar()
{
}

void
DODSContainerPersistenceCedar::look_for( const string &s )
{
    _exist = true ;
    _symbolic_name = s ;
    _real_name = _cedar_base + "/" + s + ".cbf" ;
    _container_type = "cedar" ;
}

// $Log: DODSContainerPersistenceCedar.cc,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
