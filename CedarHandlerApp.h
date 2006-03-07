// CedarHandlerApp.h

#include "OPeNDAPBaseApp.h"
#include "DODSDataHandlerInterface.h"

class DODSFilter ;

class CedarHandlerApp : public OPeNDAPBaseApp
{
private:
    DODSFilter *		_df ;
public:
    				CedarHandlerApp() ;
    virtual			~CedarHandlerApp() ;
    virtual int			initialize( int argc, char **argv ) ;
    virtual int			run() ;

    static bool			set_user( DODSDataHandlerInterface &dhi ) ;
} ;

