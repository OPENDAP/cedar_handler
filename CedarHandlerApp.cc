// CedarHandlerApp.cc

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

#include <signal.h>
#include <unistd.h>

#include <iostream>

using std::cout ;
using std::cerr ;
using std::endl ;
using std::flush ;

#include "CedarHandlerApp.h"
#include "CedarResponseNames.h"
#include "CedarFilter.h"
#include "BESCgiInterface.h"
#include "TheBESKeys.h"
#include "BESDefaultModule.h"
#include "BESDefaultCommands.h"

CedarHandlerApp::CedarHandlerApp()
    : _df( 0 )
{
}

CedarHandlerApp::~CedarHandlerApp()
{
    if( _df )
    {
	delete _df ;
	_df = 0 ;
    }
}

int
CedarHandlerApp::initialize( int argc, char **argv )
{
    BESDefaultModule::initialize( argc, argv ) ;
    BESDefaultCommands::initialize( argc, argv ) ;

    int retVal = BESBaseApp::initialize( argc, argv ) ;
    if( !retVal )
    {
	_df = new CedarFilter( argc, argv ) ;
    }

    return retVal ;
}

int
CedarHandlerApp::run()
{
    string my_key = "Cedar.Authenticate.Mode" ;
    TheBESKeys::TheKeys()->set_key( my_key, "off" ) ;
    BESCgiInterface d( CEDAR_NAME, *_df ) ;
    d.execute_request( "cedar" ) ;

    return 0 ;
}

/** @brief dumps information about this object
 *
 * Displays the pointer value of this instance and calls dump on the parent
 * class
 *
 * @param strm C++ i/o stream to dump the information to
 */
void
CedarHandlerApp::dump( ostream &strm ) const
{
    strm << BESIndent::LMarg << "CedarHandlerApp::dump - ("
			     << (void *)this << ")" << endl ;
    BESIndent::Indent() ;
    BESBaseApp::dump( strm ) ;
    BESIndent::UnIndent() ;
}

