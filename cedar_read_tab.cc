// cedar_read_tab.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include <exception>
#include <cstddef>
#include <new>

#include "CedarFile.h"
#include "CedarTab.h"
#include "cedar_read_tab.h"
#include "CedarException.h"
#include "cedar_read_descriptors.h"
#include "cedar_read_tab_support.h"
#include "CedarParameter.h"
#include "CedarConstraintEvaluator.h"

#ifdef __GNUG__
#include <strstream>
#else
#include <sstream>
#endif

struct _printable_parameter
{
    field par_value;
    bool is_valid;
};

typedef _printable_parameter printable_parameter;

void send_tab_data(CedarTab &tab_object, CedarDataRecord &dr, CedarConstraintEvaluator &qa)
{
    if (qa.validate_record(dr))
    {
	ostrstream oss;
	unsigned int w = 0 ;
	int y,z = 0 ;
	CedarDate bdate,edate;
	dr.get_record_begin_date(bdate);
	dr.get_record_end_date(edate);
	oss<<"KINST"<<'\t'<<"KINDAT"<<'\t'<<"IBYRT"<<'\t'<<"IBDTT"<<'\t'<<"IBHMT"<<'\t'<<"IBCST"<<'\t'<<"IEYRT"<<'\t'<<"IEDTT"<<'\t'<<"IEHMT"<<'\t'<<"IECST"<<'\t'<<"JPAR"<<'\t'<<"MPAR"<<'\t'<<"NROWS"<<endl;
	oss<<dr.get_record_kind_instrument()<<'\t';
	oss<<dr.get_record_kind_data()<<'\t';
	oss<< bdate.get_year()<<'\t';
	oss<<bdate.get_month_day()<<'\t';
	oss<<bdate.get_hour_min()<<'\t';
	oss<<bdate.get_second_centisecond()<<'\t';
	oss<<edate.get_year()<<'\t';
	oss<<edate.get_month_day()<<'\t';
	oss<<edate.get_hour_min()<<'\t';
	oss<<edate.get_second_centisecond()<<'\t';
	oss<<dr.get_jpar()<<'\t';
	oss<<dr.get_mpar()<<'\t';
	oss<<dr.get_nrows()<<endl;

	unsigned int jpar_value=dr.get_jpar();
	short int *pJparData =new short int[jpar_value];
	if (!pJparData)
	{
	    throw bad_alloc();
	}
	dr.load_JPAR_data(pJparData);

	short int *pJparVars = new short int[jpar_value];
	if (!pJparVars)
	{
	    throw bad_alloc();
	}
	dr.load_JPAR_vars(pJparVars);

	for (w=0; w<jpar_value; w++)
	{ 
	    string JparVarName="";
	    string the_var="";
	    if (qa.validate_parameter(pJparVars[w]))
	    {
		int val;
		if (pJparVars[w]<0)
		{
		    val=pJparVars[w]*-1;
		    the_var+="e_";
		}
		else
		{
		    val=pJparVars[w];
		}
		get_name_for_parameter(JparVarName,val);
		the_var+=JparVarName;
		oss<<the_var;
		if(w<(jpar_value-1))
		{
		    oss<<'\t';
		}
	    }
	}
	oss<<endl;

	for (w=0; w<jpar_value; w++)
	{ 
	    if (qa.validate_parameter(pJparVars[w]))
	    {
		oss<<pJparVars[w];
		if(w<(jpar_value-1))
		{
		    oss<<'\t';
		}
	    }
	}
	oss<<endl;
	for (w=0; w<jpar_value; w++)
	{ 
	    if (qa.validate_parameter(pJparVars[w]))
	    {
		oss<<pJparData[w];
		if(w<(jpar_value-1))
		{
		    oss<<'\t';
		}
	    }
	}
	oss<<endl;
	delete [] pJparData;
	delete [] pJparVars;

	int mpar_value=dr.get_mpar();
	int nrow_value=dr.get_nrows();
	if ((mpar_value>0) && (nrow_value>0))
	{
	    short int *pMparVars=new short int[mpar_value];
	    if (!pMparVars)
	    {
		throw bad_alloc();
	    }
	    dr.load_MPAR_vars(pMparVars);

	    short int *pMparData=new short int[nrow_value*mpar_value];
	    if (!pMparData)
	    {
		throw bad_alloc();
	    }
	    dr.load_MPAR_data(pMparData);

	    for (y=0; y<mpar_value;y++)
	    {
		string MparVarName="";
		string the_var="";
		if (qa.validate_parameter(pMparVars[y]))
		{
		    int val;
		    if (pMparVars[y]<0)
		    {
			val=pMparVars[y]*-1;
			the_var+="e_";
		    }
		    else
		    {
			val=pMparVars[y];
		    }
		    get_name_for_parameter(MparVarName,val);
		    the_var+=MparVarName;
		    oss<<the_var;
		    if(y<(mpar_value-1))
		    {
			oss<<'\t';
		    }
		}
	    }
	    oss<<endl;

	    unsigned int number_of_valid_variables=0;

	    printable_parameter valid_printable_parameters[mpar_value];

	    for (y=0; y<mpar_value;y++)
	    {
		valid_printable_parameters[y].is_valid=0;
	    }

	    for (y=0; y<mpar_value;y++)
	    {
		if (qa.validate_parameter(pMparVars[y]))
		{
		    number_of_valid_variables++;
		    oss<<pMparVars[y];
		    if(y<(mpar_value-1))
		    {
			oss<<'\t';
		    }
		    valid_printable_parameters[y].is_valid=1;
		    valid_printable_parameters[y].par_value=pMparVars[y];
		}
	    }
	    oss<<endl;

	    // Print the data

	    CedarParameter pp;

	    unsigned int number_of_printable_items;

	    bool print_row;

	    for (y=0; y<nrow_value;y++)
	    {
		print_row=1;

		if (qa.got_parameter_constraint())
		{
		    number_of_printable_items=0;
		    for (z=0; z<mpar_value;z++)
		    {
			if(valid_printable_parameters[z].is_valid)
			{
			    pp=qa.get_parameter(valid_printable_parameters[z].par_value);
			    if(pp.validateValue(pMparData[z+(y*mpar_value)]))
			    {
				number_of_printable_items++;
			    }
			}
		    }

		    if(number_of_printable_items!=number_of_valid_variables)
		    {
			print_row=0;
		    }
		}

		if (print_row)
		{
		    for (z=0; z<mpar_value;z++)
		    {
			if(valid_printable_parameters[z].is_valid)
			{
			    oss<<pMparData[z+(y*mpar_value)];

			    if(z<(mpar_value-1))
			    {
				oss<<'\t';
			    }
			}
		    }
		    oss<<endl;
		}
	    }

	    delete [] pMparVars;
	    delete [] pMparData;

	    oss<<endl;
	}
	oss<<'\0';
	char *p=0;
	p=oss.str();
	if (p) 
	{
	    tab_object.add_data(string(p));
	    delete p;
	}
    }
}

int cedar_read_tab(CedarTab &dt, string filename, string query, string &error)
{
    CedarConstraintEvaluator qa;
    try
    {
	qa.parse(query.c_str());
    }
    catch (CedarException &ex)
    {
	error=ex.get_description();
	return 0;
    }

    CedarFile file;
    try
    {
	file.open_file (filename.c_str());
	const CedarLogicalRecord *lr =file.get_first_logical_record();

	if(lr)
	{
	    if((lr->get_type()==1))
	    {
		send_tab_data(dt, *(CedarDataRecord*)lr,qa);
	    }
	    while (!file.end_dataset())
	    {
		lr=file.get_next_logical_record();
		if(lr)
		{
		    if((lr->get_type()==1))
		    {
			send_tab_data(dt, *(CedarDataRecord*)lr,qa);
		    }
		}
	    }
	}
	else 
	{
	    error = (string)"Failure reading data from file "
		    + filename
		    + ", corrupted file or not a cbf file.\n" ;
	    return false;
	}
    }
    catch (CedarException &cedarex)
    {
	error="The requested dataset produces the following exception ";
	error+=cedarex.get_description() + (string)"\n";
	return 0;
    }
    catch (bad_alloc::bad_alloc)
    {
	error="There has been a memory allocation error.\n";
	return 0;
    }
    catch (...)
    {
	error="There has been an undefined exception while executing the request.\n";
	return 0;
    }

    return 1;
}
 
// $Log: cedar_read_tab.cc,v $
// Revision 1.3  2005/03/17 20:47:54  pwest
// added more information to error messages
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
