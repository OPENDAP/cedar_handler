// DODSMySQLChannel.cc

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

using std::endl ;

#include "DODSMySQLChannel.h"
#include "BESLog.h"

DODSMySQLChannel::DODSMySQLChannel()
{
    _channel_open = false ;
    _has_log = false ;
    _the_channel = 0 ;
    mysql_init( &_mysql ) ;
}

DODSMySQLChannel::~DODSMySQLChannel()
{
    if( _channel_open )
    {
	if( BESLog::TheLog()->is_verbose() )
	{
	    (*BESLog::TheLog()) << "MySQL channel disconnected from:" << endl
			         << "  server = " << _server << endl
			         << "  user = " << _user << endl
			         << "  database = " << _database << endl ;
	}
	mysql_close( _the_channel ) ;
    }
}

bool
DODSMySQLChannel::open( const char* server, const char* user,
			const char* password, const char* database)
{
    if( _channel_open )
	return true ;
    else
    {
	_server = server ;
	_user = user ;
	_database = database ;
	_the_channel = mysql_real_connect( &_mysql, server, user,
					   password, database, 0, 0, 0 ) ;
	if( !_the_channel )
	    return false ;
	else
	{
	    if( BESLog::TheLog()->is_verbose() )
	    {
		(*BESLog::TheLog()) << "MySQL channel connected to:" << endl
				     << "  server = " << _server << endl
				     << "  user = " << _user << endl
				     << "  database = " << _database << endl ;
	    }
	    _channel_open = true ;
	    return true ;
	}
    }
}

void
DODSMySQLChannel::close()
{
    if( _channel_open )
    {
	mysql_close( _the_channel ) ;
	_channel_open = 0 ;
    }
}

string
DODSMySQLChannel::get_error()
{
    if( _channel_open )
	_error = mysql_error( _the_channel ) ;      
    else
	_error = mysql_error( &_mysql ) ;
    return _error ;
}

