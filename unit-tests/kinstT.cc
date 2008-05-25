// kinstT.cc

#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>

using std::cerr ;
using std::endl ;

#include "CedarReadKinst.h"
#include "CedarMySQLDB.h"
#include "BESDebug.h"
#include "BESError.h"

#include "test_config.h"

using namespace CppUnit ;

class kinstT: public TestFixture {
private:

public:
    kinstT() {}
    ~kinstT() {}

    void setUp()
    {
    } 

    void tearDown()
    {
    }

    CPPUNIT_TEST_SUITE( kinstT ) ;

    CPPUNIT_TEST( do_conversion ) ;

    CPPUNIT_TEST_SUITE_END() ;

    void do_conversion()
    {
	string bes_conf = (string)"BES_CONF=" + TEST_SRC_DIR + "/bes.conf" ;
	putenv( (char *)bes_conf.c_str() ) ;

	BESDebug::SetUp( "cerr,cedar" ) ;
	try
	{
	    CedarDB::Add_DB_Builder( "mysql", CedarMySQLDB::BuildMySQLDB ) ;

	    string inst = CedarReadKinst::Get_Kinst_as_String( 5340 ) ;
	    cerr << "instrument = " << inst << endl ;
	    CPPUNIT_ASSERT( inst == "5340" ) ;
	    string name = CedarReadKinst::Get_Name( 5340 ) ;
	    cerr << "name = " << name << endl ;
	    CPPUNIT_ASSERT( name == "Millstone Hill Fabry-Perot" ) ;
	    string prefix = CedarReadKinst::Get_Prefix( 5340 ) ;
	    cerr << "prefix = " << prefix << endl ;
	    CPPUNIT_ASSERT( prefix == "MFP" ) ;
	    string lat = CedarReadKinst::Get_Latitude_as_String( 5340 ) ;
	    cerr << "lat = " << lat << endl ;
	    CPPUNIT_ASSERT( lat == "42 37'10\\\"" ) ;
	    string lon = CedarReadKinst::Get_Longitude_as_String( 5340 ) ;
	    cerr << "lon = " << lon << endl ;
	    CPPUNIT_ASSERT( lon == "-72 30'29\\\"" ) ;
	    string alt = CedarReadKinst::Get_Altitude_as_String( 5340 ) ;
	    cerr << "alt = " << alt << endl ;
	    CPPUNIT_ASSERT( alt == "0.146" ) ;

	    CedarDB::Close() ;
	}
	catch( BESError &e )
	{
	    cerr << e << endl ;
	    CPPUNIT_ASSERT( !"Caught BES exception" ) ;
	}
    }

} ;

CPPUNIT_TEST_SUITE_REGISTRATION( kinstT ) ;

int 
main( int, char** )
{
    CppUnit::TextTestRunner runner ;
    runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() ) ;

    bool wasSuccessful = runner.run( "", false )  ;

    return wasSuccessful ? 0 : 1 ;
}

