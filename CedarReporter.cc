// CedarReporter.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include "CedarReporter.h"
#include "TheDODSKeys.h"
#include "DODSLogException.h"
#include "OPeNDAPDataNames.h"

CedarReporter::CedarReporter()
    : DODSReporter(),
      _file_buffer( 0 )
{
    bool found = false ;
    string log_name = TheDODSKeys->get_key( "Cedar.LogName", found ) ;
    if( log_name == "" )
    {
	DODSLogException e ;
	e.set_error_description( "can not determine Cedar log name" ) ;
	throw e ;
    }
    else
    {
	_file_buffer = new ofstream( log_name.c_str(), ios::out | ios::app ) ;
	if( !(*_file_buffer) )
	{
	    DODSLogException le ;
	    le.set_error_description( "can not open Cedar log file" ) ;
	    throw le ;
	} 
    }
}

CedarReporter::~CedarReporter()
{
    if( _file_buffer )
    {
	delete _file_buffer ;
	_file_buffer = 0 ;
    }
}

void
CedarReporter::report( const DODSDataHandlerInterface &dhi )
{
    const time_t sctime = time( NULL ) ;
    const struct tm *sttime = localtime( &sctime ) ; 
    char zone_name[10] ;
    strftime( zone_name, sizeof( zone_name ), "%Z", sttime ) ;
    char *b = asctime( sttime ) ;
    *(_file_buffer) << "[" << zone_name << " " ;
    for(register int j = 0; b[j] != '\n'; j++ )
	*(_file_buffer) << b[j] ;
    *(_file_buffer) << "] " ;

    string user_name = "" ;
    DODSDataHandlerInterface::data_citer citer ;
    citer = dhi.data_c().find( USER_NAME ) ;
    if( citer != dhi.data_c().end() )
	user_name = (*citer).second ;

    if( user_name == "" )
	*(_file_buffer) << "USER_UNKNOWN" ;
    else
	*(_file_buffer) << user_name ;

    string request = "" ;
    citer = dhi.data_c().find( DATA_REQUEST ) ;
    if( citer != dhi.data_c().end() )
	request = (*citer).second ;

    string real = "" ;
    citer = dhi.data_c().find( REAL_NAME_LIST ) ;
    if( citer != dhi.data_c().end() )
	real = (*citer).second ;

    *(_file_buffer) << " " << dhi.action << " " << real << " \"" 
                    << request << "\"" << endl ;
}

// $Log: CedarReporter.cc,v $
// Revision 1.4  2005/02/09 20:30:18  pwest
// catch up to dispatch
//
// Revision 1.3  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.2  2004/07/09 16:12:40  pwest
// If the user name is not available then print this information out, otherwise
// print the user name.
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
