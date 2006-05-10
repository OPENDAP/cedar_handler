// CedarAuthenticate.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include <iostream>
#include <sstream>

using std::endl ;
using std::ostringstream ;

#include <time.h>

#include "CedarAuthenticate.h"
#include "DODSMySQLQuery.h"
#include "DODSMemoryException.h"
#include "TheDODSKeys.h"
#include "CedarAuthenticateException.h"
#include "OPeNDAPDataNames.h"
#include "DODSLog.h"

/** @brief Cedar authentication using MySQL database
 *
 * First reads the key/value pairs from the opendap initiailization file
 * using TheDODSKeys in order to make a connection to the MySQL database
 * and to determine if authentication is turned on or off. The key/value
 * pairs used from the intialization file are:
 *
 * Cedar.Authenticate.MySQL.server=&lt;serverName&gt;
 * Cedar.Authenticate.MySQL.user=&lt;userName&gt;
 * Cedar.Authenticate.MySQL.password=&lt;encryptedPassword&gt;
 * Cedar.Authenticate.MySQL.database=&lt;databaseName&gt;
 * Cedar.Authenticate.MySQL.mode=&lt;on|off&gt;
 *
 * Then authenticates the user specified in the DODSDataHandlerInterface
 * using a MySQL database. The table tbl_session in the MySQL database is
 * used to authenticate the user. The session information must be created
 * prior to this method being called.
 *
 * @param dhi contains the user name of the user to be authenticated
 * @throws CedarAuthenticateException if unable to read information from
 * initialization file or if unable to authenticate the user.
 * @throws DODSMySQLConnectException if unable to connect to the MySQL
 * database.
 * @throws DODSMySQLQueryException if unable to query the MySQL database.
 * @see _DODSDataHandlerInterface
 * @see DODSMySQLQuery
 * @see CedarAuthenticateException
 * @see DODSMySQLConnectException
 * @see DODSMySQLQueryException
 * @see DODSKeys
 */
bool
CedarAuthenticate::authenticate( DODSDataHandlerInterface &dhi )
{
    if( DODSLog::TheLog()->is_verbose() )
    {
	*(DODSLog::TheLog()) << "authenticating" << endl ;
    }
    bool found = false ;
    string my_key = "Cedar.Authenticate.MySQL." ;

    string my_server = TheDODSKeys::TheKeys()->get_key( my_key + "server", found ) ;
    if( found == false )
    {
	CedarAuthenticateException pe ;
	pe.set_error_description( "MySQL server not specified for authentication" ) ;
	throw pe ;
    }
    if( DODSLog::TheLog()->is_verbose() )
    {
	*(DODSLog::TheLog()) << "  server = " << my_server << endl ;
    }

    string my_user = TheDODSKeys::TheKeys()->get_key( my_key + "user", found  ) ;
    if( found == false )
    {
	CedarAuthenticateException pe ;
	pe.set_error_description( "MySQL user not specified for authentication" ) ;
	throw pe ;
    }
    if( DODSLog::TheLog()->is_verbose() )
    {
	*(DODSLog::TheLog()) << "  MySQL user = " << my_user << endl ;
    }

    string my_password = TheDODSKeys::TheKeys()->get_key( my_key + "password", found  ) ;
    if( found == false )
    {
	CedarAuthenticateException pe ;
	pe.set_error_description( "MySQL password not specified for authentication" ) ;
	throw pe ;
    }
    if( DODSLog::TheLog()->is_verbose() )
    {
	*(DODSLog::TheLog()) << "  MySQL password = " << my_password << endl ;
    }

    string my_database=TheDODSKeys::TheKeys()->get_key( my_key + "database", found ) ;
    if( found == false )
    {
	CedarAuthenticateException pe ;
	pe.set_error_description( "MySQL database not specified for authentication" ) ;
	throw pe ;
    }
    if( DODSLog::TheLog()->is_verbose() )
    {
	*(DODSLog::TheLog()) << "  MySQL database = " << my_database << endl ;
    }
    
    bool port_found = false ;
    string my_sport = TheDODSKeys::TheKeys()->get_key( my_key + "port",
						       port_found ) ;
    int mysql_port = 0 ;
    if( port_found )
    {
	mysql_port = atoi( my_sport.c_str() ) ;
	if( mysql_port == 0 )
	{
	    CedarAuthenticateException pe ;
	    pe.set_error_description( "MySQL port must be set to a valid port number" ) ;
	    throw pe ;
	}
    }
    if( DODSLog::TheLog()->is_verbose() )
    {
	*(DODSLog::TheLog()) << "  MySQL port = " << mysql_port << endl ;
    }

    bool sock_found = false ;
    string mysql_sock = TheDODSKeys::TheKeys()->get_key( my_key + "socket",
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
	CedarAuthenticateException pe ;
	pe.set_error_description( "MySQL socket must be set to a non-empty string" ) ;
	throw pe ;
    }
    if( DODSLog::TheLog()->is_verbose() )
    {
	*(DODSLog::TheLog()) << "  MySQL socket = " << mysql_sock << endl ;
    }

    bool enforce_authentication = false ;
    string authentication_mode = TheDODSKeys::TheKeys()->get_key( my_key + "mode", found ) ;
    if( found == false )
    {
	CedarAuthenticateException pe ;
	pe.set_error_description( "Authentication mode (on/off) is not specified" ) ;
	throw pe ;
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
		CedarAuthenticateException pe ;
		pe.set_error_description( "Authentication mode is neither on nor off" ) ;
		throw pe ;
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
	    DODSMemoryException ex ;
	    ex.set_error_description( "Can not get memory for query object" );
	    ex.set_amount_of_memory_required( sizeof( DODSMySQLQuery ) ) ;
	    throw ex ;
	}
	catch( DODSException &e )
	{
	    if( DODSLog::TheLog()->is_verbose() )
	    {
		*(DODSLog::TheLog()) << "error logging in: " << e.get_error_description() << endl ;
	    }
	    CedarAuthenticateException pe ;
	    pe.set_error_description( e.get_error_description() ) ;
	    throw pe ;
	}

	// get the current date and time
	string query_str = "select USER_NAME from tbl_sessions " ;
	query_str += "where USER_NAME=\"" + dhi.data[USER_NAME] + "\";" ;
	query->run_query( query_str ) ;
	if( !query->is_empty_set() )
	{
	    if( (query->get_nfields() != 1) )
	    {
		ostringstream err_str ;
		err_str << "Unable to authenticate user "
		        << dhi.data[USER_NAME] << endl
			<< "Invalid data from MySQL: "
			<< query->get_nrows() << " rows and "
			<< query->get_nfields() << " fields returned" ;
		CedarAuthenticateException pe ;
		pe.set_error_description( err_str.str() ) ;
		throw pe ;
	    }
	}
	else
	{
	    ostringstream err_str ;
	    err_str << "Unable to authenticate user "
	            << dhi.data[USER_NAME] ;
	    CedarAuthenticateException pe ;
	    pe.set_error_description( err_str.str() ) ;
	    throw pe ;
	}

	if( query ) delete query ;
	query = 0 ;
    }

    return true ;
}

// $Log: CedarAuthenticate.cc,v $
