// DODSMySQLResult.cc

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

#include "DODSMySQLResult.h"

DODSMySQLResult::DODSMySQLResult( const int &n, const int &f )
    : _nrows( n ),
      _nfields( f )
{
    _matrix=new matrix ;
    _matrix->reserve( _nrows ) ;
    row r ;
    r.reserve( _nfields ) ;
    for( register int j=0; j<_nrows; j++ )
	_matrix->push_back( r ) ;
}

DODSMySQLResult::~DODSMySQLResult()
{
    delete _matrix;
}

void
DODSMySQLResult::set_field( const char *s )
{
    string st = s ;
    (*_matrix)[_row_position].push_back( st ) ;
}

string
DODSMySQLResult::get_field()
{
    return (*_matrix)[_row_position][_field_position];
}

bool
DODSMySQLResult::first_field()
{
    if( _nfields > 0 )
    {
	_field_position = 0 ;
	return true ;
    }
    return false ;
}

bool
DODSMySQLResult::next_field()
{
    if( ++_field_position < _nfields )
	return true ;
    return false ;
}

bool
DODSMySQLResult::next_row()
{
    if( ++_row_position < _nrows )
	return true ;
    return false ;
}

bool
DODSMySQLResult::first_row()
{
    if( _nrows > 0 )
    {
	_row_position = 0 ;
	return true ;
    }
    return false ;
}

