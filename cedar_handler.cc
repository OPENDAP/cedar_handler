// cedar_handler.cc

// 2004 Copyright University Corporation for Atmospheric Research

// -*- mode: c++; c-basic-offset:4 -*-

// This file is part of libdap, A C++ implementation of the OPeNDAP Data
// Access Protocol.

// Copyright (c) 2002,2003 OPeNDAP, Inc.
// Author: Patrick West <pwest@ucar.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// You can contact OPeNDAP, Inc. at PO Box 112, Saunderstown, RI. 02874-0112.
 
#include "config_cedar.h"

static char not_used rcsid[]={"$Id: cedar_handler.cc,v 1.3 2005/04/06 20:14:24 pwest Exp $"};

#include "DODSCgi.h"
#include "CedarFilter.h"
#include "DODSGlobalIQ.h"
#include "DODSException.h"

int 
main(int argc, char *argv[])
{
    try
    {
	putenv( "DODS_INI=/project/cedar/bin/apache_1.3.29/conf/opendap.ini" ) ;
	DODSGlobalIQ::DODSGlobalInit( argc, argv ) ;
    }
    catch( DODSException &e )
    {
	cerr << "Error initializing application" << endl ;
	cerr << "    " << e.get_error_description() << endl ;
	return 1 ;
    }

    CedarFilter df(argc, argv);

    DODSCgi d( "cedar", df ) ;
    d.execute_request() ;

    DODSGlobalIQ::DODSGlobalQuit() ;

    return 0;
}

// $Log: cedar_handler.cc,v $
// Revision 1.3  2005/04/06 20:14:24  pwest
// added initialization and termination calls
//
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
