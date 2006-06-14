// DODSMySQLChannel.h

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

#ifndef DODSMySQLChannel_h_ 
#define DODSMySQLChannel_h_ 1

#include <string>
#include <mysql.h>

using std::string ;


class DODSMySQLChannel
{
private:
    string		_server, _user, _database ;
    string		_error;
    bool		_channel_open;
    bool		_has_log;
    MYSQL *		_the_channel;
    MYSQL		_mysql;

public:
    			DODSMySQLChannel();
    			~DODSMySQLChannel();

    bool		open( const char* server, const char* user,
			      const char* password, const char* database ) ;
    void		close();
    int			is_channel_open() const { return _channel_open ; }
    string		get_error();
    MYSQL *		get_channel() { return _the_channel ; }
};

#endif // DODSMySQLChannel_h_

