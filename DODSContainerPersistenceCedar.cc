// DODSContainerPersistenceCedar.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include <sstream>
#include <fstream>
#include <iostream>

using std::stringstream ;
using std::ifstream ;

#include "DODSContainerPersistenceCedar.h"
#include "DODSContainer.h"
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
DODSContainerPersistenceCedar::look_for( DODSContainer &d )
{
    d.set_valid_flag( true ) ;
    d.set_real_name( _cedar_base + "/" + d.get_symbolic_name() + ".cbf" ) ;
    d.set_container_type( "cedar" ) ;
}

// $Log: DODSContainerPersistenceCedar.cc,v $
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
