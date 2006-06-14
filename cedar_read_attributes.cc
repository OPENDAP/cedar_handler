// cedar_read_attributes.cc

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

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string>

using std::string ;

#include "CedarReadKinst.h"
#include "CedarReadParcods.h"
#include "cedar_read_attributes.h"
#include "CedarException.h"
#include "CedarFile.h"

static const char STRING[]="String";
static const char BYTE[]="Byte";
static const char INT16[]="Int16";
static const char FLOAT64[]="Float64";

bool cedar_read_attributes( DAS &das, const string &filename, string &error )
{
    try
    {
	CedarFile file;
	file.open_file (filename.c_str());
	const CedarLogicalRecord* lr=file.get_first_logical_record();
	if(lr)
	{
	    if(lr->get_type()==1) load_das(das, (CedarDataRecord*)lr);
	    while (!file.end_dataset())
	    {
		lr=file.get_next_logical_record();
		if(lr) 
		    if(lr->get_type()==1) load_das(das, (CedarDataRecord*)lr);
	    }
	    return true;
	}
	else
	{
	    error="Can not connect to file-> ";
	    error+=filename;
	    error+=" .Non existent file or not a cbf file.\n";
	    return false;
	}
    }
    catch (CedarException &cedarex)
    {
	error="The requested dataset is either corrupted or is not a cbf file\n";
	error+="Cedar API reports: " + (string)cedarex.get_description() + (string)"\n";
	return false;
    }
}

int logged(int dat)
{
    static CedarArray<field>reg(1,0);
    int max_elem=reg.get_size();
    for (int i=0; i<max_elem-1;i++)
    {
	if (dat==reg[i])
	    return 1;
    }
    reg.set_size(max_elem+1);
    reg[max_elem-1]=dat;
    return 0;
}

void load_das(DAS &das,CedarDataRecord *dr)
{
    if (!logged(dr->get_record_kind_data()))
    { 
	CedarReadKinst kin;
	CedarReadParcods afx;
	char tmp[100];
	string info="";
	string type="String";
	string str="Data_Descriptor_for_KINDAT_";
	CedarStringConversions::ltoa(dr->get_record_kind_data(),tmp,10);
	str+=tmp;
	str+="_KINST_";
	CedarStringConversions::ltoa(dr->get_record_kind_instrument(),tmp,10);
	str+=tmp;
	AttrTable *at=new AttrTable(); 
	AttrTable *t1;
	t1=at->append_container("KINST"); 
	info+="\"";
	info+=kin.get_info(dr->get_record_kind_instrument());
	info+="\"";
	string name="INST_";
	name+=tmp;
	t1->append_attr(name, type, info);
	int njpar=dr->get_jpar();
	short int *jparvars= new short int[njpar];
	if (jparvars)
	{
	    dr->load_JPAR_vars(jparvars);
	    for (int i=0; i<njpar; i++)
	    {
		int val;
		string nm="JPAR_";
		CedarStringConversions::ltoa(i,tmp,10);
		nm+=tmp;
		t1=at->append_container(nm);
		if (jparvars[i]<0)
		{
		    val=jparvars[i]*-1;
		    info="\"Error in ";
		    name="ERROR_IN_PARAMETER_CODE_";
		}
		else
		{
		    val=jparvars[i];
		    info="\"";
		    name="PARAMETER_CODE_";
		}
		info+=afx.get_PCLNAM(val);
		info+=" ";
		info+=afx.get_PCSFCT(val);
		info+=" ";
		info+=afx.get_PCULBL(val);
		info+="\"";
		CedarStringConversions::ltoa(val,tmp,10);
		name+=tmp;
		t1->append_attr(name, type,info);
	    }
	}
	delete [] jparvars;
	int nmpar=dr->get_mpar();
	short int *mparvars= new short int[nmpar];
	if (mparvars)
	{
	    dr->load_MPAR_vars(mparvars);
	    for (int i=0; i<nmpar; i++)
	    {
		int val;
		string nm="MPAR_";
		CedarStringConversions::ltoa(i,tmp,10);
		nm+=tmp;
		t1=at->append_container(nm);
		if (mparvars[i]<0)
		{
		    val=mparvars[i]*-1;
		    info="\"Error in ";
		    name="ERROR_IN_PARAMETER_CODE_";
		}
		else
		{
		    val=mparvars[i];
		    info="\"";
		    name="PARAMETER_CODE_";
		}
		info+=afx.get_PCLNAM(val);
		info+=" ";
		info+=afx.get_PCSFCT(val);
		info+=" ";
		info+=afx.get_PCULBL(val);
		info+="\"";
		CedarStringConversions::ltoa(val,tmp,10);
		name+=tmp;
		t1->append_attr(name, type,info);
	    }
	}
	delete [] mparvars;
	das.add_table(str, at);
    }
}

