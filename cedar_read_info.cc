// cedar_read_info.cc

#include "CedarBlock.h"
#include "CedarFile.h"
#include "CedarVersion.h"
#include "CedarErrorHandler.h"
#include "cedar_read_info.h"
#include "CedarException.h"
#include "CedarConstraintEvaluator.h"

#include <string>
#ifdef __GNUG__
#include <strstream>
using std::ostrstream ;
#else
#include <sstream>
#endif

void
route_buffer( const CedarLogicalRecord *pLogRec, DODSInfo &info )
{
    ostrstream *oss = new ostrstream() ;
    switch( pLogRec->get_type() )
    {
	case 2:
	    (*oss) << "\n" ;
	    pLogRec->save_prologue_header( oss->rdbuf() ) ;
	    pLogRec->save_prologue( oss->rdbuf() ) ;
	    pLogRec->save_data_buffer( oss->rdbuf() ) ;
	    break;
	case 3:
	    (*oss) << "\n" ;
	    pLogRec->save_prologue_header( oss->rdbuf() ) ;
	    pLogRec->save_prologue( oss->rdbuf() ) ;
	    pLogRec->save_data_buffer( oss->rdbuf() ) ;
	    break ;
    }
    (*oss) << '\0' ;
    char *p = oss->str() ;
    if( p ) 
    {
	info.add_data( string( p ) ) ;
	delete p ;
    }
    delete oss ;
}

inline void
deal_with_record( CedarBlock &block,
                  CedarConstraintEvaluator &qa,
		  DODSInfo &info )
{
    const CedarLogicalRecord *pLogRec = block.get_first_record() ;
    if( pLogRec )
    {
	if( qa.validate_record( pLogRec ) )
	route_buffer( pLogRec, info ) ;
	pLogRec = block.get_next_record() ;
	while( pLogRec )
	{
	    if( qa.validate_record( pLogRec ) )
		route_buffer( pLogRec, info ) ;
	    pLogRec = block.get_next_record() ;
	}
    }
}

bool
cedar_read_info( DODSInfo &info, const string &filename,
                 const string &name, const string &query, string &error )
{
    CedarConstraintEvaluator qa ;
    try
    {
	qa.parse( query.c_str() ) ;
    }
    catch( CedarException &ex )
    {
	error = ex.get_description() ;
	return false ;
    }

    CedarFile file ;
    try
    {
	info.add_data( "CATALOG AND HEADER RECORD CORRESPONDING TO: " ) ;
	info.add_data( name ) ;
	info.add_data( "\n" ) ;
	file.open_file( filename.c_str() ) ;
	const CedarLogicalRecord *lr = file.get_first_logical_record() ;

	if( lr )
	{
	    if( qa.validate_record( lr ) )
		route_buffer( lr, info ) ;
	    while( !file.end_dataset() )
	    {
		lr = file.get_next_logical_record() ;
		if( lr )
		    if( qa.validate_record( lr ) )
			route_buffer( lr, info ) ;
	    }
	}
	else 
	{
	    error = "Failure reading data, corrupted file or not a cbf file.\n";
	    return false ;
	}
    }
    catch( CedarException &ex )
    {
	error = ex.get_description() ;
	return false ;
    }

    return true ;
}

// $Log: cedar_read_info.cc,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
