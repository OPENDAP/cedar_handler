// CedarReadKinst.cc

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

#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>

using std::ostringstream ;
using std::setw ;
using std::setprecision ;
using std::setfill ;
using std::left ;

#include "CedarReadKinst.h"
#include "CedarDB.h"
#include "CedarDBResult.h"
#include "BESInternalError.h"

map<int,CedarReadKinst::CedarInstrument> CedarReadKinst::stored_list ;

/** @brief given an instrument id (kinst) load the information from the
 * database
 *
 * Loads the information about the given instrument specified by the
 * instrument id (kinst) and stores it in the stored_list. If the instrument
 * information already exists, then just return the stored information, else
 * go get the information from the Catalog database.
 *
 * columns of the table needed are KINST, INST_NAME, PREFIX
 *
 * FIXME: With the re-work of the CEDARCATALOG, LATITUDE, LONGITUDE, and
 * ALTITUDE are no win the tbl_site table, which is not yet populated
 *
 * @param kinst instrument id to look up
 */
void
CedarReadKinst::Load_Instrument( int kinst )
{
    // see if the request kinst is already stored. If not, go get it and
    // store it. Only get what is requested
    map<int,CedarReadKinst::CedarInstrument>::iterator iter ;
    iter = CedarReadKinst::stored_list.find( kinst ) ;
    if( iter == CedarReadKinst::stored_list.end() )
    {
	CedarDB *db = CedarDB::DB( "Catalog" ) ;
	if( !db )
	{
	    string err = "Unable to establish connection to Catalog database" ;
	    throw BESInternalError( err, __FILE__, __LINE__ ) ;
	}

	ostringstream query ;
	query << "SELECT KINST, INST_NAME, PREFIX from tbl_instrument where KINST = " << kinst ;
	CedarDBResult *result = db->run_query( query.str() ) ;
	if( !result )
	{
	    db->close() ;
	    string err =
		(string)"Query " + query.str() + " failed to return results";
	    throw BESInternalError( err, __FILE__, __LINE__ ) ;
	}
	if( result->is_empty_set() )
	{
	    db->close() ;
	    string err =
		(string)"Query " + query.str() + " returned the empty set";
	    throw BESInternalError( err, __FILE__, __LINE__ ) ;
	}
	if( result->get_num_rows() != 1 )
	{
	    db->close() ;
	    string err =
		(string)"Query " + query.str() + " returned too many results";
	    throw BESInternalError( err, __FILE__, __LINE__ ) ;
	}

	result->first_row() ;

	CedarReadKinst::CedarInstrument instrument ;
	instrument.kinst = atoi( (*result)["KINST"].c_str() ) ;
	instrument.name = (*result)["INST_NAME"] ;
	instrument.prefix = (*result)["PREFIX"] ;
	// FIXME: When tbl_site filled in get the information from there
	instrument.latitude = 0.0 ;
	instrument.longitude = 0.0 ;
	instrument.altitude = 0.0 ;
	//instrument.latitude = atof( (*result)["LATITUDE"].c_str() ) ;
	//instrument.longitude = atof( (*result)["LONGITUDE"].c_str() ) ;
	//instrument.altitude = atof( (*result)["ALT"].c_str() ) ;
	CedarReadKinst::stored_list[kinst] = instrument ;

	db->close() ;
    }
}

string
CedarReadKinst::Get_Instrument( int kinst )
{
    CedarReadKinst::Load_Instrument( kinst ) ;
    map<int,CedarReadKinst::CedarInstrument>::iterator iter ;
    iter = CedarReadKinst::stored_list.find( kinst ) ;
    if( iter == CedarReadKinst::stored_list.end() )
    {
	ostringstream err ;
	err << "Failed to retrieve information for kinst " << kinst ;
	throw BESInternalError( err.str(), __FILE__, __LINE__ ) ;
    }

    ostringstream strm ;
    strm << left << setw( 39 ) << setfill( ' ' ) << iter->second.name ;
    strm << left << setprecision( 5 ) << setw( 13 ) << setfill( ' ' )
	 << iter->second.latitude ;
    strm << left << setprecision( 5 ) << setw( 13 ) << setfill( ' ' )
	 << iter->second.longitude ;
    strm << left << setprecision( 5 ) << setw( 9 ) << setfill( ' ' )
	 << iter->second.altitude ;
    strm << left << setw( 3 ) << setfill( ' ' ) << iter->second.prefix ;
    return strm.str() ;
}

string
CedarReadKinst::Get_Name( int kinst )
{
    CedarReadKinst::Load_Instrument( kinst ) ;
    map<int,CedarReadKinst::CedarInstrument>::iterator iter ;
    iter = CedarReadKinst::stored_list.find( kinst ) ;
    if( iter == CedarReadKinst::stored_list.end() )
    {
	ostringstream err ;
	err << "Failed to retrieve instrument name for kinst " << kinst ;
	throw BESInternalError( err.str(), __FILE__, __LINE__ ) ;
    }
    return iter->second.name ;
}

string
CedarReadKinst::Get_Prefix( int kinst )
{
    CedarReadKinst::Load_Instrument( kinst ) ;
    map<int,CedarReadKinst::CedarInstrument>::iterator iter ;
    iter = CedarReadKinst::stored_list.find( kinst ) ;
    if( iter == CedarReadKinst::stored_list.end() )
    {
	ostringstream err ;
	err << "Failed to retrieve instrument prefix for kinst " << kinst ;
	throw BESInternalError( err.str(), __FILE__, __LINE__ ) ;
    }
    return iter->second.prefix ;
}

double
CedarReadKinst::Get_Longitude( int kinst )
{
    CedarReadKinst::Load_Instrument( kinst ) ;
    map<int,CedarReadKinst::CedarInstrument>::iterator iter ;
    iter = CedarReadKinst::stored_list.find( kinst ) ;
    if( iter == CedarReadKinst::stored_list.end() )
    {
	ostringstream err ;
	err << "Failed to retrieve instrument longitude for kinst " << kinst ;
	throw BESInternalError( err.str(), __FILE__, __LINE__ ) ;
    }
    return iter->second.longitude ;
}

double
CedarReadKinst::Get_Latitude( int kinst )
{
    CedarReadKinst::Load_Instrument( kinst ) ;
    map<int,CedarReadKinst::CedarInstrument>::iterator iter ;
    iter = CedarReadKinst::stored_list.find( kinst ) ;
    if( iter == CedarReadKinst::stored_list.end() )
    {
	ostringstream err ;
	err << "Failed to retrieve instrument latitude for kinst " << kinst ;
	throw BESInternalError( err.str(), __FILE__, __LINE__ ) ;
    }
    return iter->second.latitude ;
}

double
CedarReadKinst::Get_Altitude( int kinst )
{
    CedarReadKinst::Load_Instrument( kinst ) ;
    map<int,CedarReadKinst::CedarInstrument>::iterator iter ;
    iter = CedarReadKinst::stored_list.find( kinst ) ;
    if( iter == CedarReadKinst::stored_list.end() )
    {
	ostringstream err ;
	err << "Failed to retrieve instrument altitude for kinst " << kinst ;
	throw BESInternalError( err.str(), __FILE__, __LINE__ ) ;
    }
    return iter->second.altitude ;
}

