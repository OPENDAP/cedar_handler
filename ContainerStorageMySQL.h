// ContainerStorageMySQL.h

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

#ifndef ContainerStorageMySQL_h_
#define ContainerStorageMySQL_h_ 1

#include <string>

using std::string ;

#include "ContainerStorage.h"

class DODSMySQLQuery ;

/** @brief persistent storage of containers in a MySQL database
 *
 * This implementation of ContainerStorage looks up container
 * information in a MySQL database. The database is sepcified in the dods
 * initialization file using the keys:
 *
 * DODS.Container.Persistence.MySQL.&lt;name&gt;.server
 * DODS.Container.Persistence.MySQL.&lt;name&gt;.user
 * DODS.Container.Persistence.MySQL.&lt;name&gt;.password
 * DODS.Container.Persistence.MySQL.&lt;name&gt;.database
 *
 * where &lt;name&gt; is the name of this instance of the persistent store.
 *
 * The table name used is tbl_containers and has the following columns
 *
 * Table tbl_containers.
 * Defines the version of CEDARDB	
 * 
 * +---------------+-----------+------+-----+---------+-------+
 * | Field         | Type      | Null | Key | Default | Extra |
 * +---------------+-----------+------+-----+---------+-------+
 * | SYMBOLIC_NAME | char(250) |      | PRI |         |       |
 * | REAL_NAME     | char(250) |      |     |         |       |
 * | CONTAINER_TYPE| char(20)  |      |     |         |       |
 * +---------------+-----------+------+-----+---------+-------+
 *
 * @see ContainerStorage
 * @see DODSContainer
 * @see DODSKeys
 */
class ContainerStorageMySQL : public ContainerStorage
{
    DODSMySQLQuery *		_query ;
public:
    				ContainerStorageMySQL( const string &name ) ;
    virtual			~ContainerStorageMySQL();

    virtual void 		look_for( DODSContainer &d ) ;
    virtual void		add_container( string s_name, string r_name,
				       string type ) ;
    virtual bool		rem_container( const string &s_name ) ;

    virtual void		show_containers( DODSInfo &info ) ;
};

#endif // ContainerStorageMySQL_h_

