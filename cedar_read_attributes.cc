// cedar_read_attributes.cc

// 2004 Copyright University Corporation for Atmospheric Research

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

// $Log: cedar_read_attributes.cc,v $
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
