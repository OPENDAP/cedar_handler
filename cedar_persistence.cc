// cedar_persistence.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include <iostream>

using std::endl ;

#include "DODSInitList.h"
#include "DODSInitOrder.h"
#include "DODSContainerPersistenceCedar.h"
#include "DODSContainerPersistenceList.h"
#include "DODSLog.h"

static bool
CedarPersistenceInit(int, char**) {
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "Adding Cedar Persistence" << endl;
    DODSContainerPersistenceCedar *cpf =
	    new DODSContainerPersistenceCedar( "Cedar" ) ;
    DODSContainerPersistenceList::TheList()->add_persistence( cpf ) ;
    return true;
}

static bool
CedarPersistenceTerm(void) {
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "Removing Cedar Persistence" << endl;
    DODSContainerPersistenceList::TheList()->rem_persistence( "Cedar" ) ;
    return true ;
}

FUNINITQUIT( CedarPersistenceInit, CedarPersistenceTerm, PERSISTENCE_INIT ) ;

// $Log: cedar_persistence.cc,v $
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
