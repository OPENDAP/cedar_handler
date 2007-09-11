// CedarAuthenticate.cc

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
#include <sstream>
#include <new>

using std::endl ;
using std::ostringstream ;
using std::bad_alloc ;

#include <time.h>

#include "CedarAuthenticate.h"
#include "DODSMySQLQuery.h"
#include "BESMemoryException.h"
#include "TheBESKeys.h"
#include "CedarAuthenticateException.h"
#include "BESDataNames.h"
#include "BESLog.h"

/** @brief Cedar authentication using MySQL database
 *
 * First reads the key/value pairs from the opendap initiailization file
 * using TheBESKeys in order to make a connection to the MySQL database
 * and to determine if authentication is turned on or off. The key/value
 * pairs used from the intialization file are:
 *
 * Cedar.Authenticate.MySQL.server=&lt;serverName&gt;
 * Cedar.Authenticate.MySQL.user=&lt;userName&gt;
 * Cedar.Authenticate.MySQL.password=&lt;encryptedPassword&gt;
 * Cedar.Authenticate.MySQL.database=&lt;databaseName&gt;
 * Cedar.Authenticate.MySQL.mode=&lt;on|off&gt;
 *
 * Then authenticates the user specified in the BESDataHandlerInterface
 * using a MySQL database. The table cedar_session in the MySQL database is
 * used to authenticate the user. The session information must be created
 * prior to this method being called.
 *
 * @param dhi contains the user name of the user to be authenticated
 * @throws CedarAuthenticateException if unable to read information from
 * initialization file or if unable to authenticate the user.
 * @throws DODSMySQLConnectException if unable to connect to the MySQL
 * database.
 * @throws DODSMySQLQueryException if unable to query the MySQL database.
 * @see _BESDataHandlerInterface
 * @see DODSMySQLQuery
 * @see CedarAuthenticateException
 * @see DODSMySQLConnectException
 * @see DODSMySQLQueryException
 * @see BESKeys
 */
bool
CedarAuthenticate::authenticate( BESDataHandlerInterface &dhi )
{
    if( BESLog::TheLog()->is_verbose() )
    {
	*(BESLog::TheLog()) << "authenticating" << endl ;
    }
    bool found = false ;
    string my_key = "Cedar.Authenticate.MySQL." ;

    string my_server = TheBESKeys::TheKeys()->get_key( my_key + "server", found ) ;
    if( found == false )
    {
	string s = (string)"Unable to authenticate: MySQL server not set "
	           + "in BES configuration file" ;
	throw CedarAuthenticateException( s, __FILE__, __LINE__ ) ;
    }
    if( BESLog::TheLog()->is_verbose() )
    {
	*(BESLog::TheLog()) << "  server = " << my_server << endl ;
    }

    string my_user = TheBESKeys::TheKeys()->get_key( my_key + "user", found  ) ;
    if( found == false )
    {
	string s = (string)"Unable to authenticate: MySQL user not set "
	           + "in BES configuration file" ;
	throw CedarAuthenticateException( s, __FILE__, __LINE__ ) ;
    }
    if( BESLog::TheLog()->is_verbose() )
    {
	*(BESLog::TheLog()) << "  MySQL user = " << my_user << endl ;
    }

    string my_password = TheBESKeys::TheKeys()->get_key( my_key + "password", found  ) ;
    if( found == false )
    {
	string s = (string)"Unable to authenticate: MySQL password not set "
	           + "in BES configuration file" ;
	throw CedarAuthenticateException( s, __FILE__, __LINE__ ) ;
    }
    if( BESLog::TheLog()->is_verbose() )
    {
	*(BESLog::TheLog()) << "  MySQL password = " << my_password << endl ;
    }

    string my_database=TheBESKeys::TheKeys()->get_key( my_key + "database", found ) ;
    if( found == false )
    {
	string s = (string)"Unable to authenticate: MySQL database not set "
	           + "in BES configuration file" ;
	throw CedarAuthenticateException( s, __FILE__, __LINE__ ) ;
    }
    if( BESLog::TheLog()->is_verbose() )
    {
	*(BESLog::TheLog()) << "  MySQL database = " << my_database << endl ;
    }
    
    bool port_found = false ;
    string my_sport = TheBESKeys::TheKeys()->get_key( my_key + "port",
						       port_found ) ;
    int mysql_port = 0 ;
    if( port_found )
    {
	mysql_port = atoi( my_sport.c_str() ) ;
	if( mysql_port == 0 )
	{
	    string s = "Unable to authenticate: MySQL port " + my_sport
	               + " is not valid in BES configuration file" ;
	    throw CedarAuthenticateException( s, __FILE__, __LINE__ ) ;
	}
    }
    if( BESLog::TheLog()->is_verbose() )
    {
	*(BESLog::TheLog()) << "  MySQL port = " << mysql_port << endl ;
    }

    bool sock_found = false ;
    string mysql_sock = TheBESKeys::TheKeys()->get_key( my_key + "socket",
						         sock_found ) ;
    if( !sock_found && !port_found )
    {
	char *mysql_home = getenv( "MYSQL_HOME" ) ;
	if( !mysql_home )
	{
	    mysql_sock = "/tmp/mysql.sock" ;
	}
	else
	{
	    mysql_sock = string( mysql_home ) + "/mysql.sock" ;
	}
    }
    else if( sock_found && mysql_sock != "" )
    {
	mysql_port = 0 ;
    }
    else if( sock_found && mysql_sock == "" )
    {
	string s = (string)"Unable to authenticate: MySQL socket is not set "
		   + "in BES configuration file" ;
	throw CedarAuthenticateException( s, __FILE__, __LINE__ ) ;
    }
    if( BESLog::TheLog()->is_verbose() )
    {
	*(BESLog::TheLog()) << "  MySQL socket = " << mysql_sock << endl ;
    }

    bool enforce_authentication = false ;
    string authentication_mode = TheBESKeys::TheKeys()->get_key( my_key + "mode", found ) ;
    if( found == false )
    {
	string s = (string)"Unable to authenticate: "
	           + "Authentication mode (on/off) is not set "
		   + "in BES configuration file" ;
	throw CedarAuthenticateException( s, __FILE__, __LINE__ ) ;
    }
    else
    {
	if( authentication_mode == "on" )
	    enforce_authentication = true ;
	else
	{
	    if( authentication_mode == "off" )
		enforce_authentication = false ;
	    else
	    {
		string s = "Unable to authenticate: Authentication mode set to "
		           + authentication_mode + " in BES configuration file"
			   + ", should be set to on or off)" ;
		throw CedarAuthenticateException( s, __FILE__, __LINE__ ) ;
	    }
	}
    }

    if( enforce_authentication )
    {
	// build the query objects, which connects to the database
	DODSMySQLQuery *query = 0 ;
	try
	{
	    query = new DODSMySQLQuery( my_server, my_user,
					my_password, my_database,
					mysql_port, mysql_sock ) ;
	}
	catch( bad_alloc::bad_alloc )
	{
	    string s = "Can not get memory for MySQL Query object" ;
	    throw BESMemoryException( s, __FILE__, __LINE__ ) ;
	}
	catch( BESException &e )
	{
	    if( BESLog::TheLog()->is_verbose() )
	    {
		*(BESLog::TheLog()) << "error logging in: "
		                    << e.get_message() << endl ;
	    }
	    throw CedarAuthenticateException( e.get_message(), __FILE__, __LINE__ ) ;
	}

	// get the current date and time
	string query_str = "select USER_NAME from cedar_sessions " ;
	query_str += "where USER_NAME=\"" + dhi.data[USER_NAME] + "\"" ;
	if( dhi.data[USER_TOKEN] != "" )
	{
	    query_str += " AND TOKEN=\"" + dhi.data[USER_TOKEN] + "\";" ;
	}
	else
	{
	    query_str += " AND TOKEN IS NULL;" ;
	}
	query->run_query( query_str ) ;
	if( !query->is_empty_set() )
	{
	    if( (query->get_nfields() != 1) )
	    {
		ostringstream s ;
		s << "Unable to authenticate user "
		  << dhi.data[USER_NAME] << endl
		  << "Invalid data from MySQL: "
		  << query->get_nrows() << " rows and "
		  << query->get_nfields() << " fields returned" ;
		throw CedarAuthenticateException( s.str(), __FILE__, __LINE__ );
	    }
	}
	else
	{
	    ostringstream s ;
	    s << "Unable to authenticate user "
	      << dhi.data[USER_NAME] ;
	    throw CedarAuthenticateException( s.str(), __FILE__, __LINE__ ) ;
	}

	if( query ) delete query ;
	query = 0 ;
    }

    return true ;
}

