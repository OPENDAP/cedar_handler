// CedarReporter.cc

#include "CedarReporter.h"
#include "TheDODSKeys.h"
#include "DODSLogException.h"

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

    *(_file_buffer) << dhi.user_name << " " << dhi.user_address << " "
		    << dhi.action << " " << dhi.real_name_list << " \""
		    << dhi.request << "\"" << endl ;
}

// $Log: CedarReporter.cc,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
