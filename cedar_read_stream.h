// cedar_read_stream.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef cedar_read_stream_h_
#define cedar_read_stream_h_ 1

bool cedar_read_stream( const string &filename, const string &query,
                        string &error ) ;

#endif // cedar_read_stream_h_

// $Log: cedar_read_stream.h,v $
// Revision 1.3  2005/05/10 00:23:06  pwest
// using const reference to strings in signature instead of string values
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
