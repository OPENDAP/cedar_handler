// cedar_read_attributes.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef cedar_read_attributes_h_
#define cedar_read_attributes_h_ 1


#include "DAS.h"
#include "cgi_util.h"
#include "CedarFile.h"
#include "CedarDataRecord.h"


/**
  Reads the attribute data from a cbf file and loads it into a DAS object.
  This is the entry point for reading the attribute data from a given cbf
  file "filename" into and DAS object "das."

  The algorithm parses sequentially the cbf file to extract the data records
  from it; at every step if successful the data record is loaded into das
  using the function "load_das(...)". 

  @param das: reference the the DAS object to be loaded with the attribute data.
  @param filename: full qualify path to the cbf file where the data resides.
  @param error: Pointer to string object where a error string can be loaded indicating the reason for failure of this function.
  @return bool: True if the process have not problem loading the data, false otherwise.
  @see load_das
  */
bool cedar_read_attributes(DAS &das, string filename, string &cedar_error);

/**
  loads a single data record into a DAS object.
 
  By calling member methods of CedarDataRecord class in the Cedar api core
  and methods from the DODS core, a Data Attribute object (DAS) is built.
  Here lays the algorithm in which a data record parameters information is
  mapped to Attributes Tables. Even thought you may think this is the same
  as read_descriptors and load_dds (in fact we tried to keep the function
  prototypes very similar) inside they are substantially different because
  of the nature of the data they manipulate.
  @param das: A reference to the DDS object where to load the data.
  @param my_data_record: A reference to a CedarDataRecord object which contains the data to be loaded.
  @return void: At this point no return value is present until a more firm policy exist about what to do with corrupted data records. The idea is that if this function returns false then its master user (read_attributes) will spoil the whole dataset just because one record.
  @see read_attributes
  */
void load_das(DAS &das,CedarDataRecord *dr);

/**
  Mantains records about which data records has been used to build the
  DAS object.
  
  This method is used by load_das.

  Everytime a data record is extracted from a cbf file, it is parse in
  order to extract its attributes into an Attribute table. However from
  attributes point of view two data records are considered the same if
  they have the same KINDAT. In order to improve speed a static data
  structure is mantained by this function in which KINDATs are stored if
  their corresponding data records have been parsed. 

  This method will return 0 (false) if the KINDAT which is passed has not
  been logged, therefore giving a green light to load_das to parse the
  data record and add it to the DAS object.

  @param dat: the KINDAT value for the corresponding data record which is about to be parse by load_das.
  @returns: 0 (false) if the KINDAT is not already logged. 1 (true) if the KINDAT is already logged.
  @see load_das
  */
int logged(int dat);

#endif // cedar_read_attributes_h_

// $Log: cedar_read_attributes.h,v $
// Revision 1.2  2004/12/15 17:44:12  pwest
// added copyright, updated container persistence method look_for
//
// Revision 1.1  2004/06/30 21:04:03  pwest
// cedar_handler uses the new dispatch code and can also be built for normal
// cgi scripting (except the cgi needs to be updated to not check for
// extensions but allow the handler to do that) The cgi handler also needs the
// dispatch code.
//
