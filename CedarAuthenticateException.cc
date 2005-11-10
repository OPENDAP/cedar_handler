// CedarAuthenticateException.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include "CedarAuthenticateException.h"
#include "OPeNDAPDataNames.h"
#include "DODSStatusReturn.h"
#include "cgi_util.h"

int
CedarAuthenticateException::handleAuthException( DODSException &e,
						 DODSDataHandlerInterface &dhi )
{
    CedarAuthenticateException *ae =
	dynamic_cast<CedarAuthenticateException*>(&e);
    if( ae )
    {
	bool ishttp = false ;
	if( dhi.transmit_protocol == "HTTP" )
	    ishttp = true ;

	if( ishttp )
	{
	    set_mime_html( stdout, dods_error ) ;
	    fprintf( stdout, "<HTML>" ) ;
	    fprintf( stdout, "<HEAD></HEAD>" ) ;
	    fprintf( stdout, "<BODY BACKGROUND='http://cedarweb.hao.ucar.edu/images/Texture_lt_gray_004.jpg'>") ;
	    fprintf( stdout, "<TABLE BACKGROUND='http://cedarweb.hao.ucar.edu/images/Texture_lt_gray_004.jpg' BORDER='0' WIDTH='100%%' CELLPADDING='1' CELLSPACING='0'>" ) ;
	    fprintf( stdout, "<TR>" ) ;
	    fprintf( stdout, "<TD WIDTH='20%%' BACKGROUND='http://cedarweb.hao.ucar.edu/images/Texture_lt_gray_004.jpg'>" ) ;
	    fprintf( stdout, "<P ALIGN='center'>" ) ;
	    fprintf( stdout, "<A HREF='http://www.ucar.edu' TARGET='_blank'><IMG SRC='http://cedarweb.hao.ucar.edu/images/CedarwebUCAR.gif' ALT='UCAR' BORDER='0'><BR><FONT SIZE='2'>UCAR</FONT></A>" ) ;
	    fprintf( stdout, "</P>" ) ;
	    fprintf( stdout, "</TD>" ) ;
	    fprintf( stdout, "<TD WIDTH='80%%' BACKGROUND='http://cedarweb.hao.ucar.edu/images/Texture_lt_gray_004.jpg'>" ) ;
	    fprintf( stdout, "<P ALIGN='center'>" ) ;
	    fprintf( stdout, "<IMG BORDER='0' SRC='http://cedarweb.hao.ucar.edu/images/Cedarweb.jpg' ALT='CEDARweb'>" ) ;
	    fprintf( stdout, "</P>" ) ;
	    fprintf( stdout, "</TD>" ) ;
	    fprintf( stdout, "</TR>" ) ;
	    fprintf( stdout, "</TABLE>" ) ;
	    fprintf( stdout, "<BR />" ) ;
	    fprintf( stdout, "<BR />" ) ;
	    fprintf( stdout, "%s %s %s.\n",
	             "We were unable to authenticate your session",
		     "for user",
		     dhi.data[USER_NAME].c_str() ) ;
	    fprintf( stdout, "<BR />\n" ) ;
	    fprintf( stdout, "<BR />\n" ) ;
	    fprintf( stdout, "%s\n", e.get_error_description().c_str() ) ;
	    fprintf( stdout, "<BR />\n" ) ;
	    fprintf( stdout, "<BR />\n" ) ;
	    fprintf( stdout, "Please follow <A HREF=\"https://cedarweb.hao.ucar.edu:443/cgi-bin/ion-p?page=login.ion\" TARGET=\"NEW\">this link</A> to login.\n" ) ;
 	    fprintf( stdout, "Then refresh this page to get your data once you have logged in\n" ) ;
	    fprintf( stdout, "</BODY></HTML>" ) ;
	}
	else
	{
	    fprintf( stdout, "Reporting Authentication Exception.\n" ) ;
	    fprintf( stdout, "%s\n", e.get_error_description().c_str() ) ;
	}
	return CEDAR_AUTHENTICATE_EXCEPTION ;
    } 
    return DODS_EXECUTED_OK ;
}

