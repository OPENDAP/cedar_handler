// DODSMySQLResult.h

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

#ifndef DODSMySQLResult_h_
#define DODSMySQLResult_h_ 1

#include <string>
#include <vector>

using std::vector ;
using std::string ;

class DODSMySQLResult
{
private:
    typedef vector<string> row;
    typedef vector<row> matrix;

    matrix *		_matrix;
    int			_nrows;
    int			_nfields;
    int			_row_position;
    int			_field_position;

    			DODSMySQLResult( const DODSMySQLResult& ) {}
public:
    			DODSMySQLResult( const int &n_rows,
					 const int &n_fields ) ; 
    			~DODSMySQLResult();

    int			get_nrows() { return _nrows ; }
    int			get_nfields() { return _nfields ; }
    void		set_field( const char *s ) ;
    string		get_field() ;
    bool		first_field() ;
    bool		next_field() ;
    bool		next_row() ;
    bool		first_row() ;
} ;

#endif //DODSMySQLResult_h_

