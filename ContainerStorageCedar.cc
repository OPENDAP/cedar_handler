// ContainerStorageCedar.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include <sstream>
#include <fstream>
#include <iostream>

using std::stringstream ;
using std::ifstream ;

#include "ContainerStorageCedar.h"
#include "DODSContainer.h"
#include "TheDODSKeys.h"
#include "ContainerStorageException.h"
#include "DODSInfo.h"
#include "OPeNDAPDir.h"
#include "OPeNDAPFile.h"
#include "CedarResponseNames.h"

ContainerStorageCedar::ContainerStorageCedar( const string &n )
    : ContainerStorage( n )
{
    string key = "Cedar.BaseDir" ;
    bool found = false ;
    _cedar_base = TheDODSKeys::TheKeys()->get_key( key, found ) ;
    if( _cedar_base == "" )
    {
	string s = key + " not defined in key file" ;
	ContainerStorageException pe ;
	pe.set_error_description( s ) ;
	throw pe;
    }
}

ContainerStorageCedar::~ContainerStorageCedar()
{
}

void
ContainerStorageCedar::look_for( DODSContainer &d )
{
    d.set_valid_flag( true ) ;
    d.set_real_name( _cedar_base + "/" + d.get_symbolic_name() + ".cbf" ) ;
    d.set_container_type( "cedar" ) ;
}

void
ContainerStorageCedar::add_container( const string &s_name,
				      const string &r_ame,
				      const string &type )
{
    throw ContainerStorageException( "Unable to add a container to Cedar Persistence" ) ;
}

bool
ContainerStorageCedar::del_container( const string &s_name )
{
    throw ContainerStorageException( "Unable to remove a container from Cedar Persistence" ) ;
    return false ;
}

void
ContainerStorageCedar::show_containers( DODSInfo &info )
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

