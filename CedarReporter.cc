// CedarReporter.cc

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

#include "CedarReporter.h"
#include "TheBESKeys.h"
#include "BESLogException.h"
#include "BESDataNames.h"

CedarReporter::CedarReporter()
    : BESReporter(),
      _file_buffer( 0 )
{
    bool found = false ;
    string log_name = TheBESKeys::TheKeys()->get_key( "Cedar.LogName", found );
    if( log_name == "" )
    {
	throw BESLogException( "can not determine Cedar log name", __FILE__, __LINE__ ) ;
    }
    else
    {
	_file_buffer = new ofstream( log_name.c_str(), ios::out | ios::app ) ;
	if( !(*_file_buffer) )
	{
	    string s = "can not open Cedar log file " + log_name ;;
	    throw BESLogException( s, __FILE__, __LINE__ ) ;
	} 
    }
}

CedarReporter::~CedarReporter()
{
    if( _file_buffer )
    {
	delete _file_buffer ;
	_file_buffer = 0 ;
    }
}

void
CedarReporter::report( const BESDataHandlerInterface &dhi )
{
    const time_t sctime = time( NULL ) ;
    const struct tm *sttime = localtime( &sctime ) ; 
    char zone_name[10] ;
    strftime( zone_name, sizeof( zone_name ), "%Z", sttime ) ;
    char *b = asctime( sttime ) ;
    *(_file_buffer) << "[" << zone_name << " " ;
    for(register int j = 0; b[j] != '\n'; j++ )
	*(_file_buffer) << b[j] ;
    *(_file_buffer) << "] " ;

    string user_name = "" ;
    BESDataHandlerInterface::data_citer citer ;
    citer = dhi.data_c().find( USER_NAME ) ;
    if( citer != dhi.data_c().end() )
	user_name = (*citer).second ;

    if( user_name == "" )
	*(_file_buffer) << "USER_UNKNOWN" ;
    else
	*(_file_buffer) << user_name ;

    string request = "" ;
    citer = dhi.data_c().find( DATA_REQUEST ) ;
    if( citer != dhi.data_c().end() )
	request = (*citer).second ;

    string real = "" ;
    citer = dhi.data_c().find( REAL_NAME_LIST ) ;
    if( citer != dhi.data_c().end() )
	real = (*citer).second ;

    *(_file_buffer) << " " << dhi.action << " " << real << " \"" 
                    << request << "\"" << endl ;
}

