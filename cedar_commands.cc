// cedar_commands.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include <iostream>

using std::endl ;

#include "DODSInitList.h"
#include "DODSInitOrder.h"
#include "OPeNDAPCommand.h"
#include "TheDODSLog.h"
#include "DODSResponseNames.h"
#include "CedarResponseNames.h"

static bool
CedarCmdInit(int, char**)
{
    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "Initializing Cedar Commands:" << endl ;

    string cmd_name = string( GET_RESPONSE ) + "." + FLAT_RESPONSE ;
    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "    adding " << cmd_name << " command" << endl;
    OPeNDAPCommand::add_command( cmd_name, OPeNDAPCommand::TermCommand ) ;

    cmd_name = string( GET_RESPONSE ) + "." + TAB_RESPONSE ;
    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "    adding " << cmd_name << " command" << endl;
    OPeNDAPCommand::add_command( cmd_name, OPeNDAPCommand::TermCommand ) ;

    cmd_name = string( GET_RESPONSE ) + "." + STREAM_RESPONSE ;
    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "    adding " << cmd_name << " command" << endl;
    OPeNDAPCommand::add_command( cmd_name, OPeNDAPCommand::TermCommand ) ;

    cmd_name = string( GET_RESPONSE ) + "." + INFO_RESPONSE ;
    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "    adding " << cmd_name << " command" << endl;
    OPeNDAPCommand::add_command( cmd_name, OPeNDAPCommand::TermCommand ) ;

    return true ;
}

static bool
CedarCmdTerm(void)
{
    return true ;
}

FUNINITQUIT( CedarCmdInit, CedarCmdTerm, DODSMODULE_INIT ) ;

// $Log: cedar_commands.cc,v $
