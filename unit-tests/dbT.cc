// dbT.cc

#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit ;

#include <iostream>

using std::cerr ;
using std::endl ;

#include "CedarDB.h"
#include "CedarMySQLDB.h"
#include "CedarDBResult.h"
#include "BESInternalError.h"
#include "BESDebug.h"
#include "test_config.h"

class dbT: public TestFixture {
private:

public:
    dbT() {}
    ~dbT() {}

    void setUp()
    {
    } 

    void tearDown()
    {
    }

    CPPUNIT_TEST_SUITE( dbT ) ;

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

	    CedarDB *db = CedarDB::DB( "Catalog" ) ;
	    if( !db )
	    {
		CPPUNIT_ASSERT( !"Database empty" ) ;
	    }

	    cerr << (*db) << endl ;

	    db->open() ;

	    CedarDBResult *result =
		db->run_query( "SELECT * from tbl_instrument" ) ;
	    if( !result )
	    {
		CPPUNIT_ASSERT( !"result set empty" ) ;
	    }

	    cerr << (*result) << endl ;

	    bool gotone = result->first_row() ;
	    while( gotone )
	    {
		cerr << "KINST = " << (*result)["KINST"] << endl ;
		gotone = result->next_row() ;
	    }

	    CedarDB::Close() ;
	}
	catch( BESInternalError &e )
	{
	    cerr << e << endl ;
	    CPPUNIT_ASSERT( !"Caught BES exception" ) ;
	}
    }

} ;

CPPUNIT_TEST_SUITE_REGISTRATION( dbT ) ;

int 
main( int, char** )
{
    CppUnit::TextTestRunner runner ;
    runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() ) ;

    bool wasSuccessful = runner.run( "", false )  ;

    return wasSuccessful ? 0 : 1 ;
}

