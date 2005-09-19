// cedar_commands.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include <iostream>

using std::endl ;

#include "DODSInitList.h"
#include "DODSInitOrder.h"
#include "OPeNDAPCommand.h"
#include "DODSLog.h"
#include "DODSResponseNames.h"
#include "CedarResponseNames.h"

static bool
CedarCmdInit(int, char**)
{
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "Initializing Cedar Commands:" << endl ;

    string cmd_name = string( GET_RESPONSE ) + "." + FLAT_RESPONSE ;
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding " << cmd_name << " command" << endl;
    OPeNDAPCommand::add_command( cmd_name, OPeNDAPCommand::TermCommand ) ;

    cmd_name = string( GET_RESPONSE ) + "." + TAB_RESPONSE ;
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding " << cmd_name << " command" << endl;
    OPeNDAPCommand::add_command( cmd_name, OPeNDAPCommand::TermCommand ) ;

    cmd_name = string( GET_RESPONSE ) + "." + STREAM_RESPONSE ;
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding " << cmd_name << " command" << endl;
    OPeNDAPCommand::add_command( cmd_name, OPeNDAPCommand::TermCommand ) ;

    cmd_name = string( GET_RESPONSE ) + "." + INFO_RESPONSE ;
    if( DODSLog::TheLog()->is_verbose() )
	(*DODSLog::TheLog()) << "    adding " << cmd_name << " command" << endl;
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
