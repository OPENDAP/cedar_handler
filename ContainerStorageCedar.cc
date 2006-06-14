// ContainerStorageCedar.cc

// This file is part of the OPeNDAP Cedar data handler, providing data
// access views for CedarWEB data

// Copyright (c) 2004,2005 University Corporation for Atmospheric Research
// Author: Patrick West <pwest@ucar.edu> and Jose Garcia <jgarcia@ucar.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// You can contact University Corporation for Atmospheric Research at
// 3080 Center Green Drive, Boulder, CO 80301
 
// (c) COPYRIGHT University Corporation for Atmostpheric Research 2004-2005
// Please read the full copyright statement in the file COPYRIGHT_UCAR.
//
// Authors:
//      pwest       Patrick West <pwest@ucar.edu>
//      jgarcia     Jose Garcia <jgarcia@ucar.edu>

#include <sstream>
#include <fstream>
#include <iostream>

using std::stringstream ;
using std::ifstream ;

#include "ContainerStorageCedar.h"
#include "BESContainer.h"
#include "TheBESKeys.h"
#include "BESContainerStorageException.h"
#include "BESInfo.h"
#include "OPeNDAPDir.h"
#include "OPeNDAPFile.h"
#include "CedarResponseNames.h"

ContainerStorageCedar::ContainerStorageCedar( const string &n )
    : BESContainerStorage( n )
{
    string key = "Cedar.BaseDir" ;
    bool found = false ;
    _cedar_base = TheBESKeys::TheKeys()->get_key( key, found ) ;
    if( _cedar_base == "" )
    {
	string s = key + " not defined in key file" ;
	BESContainerStorageException pe ;
	pe.set_error_description( s ) ;
	throw pe;
    }
}

ContainerStorageCedar::~ContainerStorageCedar()
{
}

void
ContainerStorageCedar::look_for( BESContainer &d )
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
    throw BESContainerStorageException( "Unable to add a container to Cedar Persistence" ) ;
}

bool
ContainerStorageCedar::del_container( const string &s_name )
{
    throw BESContainerStorageException( "Unable to remove a container from Cedar Persistence" ) ;
    return false ;
}

bool
ContainerStorageCedar::del_containers( )
{
    throw BESContainerStorageException( "Unable to remove a containers from Cedar Persistence" ) ;
    return false ;
}

void
ContainerStorageCedar::show_containers( BESInfo &info )
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

