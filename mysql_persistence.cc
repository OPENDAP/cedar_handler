// mysql_persistence.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include <iostream>

using std::endl ;

#include "DODSInitList.h"
#include "DODSInitOrder.h"
#include "DODSContainerPersistenceMySQL.h"
#include "DODSContainerPersistenceList.h"
#include "DODSLog.h"

static bool
MySQLPersistenceInit(int, char**) {
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "Adding MySQL Persistence" << endl;
    DODSContainerPersistenceMySQL *cpf =
	    new DODSContainerPersistenceMySQL( "MySQL" ) ;
    DODSContainerPersistenceList::TheList()->add_persistence( cpf ) ;
    return true;
}

static bool
MySQLPersistenceTerm(void) {
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "Removing MySQL Persistence" << endl;
    DODSContainerPersistenceList::TheList()->rem_persistence( "MySQL" ) ;
    return true ;
}

FUNINITQUIT( MySQLPersistenceInit, MySQLPersistenceTerm, PERSISTENCE_INIT ) ;

// $Log: mysql_persistence.cc,v $
// Revision 1.2  2004/09/09 17:17:12  pwest
// Added copywrite information
//
// Revision 1.1  2004/06/30 20:16:24  pwest
// dods dispatch code, can be used for apache modules or simple cgi script
// invocation or opendap daemon. Built during cedar server development.
//
