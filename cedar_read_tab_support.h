// cedar_read_tab_support.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef cedar_read_tab_support_h
#define cedar_read_tab_support_h 1

typedef CedarArray <field> *pcedararray_of_field;


#endif // cedar_read_tab_support_h

// $Log: cedar_read_tab_support.h,v $
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
