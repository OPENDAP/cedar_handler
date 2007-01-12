// cedar_handler.cc

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

#include <iostream>
#include <fstream>

using std::cout ;
using std::endl ;
using std::ofstream ;

#include "config_cedar.h"

#include "CedarHandlerApp.h"
#include "BESException.h"
#include "Error.h"
#include "BESDebug.h"

int 
main(int argc, char *argv[])
{
    ostream *fstrm = new ofstream( "./opendap.debug" ) ;
    if( !(*fstrm) )
    {
	cout << "Oh Shit" << endl ;
	return 1 ;
    }
    BESDebug::Set_debugger( new BESDebug( fstrm ) ) ;
    BESDebug::Begin_debug() ;
    try
    {
	CedarHandlerApp app ;
	return app.main( argc, argv ) ;
    }
    catch( BESException &e )
    {
	cout << "HTTP/1.0 200 OK" << endl ;
	cout << "XDODS-Server: 3.5.2" << endl ;
	cout << "Date: 10/08/05" << endl ;
	cout << "Content-type: text/plain" << endl ;
	cout << endl ;
	cout << "Cedar Handler Caught unhandled exception" << endl ;
	cout << e.get_message() << endl ;
    }
    catch( Error &e )
    {
	cout << "HTTP/1.0 200 OK" << endl ;
	cout << "XDODS-Server: 3.5.2" << endl ;
	cout << "Date: 10/08/05" << endl ;
	cout << "Content-type: text/plain" << endl ;
	cout << endl ;
	cout << "Cedar Handler Caught unhandled exception" << endl ;
	cout << e.get_error_message() << endl ;
    }
    catch( ... )
    {
	cout << "HTTP/1.0 200 OK" << endl ;
	cout << "XDODS-Server: 3.5.2" << endl ;
	cout << "Date: 10/08/05" << endl ;
	cout << "Content-type: text/plain" << endl ;
	cout << endl ;
	cout << "Cedar Handler Caught unhandled, unknown exception" << endl ;
    }
    return 0 ;
}

