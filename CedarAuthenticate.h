// CedarAuthenticate.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef A_CedarAuthenticate_h
#define A_CedarAuthenticate_h 1

#include "DODSDataHandlerInterface.h"

/** @brief Authentication is done through the use of MySQL database.
 *
 * This class provides a mechanism of authentication using a MySQL database,
 * specified through the dods initialization file. The database is specified
 * with the following keys in the initialization file:
 *
 * Cedar.Authenticate.MySQL.server=&lt;serverName&gt;
 * Cedar.Authenticate.MySQL.user=&lt;userName&gt;
 * Cedar.Authenticate.MySQL.password=&lt;encryptedPassword&gt;
 * Cedar.Authenticate.MySQL.database=&lt;databaseName&gt;
 * Cedar.Authenticate.MySQL.mode=&lt;on|off&gt;
 *
 * The relevant columns for authentication in the session table tbl_session,
 * looks like this:
 * 
 * USER_NAME char(30)
 * CLIENT_IP char(45)
 *
 * CedarAuthenticate can be specified on the link line as the
 * authentication mechanism by linking in the object module
 * mysql_authenticator.o. If, during development and testing of the server,
 * you wish to turn off authentication using mysql, set the mode to off.
 *
 * The password is encrypted.
 *
 * @see TheDODSKeys
 */
class CedarAuthenticate
{
public:
    static bool		authenticate( DODSDataHandlerInterface &dhi ) ;
} ;

#endif // A_CedarAuthenticate_h

// $Log: CedarAuthenticate.h,v $
// Revision 1.3  2004/12/15 17:39:03  pwest
// Added doxygen comments
//
// Revision 1.2  2004/09/09 17:17:12  pwest
// Added copywrite information
//
// Revision 1.1  2004/06/30 20:16:24  pwest
// dods dispatch code, can be used for apache modules or simple cgi script
// invocation or opendap daemon. Built during cedar server development.
//
