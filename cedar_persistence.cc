// cedar_persistence.cc

#include <iostream>

using std::endl ;

#include "DODSInitList.h"
#include "DODSInitOrder.h"
#include "DODSContainerPersistenceCedar.h"
#include "ThePersistenceList.h"
#include "TheDODSLog.h"

static bool
CedarPersistenceInit(int, char**) {
    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "Adding Cedar Persistence" << endl;
    DODSContainerPersistenceCedar *cpf =
	    new DODSContainerPersistenceCedar( "Cedar" ) ;
    ThePersistenceList->add_persistence( cpf ) ;
    return true;
}

static bool
CedarPersistenceTerm(void) {
    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "Removing Cedar Persistence" << endl;
    ThePersistenceList->rem_persistence( "Cedar" ) ;
    return true ;
}

FUNINITQUIT( CedarPersistenceInit, CedarPersistenceTerm, FILEPERSISTENCE_INIT ) ;

// $Log: cedar_persistence.cc,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
