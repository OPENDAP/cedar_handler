// CedarHandlerApp.cc

#include <signal.h>
#include <unistd.h>

#include <iostream>

using std::cout ;
using std::cerr ;
using std::endl ;
using std::flush ;

#include "CedarHandlerApp.h"
#include "CedarResponseNames.h"
#include "CedarFilter.h"
#include "DODSCgi.h"
#include "TheDODSKeys.h"

CedarHandlerApp::CedarHandlerApp()
    : _df( 0 )
{
}

CedarHandlerApp::~CedarHandlerApp()
{
    if( _df )
    {
	delete _df ;
	_df = 0 ;
    }
}

int
CedarHandlerApp::initialize( int argc, char **argv )
{
    int retVal = OPeNDAPBaseApp::initialize( argc, argv ) ;
    if( !retVal )
    {
	_df = new CedarFilter( argc, argv ) ;
    }

    return retVal ;
}

int
CedarHandlerApp::run()
{
    string my_key = "Cedar.Authenticate.MySQL.mode" ;
    TheDODSKeys::TheKeys()->set_key( my_key, "off" ) ;
    DODSCgi d( CEDAR_NAME, *_df ) ;
    d.execute_request() ;

    return 0 ;
}

