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
#include "BESInternalError.h"
#include "BESDataNames.h"
#include "CedarDB.h"

CedarReporter::CedarReporter()
    : BESReporter()
{
    _db = CedarDB::DB( "Reporter" ) ;
    if( !_db )
    {
	string s = "Unable to open Cedar Reporter database" ;
	throw BESInternalError( s, __FILE__, __LINE__ ) ;
    }
}

CedarReporter::~CedarReporter()
{
    // The database is closed in the CedarModule class
}

void
CedarReporter::report( BESDataHandlerInterface &dhi )
{
    if( dhi.action.substr( 0, 3 ) != "get" )
	return ;

    string product = dhi.action.substr( 4, dhi.action.length() - 4 ) ;

    string user_name = "" ;
    BESDataHandlerInterface::data_citer citer ;
    citer = dhi.data_c().find( USER_NAME ) ;
    if( citer != dhi.data_c().end() )
	user_name = (*citer).second ;
    if( user_name == "" )
	user_name = "USER_UNKNOWN" ;

    string requested ;
    string constraint ;
    bool isfirst = true ;
    dhi.first_container() ;
    while( dhi.container )
    {
	if( !isfirst )
	    requested += ", " ;
	else
	    constraint = dhi.container->get_constraint() ;
	isfirst = false ;
	requested += dhi.container->get_symbolic_name() ;
	dhi.next_container() ;
    }

    string request = "" ;
    citer = dhi.data_c().find( DATA_REQUEST ) ;
    if( citer != dhi.data_c().end() )
	request = (*citer).second ;

    vector< vector<CedarDBColumn> > flds ;
    vector<CedarDBColumn> fld_set ;
    fld_set.push_back( CedarDBColumn( "user", user_name ) ) ;
    fld_set.push_back( CedarDBColumn( "requested", requested ) ) ;
    fld_set.push_back( CedarDBColumn( "product", product ) ) ;
    fld_set.push_back( CedarDBColumn( "constraint_expr", constraint ) ) ;
    flds.push_back( fld_set ) ;
    _db->insert( "tbl_cedar_report", flds ) ;
}

/** @brief dumps information about this object
 *
 * Displays the pointer value of this instance along with information about
 * the containers stored in this volatile list.
 *
 * @param strm C++ i/o stream to dump the information to
 */
void
CedarReporter::dump( ostream &strm ) const
{
    strm << BESIndent::LMarg << "CedarReporter::dump - ("
			     << (void *)this << ")" << endl ;
    BESIndent::Indent() ;
    if( _db ) _db->dump( strm ) ;
    BESIndent::UnIndent() ;
}

