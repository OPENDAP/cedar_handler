// ContainerStorageMySQL.cc

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

#include "ContainerStorageMySQL.h"
#include "BESContainer.h"
#include "DODSMySQLQuery.h"
#include "ContainerStorageException.h"
#include "BESMemoryException.h"
#include "TheBESKeys.h"
#include "BESInfo.h"

/** @brief pull container information from the specified mysql database
 *
 * Constructs a ContainerStorageMySQL, pulling the mysql database
 * information from the dods initialization file and opening up a connection
 * to the MySQL database.
 *
 * The keys in the dods initialization file that represent the database are:
 *
 * BES.Container.Persistence.MySQL.&lt;name&gt;.server
 * BES.Container.Persistence.MySQL.&lt;name&gt;.user
 * BES.Container.Persistence.MySQL.&lt;name&gt;.password
 * BES.Container.Persistence.MySQL.&lt;name&gt;.database
 *
 * where &lt;name&gt; is the name of this instance of the persistent store.
 *
 * @param n name of this persistent store.
 * @throws ContainerStorageException if unable to retrieve the MySQL
 * database connection information from the dods initialization file.
 * @throws BESMySQLConnectException if unable to connect to the MySQL
 * database.
 */
ContainerStorageMySQL::ContainerStorageMySQL( const string &n )
    :ContainerStorage( n )
{
    bool found = false ;
    string my_key = "BES.Container.Persistence.MySQL." + n + "." ;

    string my_server = TheBESKeys::TheKeys()->get_key( my_key + "server", found ) ;
    if( found == false )
    {
	string s = "MySQL server not specified for " + n ;
	throw ContainerStorageException( s, __FILE__, __LINE__ ) ;
    }

    string my_user = TheBESKeys::TheKeys()->get_key( my_key + "user", found  ) ;
    if( found == false )
    {
	string s = "MySQL user not specified for " + n ;
	throw ContainerStorageException( s, __FILE__, __LINE__ ) ;
    }

    string my_password = TheBESKeys::TheKeys()->get_key( my_key + "password", found  ) ;
    if( found == false )
    {
	string s = "MySQL password not specified for " + n ;
	throw ContainerStorageException( s, __FILE__, __LINE__ ) ;
    }

    string my_database=TheBESKeys::TheKeys()->get_key( my_key + "database", found ) ;
    if( found == false )
    {
	string s = "MySQL database not specified for " + n ;
	throw ContainerStorageException( s, __FILE__, __LINE__ ) ;
    }

    try
    {
	_query = new DODSMySQLQuery( my_server, my_user,
				     my_password, my_database ) ;
    }
    catch( bad_alloc::bad_alloc )
    {
	string s = "Can not get memory for Persistence object" ;
	throw BESMemoryException( s, __FILE__, __LINE__ ) ;
    }
}

ContainerStorageMySQL::~ContainerStorageMySQL()
{
    if( _query ) delete _query ;
    _query =0 ;
}

/** @brief looks for the specified container information in the MySQL
 * database.
 *
 * Using the symbolic name specified in the passed BESContianer object, looks
 * up the container information for the symbolic name in the MySQL database
 * opened in the constructor.
 *
 * If a match is made with the symbolic name found in the container then the
 * information is stored in the passed container object and the is_valid flag
 * is set to true. If not found, then is_valid is set to false.
 *
 * @param d container to look for and, if found, store the information in.
 * @throws ContainerStorageException if the information in the
 * database is corrupt
 * @throws DODSMySQLQueryException if error running the query
 * @see BESContainer
 */
void
ContainerStorageMySQL::look_for( BESContainer &d )
{
    d.set_valid_flag( false ) ;
    string query = "select REAL_NAME, CONTAINER_TYPE from tbl_containers where SYMBOLIC_NAME=\"";
    query += d.get_symbolic_name().c_str();
    query += "\";";
    _query->run_query( query );
    if( !_query->is_empty_set() )
    {
	if( (_query->get_nrows() != 1) || (_query->get_nfields() != 2) )
	{
	    string s = "Invalid data from MySQL" ;
	    throw ContainerStorageException( s, __FILE__, __LINE__ ) ;
	}
	else
	{
	    d.set_valid_flag( true ) ;
	    _query->first_row() ;
	    _query->first_field() ;
	    d.set_real_name( _query->get_field() ) ;
	    _query->next_field() ;
	    d.set_container_type( _query->get_field() ) ;
	}
    }
}

/** @brief adds a container with the provided information
 *
 * This method adds a container to the persistence store with the
 * specified information. This functionality is not currently supported for
 * MySQL persistence.
 *
 * @param s_name symbolic name for the container
 * @param r_name real name for the container
 * @param type type of data represented by this container
 */
void
ContainerStorageMySQL::add_container( string s_name,
                                            string r_name,
					    string type )
{
    string s = "Unable to add a container to MySQL container storage, not yet implemented" ;
    throw ContainerStorageException( s, __FILE__, __LINE__ ) ;
}

/** @brief removes a container with the given symbolic name, not implemented
 * in this implementation class.
 *
 * This method removes a container to the persistence store with the
 * given symbolic name. It deletes the container.
 *
 * @param s_name symbolic name for the container
 * @return true if successfully removed and false otherwise
 */
bool
ContainerStorageMySQL::rem_container( const string &s_name )
{
    string s = "Unable to remove a container from a MySQL container persistece, not yet implemented" ;
    throw ContainerStorageException( s, __FILE__, __LINE__ ) ;
    return false ;
}

/** @brief show information for each container in this persistent store
 *
 * For each container in this persistent store, add infomation about each of
 * those containers. The information added to the information object
 * includes a line for each container within this persistent store which 
 * includes the symbolic name, the real name, and the data type, 
 * separated by commas.
 *
 * In the case of this persistent store the MySQL database table is queried
 * and the symbolic name, real name and container type are retrieved and
 * added to the information object.
 *
 * @param info object to store the container and persistent store information
 * @see BESInfo
 */
void
ContainerStorageMySQL::show_containers( BESInfo &info )
{
    info.add_data( get_name() ) ;
    info.add_data( "\n" ) ;
    string query = "select SYMBOLIC_NAME, REAL_NAME, CONTAINER_TYPE from tbl_containers;" ;
    _query->run_query( query );
    if( !_query->is_empty_set() )
    {
	bool row = _query->first_row() ;
	while( row )
	{
	    if( ( _query->get_nfields() != 3 ) )
	    {
		string s = "Invalid data from MySQL" ;
		throw ContainerStorageException( s, __FILE__, __LINE__ ) ;
	    }
	    _query->first_field() ;
	    string sym = _query->get_field() ;
	    _query->next_field() ;
	    string real = _query->get_field() ;
	    _query->next_field() ;
	    string type = _query->get_field() ;
	    string line = sym + "," + real + "," + type + "\n" ;
	    info.add_data( line ) ;
	}
    }
}

