// cedar_read_descriptors.cc

// This file is part of the OPeNDAP Cedar data handler, providing data
// access views for CedarWEB data

// Copyright (c) 2004,2005 University Corporation for Atmospheric Research
// Author: Patrick West <pwest@ucar.edu> and Jose Garcia <jgarcia@ucar.edu>
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
// You can contact University Corporation for Atmospheric Research at
// 3080 Center Green Drive, Boulder, CO 80301
 
// (c) COPYRIGHT University Corporation for Atmostpheric Research 2004-2005
// Please read the full copyright statement in the file COPYRIGHT_UCAR.
//
// Authors:
//      pwest       Patrick West <pwest@ucar.edu>
//      jgarcia     Jose Garcia <jgarcia@ucar.edu>

#include "CedarReadParcods.h"
#include "CedarConstraintEvaluator.h"
#include "PassiveArray.h"
#include "PassiveStructure.h"
#include "PassiveInt16.h"
#include "PassiveUInt16.h"

#include "cedar_read_descriptors.h"

#include "CedarException.h"
#include "BESAutoPtr.cc"
#include "TheBESKeys.h"
#include "cgi_util.h"

bool cedar_read_descriptors( DDS &dds, const string &filename,
                             const string &name, const string &query,
			     string &error )
{
    int i=0;
    CedarConstraintEvaluator qa;
    BESAutoPtr <PassiveStructure> container( new PassiveStructure( name ) ) ;

    try
    {
	qa.parse(query.c_str());
    }
    catch (CedarException &ex)
    {
	error=ex.get_description();
	return false;
    }

    try
    {
	CedarFile file;
	file.open_file (filename.c_str());
	const CedarLogicalRecord* lr=file.get_first_logical_record();
	if(lr)
	{
	    if( lr->get_type() == 1 )
	    {
		load_dds( *container, (CedarDataRecord*)lr, qa, i ) ;
	    }
	    while (!file.end_dataset())
	    {
		lr = file.get_next_logical_record();
		if(lr) 
		{
		    if( lr->get_type() == 1 )
		    {
			load_dds( *container, (CedarDataRecord*)lr, qa, i ) ;
		    }
		}
	    }
	}
	else
	{
	    error = "Can not connect to file-> " ;
	    error += filename ;
	    error += " .Non existent file or no a cbf file.\n" ;
	    return false ;
	}
    }
    catch (CedarException &cedarex)
    {
	error = "The requested dataset is either corrupted or is not a cbf file\n" ;
	error += "The following message is reported from the Cedar API:\n" ;
	error += cedarex.get_description() ;
	return false;
    }
    catch(bad_alloc &)
    {
	string max;
	try
	{
	    bool found = false ;
	    max = TheBESKeys::TheKeys()->get_key( "BES.Memory.GlobalArea.MaximunHeapSize", found ) ;
	    if(max == "" )
		max = "[can not determine at this time]" ;
	}
	catch(...)
	{
	    max = "[can not determine at this time]" ;
	}
	error = (string)"There has been a memory allocation problem "
	      + "(bad_alloc).\n"
	      + "Please contact the server administrator "
	      + "with the following information:\n"
	      + "The dataset " + filename
	      + " is too large for the current server to handle.\n"
	      + "This server is set to have a maximun heap size of "
	      + max + "\n"
	      + "The server administrator may either increase the maximun "
	      + "heap size for the server or it may split the container "
	      + "you are requesting in smaller blocks\n";
	return false;
    }
    catch(...)
    {
	error = (string)"Undefined exception on server.\n"
	      + "Please contact the server administrator with the "
	      + "following information:\n"
	      + "The dataset " + filename + " causes an undefined "
	      + "exception on the server.\n" ;
	return false;
    }

    dds.add_var(container.get());
    dds.set_dataset_name(name_path(filename));

    return true;
}

void get_name_for_parameter(string &str, int par)
{
    CedarReadParcods afx;
    str="";
    if (par<0)
    {
	par=par*-1;
	str="e_";
    }
    string madnam=afx.get_MADNAM(par);
    if (madnam=="")
    {
	madnam="var_";
	char tmp[100];
	CedarStringConversions::ltoa(par,tmp,10);
	madnam+=tmp;
    }
    str+=madnam;
}
  
void load_dds( PassiveStructure &container, CedarDataRecord *my_data_record,
	       CedarConstraintEvaluator &qa, int &i )
{
    if( qa.validate_record( my_data_record ) )
    {
	i++;
	char stuyo [5];
	CedarStringConversions::ltoa(i,stuyo,10);
	string record_name = "data_record_";
	record_name+=stuyo;

	// BEGIN HERE LOADING PROLOGUE
	BESAutoPtr <PassiveInt16> pKINST (new PassiveInt16("KINST"));
	pKINST->set_value(my_data_record->get_record_kind_instrument());
	BESAutoPtr <PassiveInt16> pKINDAT(new PassiveInt16("KINDAT"));
	pKINDAT->set_value(my_data_record->get_record_kind_data());
	CedarDate bdate,edate;
	my_data_record->get_record_begin_date(bdate);
	my_data_record->get_record_end_date(edate);
	BESAutoPtr<PassiveUInt16> pIBYRT(new PassiveUInt16 ("IBYRT"));
	pIBYRT->set_value(bdate.get_year());
	BESAutoPtr<PassiveUInt16> pIBDTT (new PassiveUInt16 ("IBDTT")); 
	pIBDTT->set_value(bdate.get_month_day());
	BESAutoPtr<PassiveUInt16> pIBHMT (new PassiveUInt16 ("IBHMT")); 
	pIBHMT->set_value(bdate.get_hour_min());
	BESAutoPtr<PassiveUInt16> pIBCST (new PassiveUInt16 ("IBCST"));
	pIBCST->set_value(bdate.get_second_centisecond());
	BESAutoPtr<PassiveUInt16> pIEYRT (new PassiveUInt16 ("IEYRT"));
	pIEYRT->set_value(edate.get_year());
	BESAutoPtr<PassiveUInt16> pIEDTT (new PassiveUInt16 ("IEDTT"));
	pIEDTT->set_value(edate.get_month_day());
	BESAutoPtr<PassiveUInt16> pIEHMT (new PassiveUInt16 ("IEHMT"));
	pIEHMT->set_value(edate.get_hour_min());
	BESAutoPtr<PassiveUInt16> pIECST (new PassiveUInt16 ("IECST"));
	pIECST->set_value(edate.get_second_centisecond());
	BESAutoPtr<PassiveStructure> pPROLOGUEstructure (new PassiveStructure ("prologue"));
	pPROLOGUEstructure -> add_var (pKINST.get());
	pPROLOGUEstructure -> add_var (pKINDAT.get());
	pPROLOGUEstructure -> add_var (pIBYRT.get());
	pPROLOGUEstructure -> add_var (pIBDTT.get());
	pPROLOGUEstructure -> add_var (pIBHMT.get());
	pPROLOGUEstructure -> add_var (pIBCST.get());
	pPROLOGUEstructure -> add_var (pIEYRT.get());
	pPROLOGUEstructure -> add_var (pIEDTT.get());
	pPROLOGUEstructure -> add_var (pIEHMT.get());
	pPROLOGUEstructure -> add_var (pIECST.get());
	// END HERE LOADING PROLOGUE

	// BEGIN HERE LOADING JPAR SECTION
	unsigned int jpar_value=my_data_record->get_jpar();
	BESAutoPtr <dods_int16> pJparData (new dods_int16[jpar_value],true);
	my_data_record->load_JPAR_data(pJparData.get());
	BESAutoPtr <dods_int16> pJparVars (new dods_int16[jpar_value],true);
	my_data_record->load_JPAR_vars(pJparVars.get());
	BESAutoPtr <PassiveStructure>  pJPARstructure (new PassiveStructure ("JPAR"));
	string JparVarName;
	int is_JPAR_empty=1;
	for (unsigned int w=0; w<jpar_value; w++)
	{ 
	    if (qa.validate_parameter(pJparVars.get()[w]))
	    {
		is_JPAR_empty=0;
		get_name_for_parameter(JparVarName,pJparVars.get()[w]);
		BESAutoPtr <PassiveInt16> pjpardata (new PassiveInt16 (JparVarName));
		pjpardata->set_value(pJparData.get()[w]);
		pJPARstructure->add_var(pjpardata.get());
	    }
	}
	// END HERE LOADING JPAR SECTION

	// BEGIN HERE LOADING MPAR SECTION
	BESAutoPtr <PassiveStructure> pMPARstructure (new PassiveStructure("MPAR"));
	int mpar_value=my_data_record->get_mpar();
	int nrow_value=my_data_record->get_nrows();
	int is_MPAR_empty=1;
	if ((mpar_value>0) && (nrow_value>0))
	{
	    BESAutoPtr <dods_int16> pMparVars (new dods_int16[mpar_value],true);
	    my_data_record->load_MPAR_vars(pMparVars.get());
	    BESAutoPtr <dods_int16> pMparData (new dods_int16[nrow_value*mpar_value],true);
	    BESAutoPtr <dods_int16> pPartialMparData (new dods_int16[nrow_value],true);
	    my_data_record->load_MPAR_data(pMparData.get());
	    string MparVarName;
	    for (int j=0; j<mpar_value;j++)
	    {
		if (qa.validate_parameter(pMparVars.get()[j]))
		{
		    is_MPAR_empty=0;
		    get_name_for_parameter(MparVarName,pMparVars.get()[j]);
		    BaseType *pMparvar = new PassiveInt16( MparVarName ); 
		    BESAutoPtr<PassiveArray> pmpararray( new PassiveArray( MparVarName, pMparvar ) ) ;
		    delete pMparvar ; pMparvar = 0 ;
		    pmpararray->append_dim(nrow_value);
		    for (int w=0; w<nrow_value;w++)
		    {
			pPartialMparData.get()[w]=pMparData.get()[j+(w*mpar_value)];
		    }
		    pmpararray->set_value(pPartialMparData.get(),nrow_value);
		    pMPARstructure -> add_var(pmpararray.get());
		}
	    }
	}
	// END HERE LOADING MPAR SECTION

	BESAutoPtr <PassiveStructure> precord (new PassiveStructure(record_name));
	precord -> add_var (pPROLOGUEstructure.get());
	if (!is_JPAR_empty)
	    precord->add_var(pJPARstructure.get());
	if (!is_MPAR_empty)
	    precord->add_var(pMPARstructure.get());
	container.add_var(precord.get());
    }
}

