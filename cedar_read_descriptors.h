// cedar_read_descriptors.h

#ifndef cedar_read_descriptors_h_
#define cedar_read_descriptors_h_ 1

#include "DDS.h"
#include "util.h"
#include "CedarFile.h"
#include "CedarDataRecord.h"

class PassiveStructure ;
class CedarConstraintEvaluator ;

bool cedar_read_descriptors( DDS &dds, string filename, string name,
			     string query, string &cedar_error ) ;

void load_dds( PassiveStructure &, CedarDataRecord *my_data_record,
	       CedarConstraintEvaluator &qa, int &index ) ;

void get_name_for_parameter( string &str, int par ) ;

#endif // cedar_read_descriptors_h_

// $Log: cedar_read_descriptors.h,v $
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
