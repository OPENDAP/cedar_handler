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
#include "DODSInfo.h"
#include "OPeNDAPDir.h"
#include "OPeNDAPFile.h"
#include "CedarResponseNames.h"

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

void
DODSContainerPersistenceCedar::add_container( string s_name,
                                            string r_ame,
					    string type )
{
    throw DODSContainerPersistenceException( "Unable to add a container to Cedar Persistence" ) ;
}

bool
DODSContainerPersistenceCedar::rem_container( const string &s_name )
{
    throw DODSContainerPersistenceException( "Unable to remove a container from Cedar Persistence" ) ;
    return false ;
}

void
DODSContainerPersistenceCedar::show_containers( DODSInfo &info )
{
    info.add_data( get_name() ) ;
    info.add_data( "\n" ) ;

    // need to get every file name in the directory and display
    try
    {
	OPeNDAPDir d( _cedar_base, ".*\\.cbf$" ) ;
	OPeNDAPDir::fileIterator i ;
	for( i = d.beginOfFileList(); i != d.endOfFileList(); i++ )
	{
	    string sym = (*i).getBaseName() ;
	    string real = (*i).getFullPath() ;
	    string line = sym + "," + real + "," + CEDAR_NAME + "\n" ;
	    info.add_data( line ) ;
	}
    }
    catch( const string &err_str )
    {
	info.add_data( err_str ) ;
    }
    catch( ... )
    {
	info.add_data( "Failed to retrieve containers for cedar" ) ;
    }
}

// $Log: DODSContainerPersistenceCedar.cc,v $
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
